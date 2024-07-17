from random import *
counts={}#创建一个空字典
with open("student.csv", 'r') as fobj:
    for i in fobj:
        if i[:2]=="学号":
            continue
        i=i. strip()
        code, name=i. split(",")
        counts[name]=randint(30,100)
import matplotlib. pyplot as plt
from wordcloud import WordCloud
from imageio.v2 import imread
pic = imread('star2.png')
wc=WordCloud(mask=pic,font_path='msyh.ttc',  #中文字体
repeat=False, #内容是否可以重复
background_color='white', #设置背景颜色
max_words=100,           #设置最大词数
max_font_size=20,     #设置字体最大值
min_font_size=2,     #设置字体最小值
random_state=50,       #设置有配色方案
scale=10)                      #按照比例进行放大画布
wc.generate_from_frequencies(counts)
plt.imshow(wc)
plt.show()