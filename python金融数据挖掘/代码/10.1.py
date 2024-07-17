import tkinter as tk
import time

def update_clock():
    now = time.strftime("%H:%M:%S")
    clock_label.config(text=now)
    clock_label.after(1000, update_clock)  # 每隔1秒更新时钟

root = tk.Tk()
root.title("动态时钟徐昊博21013134")

clock_label = tk.Label(root, font=("Arial", 24))
clock_label.pack(padx=200, pady=200)

update_clock()  # 初始更新时钟

root.mainloop()
