import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# 读取CSV文件
df = pd.read_csv('student.csv')

# 提取需要的列
heights = df['Height']
weights = df['Weight']

# 设置图形风格
sns.set(style="whitegrid")

# 创建一个2x2的子图
fig, axes = plt.subplots(2, 2, figsize=(14, 10))

# 绘制身高的直方图
sns.histplot(heights, bins=10, kde=False, ax=axes[0, 0])
axes[0, 0].set_title('Height Histogram21013134')
axes[0, 0].set_xlabel('Height')
axes[0, 0].set_ylabel('Frequency')

# 绘制体重的直方图
sns.histplot(weights, bins=10, kde=False, ax=axes[0, 1])
axes[0, 1].set_title('Weight Histogram')
axes[0, 1].set_xlabel('Weight')
axes[0, 1].set_ylabel('Frequency')

# 绘制身高的箱型图
sns.boxplot(x=heights, ax=axes[1, 0])
axes[1, 0].set_title('Height Boxplot')
axes[1, 0].set_xlabel('Height')

# 绘制体重的箱型图
sns.boxplot(x=weights, ax=axes[1, 1])
axes[1, 1].set_title('Weight Boxplot')
axes[1, 1].set_xlabel('Weight')

# 调整子图布局
plt.tight_layout()

# 显示图形
plt.show()
