import jieba
from wordcloud import WordCloud
import matplotlib.pyplot as plt
from collections import Counter

# 从文件中读取中文文本内容
with open('gov.txt', 'r', encoding='utf-8') as file:
    text = file.read()

# 使用jieba进行中文分词
words = jieba.cut(text)

# 过滤掉单个字和停用词
filtered_words = [word for word in words if len(word) > 1]

# 进行词频统计
word_counts = Counter(filtered_words)

# 生成词云图
wordcloud = WordCloud(font_path='simhei.ttf', width=800, height=400, background_color='white').generate_from_frequencies(word_counts)

# 显示词云图
plt.figure(figsize=(10, 5))
plt.imshow(wordcloud, interpolation='bilinear')
plt.axis('off')
plt.show()
