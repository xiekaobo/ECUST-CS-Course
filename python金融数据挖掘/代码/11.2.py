import tkinter as tk
from tkinter import filedialog
import pandas as pd
import matplotlib.pyplot as plt
# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号 '-' 显示为方块的问题

class FinancialDataApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Financial Data App")

        self.data = None

        self.load_button = tk.Button(root, text="读入数据", command=self.load_data)
        self.load_button.pack(pady=10)

        self.scatter_button = tk.Button(root, text="画散点图", command=self.plot_scatter)
        self.scatter_button.pack(pady=10)

        self.bar_button = tk.Button(root, text="画柱形图", command=self.plot_bar)
        self.bar_button.pack(pady=10)

    def load_data(self):
        file_path = filedialog.askopenfilename()
        if file_path:
            self.data = pd.read_csv(file_path)
            print(f"数据已加载: {file_path}")

    def plot_scatter(self):
        if self.data is not None:
            plt.figure()
            # 设置字体为支持中文的字体

            plt.scatter(self.data['x'], self.data['y'])
            plt.xlabel('X 轴')
            plt.ylabel('Y 轴')
            plt.title('散点图徐昊博21013134')
            plt.show()
        else:
            print("请先读入数据")

    def plot_bar(self):
        if self.data is not None:
            plt.figure()
            plt.bar(self.data['x'], self.data['y'])
            plt.xlabel('X 轴')
            plt.ylabel('Y 轴')
            plt.title('柱形图徐昊博21013134')
            plt.show()
        else:
            print("请先读入数据")

if __name__ == "__main__":
    root = tk.Tk()
    app = FinancialDataApp(root)
    root.mainloop()
