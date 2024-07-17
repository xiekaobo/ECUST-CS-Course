import tkinter as tk
from tkinter import messagebox
import requests
from bs4 import BeautifulSoup
import pandas as pd
import pymysql
import re
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from xgboost import XGBRegressor
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号 '-' 显示为方块的问题

def fetch_data():
    url = entry_url.get()
    response = requests.get(url)
    soup = BeautifulSoup(response.content, 'html.parser')

    # 查找包含GDP数据的表格
    table = soup.find('table', {'class': 'table'})
    rows = table.find_all('tr')

    gdp_data = []
    for row in rows[2:]:  # 跳过表头行
        cols = row.find_all('td')
        if len(cols) < 2:
            continue
        year = cols[0].text.strip()
        gdp_text = cols[1].text.strip()

        # 使用正则表达式提取括号内的数值
        gdp_match = re.search(r'\(([\d,]+)\)', gdp_text)
        if gdp_match:
            gdp = gdp_match.group(1).replace(',', '')
            gdp_data.append((int(year), float(gdp)))

    global df
    df = pd.DataFrame(gdp_data, columns=['year', 'gdpnum'])
    messagebox.showinfo("成功", "数据爬取并清洗成功！")


def save_to_db():
    db = pymysql.connect(
        host="localhost",
        user="root",
        password="Xhb200302%",
        database="finance"
    )

    cursor = db.cursor()

    for index, row in df.iterrows():
        cursor.execute("REPLACE INTO gdp (year, gdpnum) VALUES (%s, %s)", (row['year'], row['gdpnum']))

    db.commit()
    cursor.close()
    db.close()
    messagebox.showinfo("成功", "数据保存到数据库成功！")


def predict_gdp():
    db = pymysql.connect(
        host="localhost",
        user="root",
        password="Xhb200302%",
        database="finance"
    )

    cursor = db.cursor()
    cursor.execute("SELECT * FROM gdp")
    data = cursor.fetchall()

    df = pd.DataFrame(data, columns=['year', 'gdpnum'])

    X = df[['year']]
    y = df['gdpnum']

    # 标准化数据
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)

    X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

    # 使用XGBoost回归模型
    model = XGBRegressor(n_estimators=100, random_state=42)
    model.fit(X_train, y_train)

    future_years = pd.DataFrame({'year': range(2023, 2030)})
    future_years_scaled = scaler.transform(future_years)
    predictions = model.predict(future_years_scaled)

    plt.plot(df['year'], df['gdpnum'], label='实际值')
    plt.plot(future_years['year'], predictions, label='预测值', linestyle='--')
    plt.xlabel('年份')
    plt.ylabel('GDP')
    plt.legend()
    plt.show()
    cursor.close()
    db.close()

app = tk.Tk()
app.title("GDP数据爬取器")

label_url = tk.Label(app, text="URL:")
label_url.pack()
entry_url = tk.Entry(app)
entry_url.pack()

btn_fetch = tk.Button(app, text="爬取数据", command=fetch_data)
btn_fetch.pack()

btn_save = tk.Button(app, text="保存到数据库", command=save_to_db)
btn_save.pack()

btn_predict = tk.Button(app, text="预测GDP", command=predict_gdp)
btn_predict.pack()

app.mainloop()
