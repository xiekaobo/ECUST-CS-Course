import tkinter as tk
from tkinter import filedialog, messagebox
import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号 '-' 显示为方块的问题

def browse_file():
    file_path = filedialog.askopenfilename(filetypes=[("CSV files", "*.csv")])
    file_entry.insert(0, file_path)


def analyze_data():
    file_path = file_entry.get()
    try:
        global analyzed_data, original_file_path
        original_file_path = file_path
        data = pd.read_csv(file_path)
        # 计算涨幅
        data['price_change'] = ((data['pricehigh'] - data['pricelow']) / data['pricelow']) * 100

        # 设置图标样式
        plt.figure(figsize=(10, 6))
        plt.bar(data['name'], data['price_change'], color='skyblue')
        plt.xlabel('股票名字')
        plt.ylabel('股票增长率(%)')
        plt.title('美股市涨幅情况')
        plt.xticks(rotation=45)
        plt.tight_layout()
        plt.show()

        # 设计消息提示框
        messagebox.showinfo("分析完成", "分析完成，点击查看")
        global analyzed_data
        analyzed_data = data
        print(analyzed_data)
    except Exception as e:
        messagebox.showerror("Error", str(e))


def save_results():
    if analyzed_data is not None:
        try:
            with open(original_file_path, 'w', newline='') as file:
                analyzed_data.to_csv(file, index=False)
            messagebox.showinfo("成功", "分析数据已经成功写回！")
        except Exception as e:
            messagebox.showerror("错误r", str(e))
    else:
        messagebox.showerror("错误", "没有数据可以写回")


# 界面初始化
root = tk.Tk()
root.title("金融数据分析-徐昊博21013134")

# 输入文档地址
file_label = tk.Label(root, text="输入文件名")
file_label.grid(row=0, column=0, padx=10, pady=10)
file_entry = tk.Entry(root, width=50)
file_entry.grid(row=0, column=1, padx=10, pady=10)

# 查找文档按钮
browse_button = tk.Button(root, text="浏览", command=browse_file)
browse_button.grid(row=0, column=2, padx=10, pady=10)

# 分析按钮
analyze_button = tk.Button(root, text="分析", command=analyze_data)
analyze_button.grid(row=1, column=1, pady=20)

# 保存数据按钮
save_button = tk.Button(root, text="保存结果", command=save_results)
save_button.grid(row=2, column=1, pady=20)

analyzed_data = None

root.mainloop()
