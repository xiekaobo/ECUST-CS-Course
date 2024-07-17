# encoding:utf-8
# import ImageTk
import pymssql
import tkinter as tk
import tkinter.ttk
from PIL import Image, ImageTk

# skin_type:肤质
# product_name:商品名称
# out_product_name:商品详情中的商品名称
# price:商品详情中的商品价格
# out_skin_type:商品详情中的商品肤质
# item_number为商品序号
# photo为商品图片
out_product_details = []
out_product_name = ""
price = 0
out_skin_type = ""
item_number = 0
photo = None


# 寻找商品详情
def Good_detail():
    product_number = the_order_you_want.current()
    skin_type_number = the_product_you_want.current()
    skin_type = type_of_skin[skin_type_number]
    show_listbox.delete(0, tk.END)
    global item_number
    global out_product_name
    global price
    global out_skin_type
    global photo
    item_number = Goods[product_number][0]
    out_product_name = Goods[product_number][1]
    price = Goods[product_number][2]
    out_skin_type = Goods[product_number][3]
    img_path = 'D:\Marston\课程作业及资料\电商金融\A-ERP-CRM-main\A-ERP-CRM-main\CRM\img\\' + item_number + '.jpg'
    img = Image.open(img_path).resize((100, 120))
    photo = ImageTk.PhotoImage(img)

    show_product_name.delete(0, tk.END)
    show_product_name.insert(0, out_product_name)
    show_product_price.delete(0, tk.END)
    show_product_price.insert(0, price)
    show_product_skin.delete(0, tk.END)
    show_product_skin.insert(0, out_skin_type)
    # 显示商品详情界面
    show_product_photo = tk.Label(root, image=photo)
    show_product_photo.place(x=150, y=500, width=100, height=120)

    if skin_type == out_skin_type:
        recommend(out_product_name, skin_type, 1)
    else:
        recommend(out_product_name, skin_type, 0)


# 最小支持度
min_support = 0.05
# 最小置信度
min_reliability = 0.4
# 最小兴趣度
min_interest = 1
# 推荐结果
recommend_result = []


def support1(item_number):
    Buy_n = len(Buy)
    i = 0
    count = 0
    while i < Buy_n:
        if Buy[i][1] == item_number:
            count = count + 1
        i = i + 1
    support = count / N
    return support


def support2(item_number1, item_number2):
    Buy_n = len(Buy)
    i = 0
    count = 0
    while i < Buy_n:
        j = 0
        if Buy[i][1] == item_number1:
            while j < Buy_n:
                if Buy[j][1] == item_number2 and Buy[j][0] == Buy[i][0]:
                    break
                j = j + 1
            if j < Buy_n:
                count = count + 1
        i = i + 1
    support = count / N
    return support


def confidence_level(item_number1, item_number2):
    n1_support = support1(item_number1)
    n2_support = support1(item_number2)
    n12_support = support2(item_number1, item_number2)
    if n2_support > min_support:
        reliability = n12_support / n1_support
    else:
        reliability = 0
    return reliability


def interestingness(item_number1, item_number2):
    n1_support = support1(item_number1)
    n2_support = support1(item_number2)
    n12_support = support2(item_number1, item_number2)
    if n2_support > min_support:
        interest = n12_support / (n1_support * n2_support)
    else:
        interest = 0
    return interest


def recommend(product_name, skin_type, flag):
    global recommend_result
    recommend_result = []
    if flag == 1:
        i = 0
        Goods_n = len(Goods)
        while i < Goods_n:
            if Goods[i][3] == skin_type and Goods[i][1] != product_name:
                reliability = confidence_level(item_number, Goods[i][0])
                interest = interestingness(item_number, Goods[i][0])
                if reliability > min_reliability and interest > min_interest:
                    recommend_result.append(Goods[i])
            i = i + 1
    elif flag == 0:
        notice = '你想买的产品不适合你的身体状况哦！'
        show_listbox.insert(tk.END, notice)
        notice = '我们为您推荐了以下适合您的食物：'
        show_listbox.insert(tk.END, notice)
        i = 0
        Goods_n = len(Goods)
        while i < Goods_n:
            if Goods[i][3] == skin_type:
                if support1(Goods[i][0]) > min_support:
                    recommend_result.append(Goods[i])
            i = i + 1

    for i in recommend_result:
        show_listbox.insert(tk.END, i)


# 连接数据表，调用数据分别存储在列表User、Goods、Buy中
#conn = pymssql.connect(host='localhost', user='sa', password='lzy123456', database='CRM_db', charset='UTF8')
conn = pymssql.connect(server='LAPTOP-UQK4UCE9', database='CRM_db',charset='UTF8')
cursor = conn.cursor()

sql_select1 = "SELECT * FROM User1"
cursor.execute(sql_select1)
User = cursor.fetchall()

sql_select2 = "SELECT * FROM Goods"
cursor.execute(sql_select2)
Goods = cursor.fetchall()

sql_select3 = "SELECT * FROM Buy"
cursor.execute(sql_select3)
Buy = cursor.fetchall()

sql_select4 = "SELECT goodsName FROM Goods"
cursor.execute(sql_select4)
all_Goods_name = cursor.fetchall()

conn.commit()
conn.close()

# N为用户总数
N = len(User)

root = tk.Tk()
root.wm_title("CRM")
sw = root.winfo_screenwidth()
sh = root.winfo_screenheight()
ww = 800
wh = 700
x = (sw - ww) / 2
y = (sh - wh) / 2
root.geometry("%dx%d+%d+%d" % (ww, wh, x, y))

# 标题
label1 = tk.Label(root, text="CRM系统")

# #用label.pack()会使该布局无效
label1.place(width=200, height=30, x=280, y=20)

# 选择bmi
label2 = tk.Label(root, text="请选择你的体型", fg="#DAA520")
label2.place(x=20, y=100, width=150, height=30)

# bmi
type_of_skin = ['极度偏瘦（BMI < 16.0）', '偏瘦（16.0 ≤ BMI < 18.5）', '正常体重（18.5 ≤ BMI < 24.9）', ' 超重（25.0 ≤ BMI < 29.9）', '肥胖（30.0 ≤ BMI < 35.0）', '极度肥胖（BMI ≥ 35.0）']
the_product_you_want = tk.ttk.Combobox(root, value=type_of_skin)
# the_product_you_want.pack(padx=5, pady=10)
the_product_you_want.place(x=150, y=100, width=150, height=30)

# 商品选择
label3 = tk.Label(root, text="请选择你想买的商品", fg="#DAA520")
label3.place(x=350, y=100, width=150, height=30)

# 商品
the_order_you_want = tk.ttk.Combobox(root, value=all_Goods_name)
the_order_you_want.place(x=500, y=100, width=150, height=30)

# “搜索”按钮
b1 = tk.Button(root, text="搜索", command=Good_detail, activebackground="#2082AA", fg="#DAA520", bg="#FFEBCD")
b1.place(x=330, y=160, width=100, height=30)

# 选择的商品详情
label5 = tk.Label(root, text="食品详情", fg="#DAA520")
label5.place(x=120, y=200, width=150, height=30)

# 显示商品详情界面
Label7 = tk.Label(root, text="商品名称：", fg="#DAA520")
Label7.place(x=30, y=240, width=150, height=30)
show_product_name = tk.Entry(root, width=20, font=('宋体', '10'))
show_product_name.place(x=150, y=250)

Label8 = tk.Label(root, text="商品价格：", fg="#DAA520")
Label8.place(x=30, y=340, width=150, height=30)
show_product_price = tk.Entry(root, width=20, font=('宋体', '10'))
show_product_price.place(x=150, y=350)

Label9 = tk.Label(root, text="适合体型：", fg="#DAA520")
Label9.place(x=30, y=440, width=150, height=30)
show_product_skin = tk.Entry(root, width=20, font=('宋体', '10'))
show_product_skin.place(x=150, y=450)

Label10 = tk.Label(root, text="商品图片：", fg="#DAA520")
Label10.place(x=30, y=540, width=150, height=30)

# 推荐的商品
label6 = tk.Label(root, text="可能适合你的产品", fg="#DAA520")
label6.place(x=520, y=200, width=150, height=30)

# 推荐的商品详情界面
show_listbox = tk.Listbox(root)
show_listbox.place(x=410, y=240, width=340, height=400)

root.mainloop()
