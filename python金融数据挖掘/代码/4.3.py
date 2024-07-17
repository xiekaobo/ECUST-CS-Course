import jieba
import matplotlib.pyplot as plt
from wordcloud import WordCloud
from imageio.v2 import imread
fobj=open("python.txt","r",encoding="utf-8")
txt=fobj.read()
words=jieba.lcut(txt)
counts={}
excludes=set()
with open("中文停用词.txt","r",encoding="utf-8") as fobj:
    for i in fobj:
        i=i. strip()
        excludes. add(i)
for word in words:
    if len(word)==1:
        continue
    elif word in excludes:
        continue
    else:
        counts[word]=counts. get(word,0)+1
items = list(counts.items())
items.sort(key=lambda x: x[1], reverse=True)
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
for i in range(10):
    word, count = items[i]
    plt.bar(word, count)
plt.show()