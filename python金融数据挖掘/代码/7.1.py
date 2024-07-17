import requests
import re
url="http://www.caijing.com.cn"
html=requests. get(url)
html. encoding=html. apparent_encoding
data=html. text
#print(data)
reg='<li><a href="(.*?)" target="_blank">(.*?)</a></li>'
urls=re.findall(reg, data)
#print(urls)
fobj=open("result.csv",'w', encoding="gb2312")
for titu in urls:
    fobj.write(titu[0]+","+titu[1]+'\n')
fobj.close()