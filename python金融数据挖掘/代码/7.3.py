
import requests
import re

# 定义校区对应的链接
urls = {
    "奉贤校区": "https://xiaoban.ecust.edu.cn/2021/0928/c10391a133815/page.htm",
    "徐汇校区": "https://xiaoban.ecust.edu.cn/2021/0928/c10391a133819/page.htm",
    "金山校区": "https://xiaoban.ecust.edu.cn/2021/0928/c10391a133814/page.htm"
}

# 用户选择校区
print("请选择要爬取的校区：")
for idx, campus in enumerate(urls.keys(), start=1):
    print(f"{idx}. {campus}")
choice = int(input("请输入序号："))


# 获取用户选择的校区链接
campus_name = list(urls.keys())[choice - 1]
url = urls[campus_name]

r = requests.get(url)
r.encoding = r.apparent_encoding
paper = r.text
cond = '<img src="(.*?\.jpg)"'  # 修正正则表达式以匹配图像URL
urls = re.findall(cond, paper)

print(urls)

for x, img_url in enumerate(urls):
    img_url = url + img_url  # 使用完整的图像URL
    r = requests.get(img_url)
    with open(f"D:\\result\\result{x}.jpg", 'wb') as fobj:  # 使用f-string格式化文件名
        fobj.write(r.content)