import tkinter as tk
import requests
import re
import time

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
}

def baidu(company):
    url = 'http://www.baidu.com/s?tn=news&rtt=1&wd=' + company
    res = requests.get(url, headers=headers, timeout=10).text
    p_href = '<h3 class="news-title_1YtI1 "><a href="(.*?)"'
    href = re.findall(p_href, res, re.S)
    p_title = '<h3 class="news-title_1YtI1 ">.*?>(.*?)</a>'
    title = re.findall(p_title, res, re.S)
    p_date = '<span class="c-color-gray2 c-font-normal c-gap-right-xsmall" .*?>(.*?)</span>'
    date = re.findall(p_date, res)
    p_source = '<span class="c-color-gray" .*?>(.*?)</span>'
    source = re.findall(p_source, res)

    result_text = ""
    for i in range(len(date)):
        title[i] = title[i].strip()
        title[i] = re.sub('<.*?>', '', title[i])
        if ('小时' in date[i]) or ('分钟' in date[i]):
            date[i] = time.strftime("%Y-%m-%d")
        else:
            date[i] = date[i]
        result_text += str(i + 1) + '.' + title[i] + '(' + date[i] + '-' + source[i] + ')\n' + href[i] + '\n\n'

    return result_text

def on_button_click():
    company_name = entry.get()
    result = baidu(company_name)
    result_text.delete(1.0, tk.END)
    result_text.insert(tk.END, result)

root = tk.Tk()
root.title("新闻搜索徐昊博21013134")

label = tk.Label(root, text="请输入要搜索的公司名称：")
label.pack(pady=10)

entry = tk.Entry(root, width=30)
entry.pack(pady=5)

button = tk.Button(root, text="搜索", command=on_button_click)
button.pack(pady=5)

result_text = tk.Text(root, width=80, height=20)
result_text.pack(pady=10)

root.mainloop()
