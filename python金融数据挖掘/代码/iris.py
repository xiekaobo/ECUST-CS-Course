import pandas as pd
import numpy as np
from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
import seaborn as sns

# 加载鸢尾花数据集
iris = load_iris()
data = iris.data
target = iris.target
target_names = iris.target_names

# 将数据转换为DataFrame
df = pd.DataFrame(data, columns=iris.feature_names)
df['target'] = target

# 数据标准化
scaler = StandardScaler()
data_scaled = scaler.fit_transform(data)

# 使用K-means算法进行聚类
kmeans = KMeans(n_clusters=3, random_state=42)
kmeans.fit(data_scaled)
clusters = kmeans.labels_

# 将聚类结果加入到DataFrame
df['cluster'] = clusters

# 可视化聚类结果
plt.figure(figsize=(10, 6))
sns.scatterplot(data=df, x='sepal length (cm)', y='sepal width (cm)', hue='cluster', palette='viridis', style='target')
plt.title('K-means Clustering of Iris Data (Sepal Length vs Sepal Width)')
plt.xlabel('Sepal Length (cm)')
plt.ylabel('Sepal Width (cm)')
plt.legend(title='Cluster')
plt.show()

plt.figure(figsize=(10, 6))
sns.scatterplot(data=df, x='petal length (cm)', y='petal width (cm)', hue='cluster', palette='viridis', style='target')
plt.title('K-means Clustering of Iris Data (Petal Length vs Petal Width)')
plt.xlabel('Petal Length (cm)')
plt.ylabel('Petal Width (cm)')
plt.legend(title='Cluster')
plt.show()
