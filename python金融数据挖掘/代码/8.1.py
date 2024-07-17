import requests
from bs4 import BeautifulSoup
import pymysql

# 连接到MySQL数据库
conn = pymysql.connect(
    host="localhost",  # MySQL服务器主机
    user="root",  # 数据库用户名
    password="Xhb200302%",  # 数据库密码
    database="finance",  # 数据库名
    port=3306
)
cursor = conn.cursor()

# 创建一个表来存储数据
cursor.execute('''CREATE TABLE IF NOT EXISTS financial_data
              (id INT AUTO_INCREMENT PRIMARY KEY, title VARCHAR(255), link VARCHAR(255))''')

# 选择一个金融网站
url = 'http://www.caijing.com.cn'

# 发送GET请求并解析HTML
response = requests.get(url, headers={'Content-Type': 'text/html; charset=utf-8'})
soup = BeautifulSoup(response.text, 'html.parser')

# 找到所有的标题链接
for a in soup.find_all('a', href=True):
    title = a.get_text(strip=True).encode('iso-8859-1').decode('utf-8', errors='ignore')
    link = a['href']
    print((title, link))
    # 如果链接不是以'http'或'https'开头，则可能是相对链接，需要拼接完整链接
    if not link.startswith(('http://', 'https://')):
        link = url + link

    # 插入到数据库中
    cursor.execute('INSERT INTO financial_data (title, link) VALUES (%s, %s)', (title, link))

# 提交更改并关闭数据库连接
conn.commit()
conn.close()
