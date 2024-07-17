import requests
import re

url = 'https://www.fecn.net/'
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
