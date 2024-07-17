import pdfplumber
import jieba
import matplotlib.pyplot as plt
from wordcloud import WordCloud

# 打开PDF文件
with pdfplumber.open("2.pdf") as pdf:
    full_text = ""
    for page in pdf.pages:
        # 提取每一页的文本
        text = page.extract_text()
        if text:
            full_text += text

# 分词
words = jieba.lcut(full_text)
counts = {}
excludes = set()

# 读取停用词
with open("stop.txt", "r", encoding="utf-8") as fobj:
    for i in fobj:
        i = i.strip()
        excludes.add(i)

# 统计词频
for word in words:
    if len(word) == 1:
        continue
    elif word in excludes:
        continue
    else:
        counts[word] = counts.get(word, 0) + 1

wordcloud = WordCloud(font_path='simhei.ttf',
                      width=800,
                      height=400,
                      background_color='white',
                      max_words=200)
# 生成词云
wc = wordcloud.generate_from_frequencies(counts)

# 显示词云
plt.imshow(wc, interpolation='bilinear')
plt.axis('off')  # 不显示坐标轴
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.title("徐昊博21013134")
plt.show()

# 排序并选取前10个单词
items = list(counts.items())
items.sort(key=lambda x: x[1], reverse=True)
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
for i in range(10):
    word, count = items[i]
    plt.bar(word, count)
plt.title("徐昊博21013134")
plt.show()
