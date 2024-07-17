import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# 读取CSV文件
df = pd.read_csv('financialdata.csv')

# 设置图形风格
sns.set(style="whitegrid")

# 创建一个散点图
plt.figure(figsize=(10, 6))

# 使用Seaborn的scatterplot函数，根据Category字段进行分类并绘制不同颜色的散点图
sns.scatterplot(data=df, x='Value1', y='Value2', hue='Category', palette='Set2', s=100)

# 设置图形标题和标签
plt.title('Scatter Plot of Financial Data by Category')
plt.xlabel('Value1')
plt.ylabel('Value2')

# 显示图例
plt.legend(title='Category21013134')

# 显示图形
plt.show()
