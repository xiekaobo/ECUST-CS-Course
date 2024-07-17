import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号 '-' 显示为方块的问题

# 2月花销
expenses_feb = {
    'Food': 200,
    'Transport': 50,
    'Entertainment': 75,
    'Shopping': 100,
    'Others': 50
}

# 3月花销
expenses_mar = {
    'Food': 180,
    'Transport': 60,
    'Entertainment': 90,
    'Shopping': 120,
    'Others': 70
}

# 4月花销
expenses_apr = {
    'Food': 210,
    'Transport': 55,
    'Entertainment': 85,
    'Shopping': 130,
    'Others': 60
}

# 绘制饼图函数
def plot_expenses(expenses, month):
    labels = list(expenses.keys())
    sizes = list(expenses.values())
    explode = (0.1, 0, 0, 0, 0)  # 使食物的部分稍微凸出

    plt.figure(figsize=(7, 7))
    plt.pie(sizes, explode=explode, labels=labels, autopct='%1.1f%%', shadow=True, startangle=140)
    plt.title(f'Expenses for {month}')
    plt.show()

# 绘制2月、3月和4月的花销饼图
plot_expenses(expenses_feb, '徐昊博21013134二月')
plot_expenses(expenses_mar, '徐昊博21013134三月')
plot_expenses(expenses_apr, '徐昊博21013134四月')
