import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
import matplotlib.pyplot as plt

# 读取CSV文件
data = pd.read_csv('info.csv')

# 清洗数据，去除多余的空格或特殊字符
data.columns = data.columns.str.strip()
data['Height'] = data['Height'].astype(float)
data['Weight'] = data['Weight'].astype(float)
data['Type'] = data['Type'].str.strip()

# 提取特征和标签
X = data[['Height', 'Weight']].values
y = data['Type'].values

# 输入个人信息
height = float(input("请输入您的身高(cm): "))
weight = float(input("请输入您的体重(kg): "))

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 逻辑回归
logistic_model = LogisticRegression()
logistic_model.fit(X_train, y_train)

# 决策树
tree_model = DecisionTreeClassifier()
tree_model.fit(X_train, y_train)

# KNN
knn_model = KNeighborsClassifier(n_neighbors=5)
knn_model.fit(X_train, y_train)

# 将个人信息转换为模型输入格式
user_data = np.array([[height, weight]])

# 使用不同的模型进行预测
logistic_pred = logistic_model.predict(user_data)[0]
tree_pred = tree_model.predict(user_data)[0]
knn_pred = knn_model.predict(user_data)[0]

# 输出预测结果
print(f"逻辑回归预测结果: {logistic_pred}")
print(f"决策树预测结果: {tree_pred}")
print(f"KNN预测结果: {knn_pred}")

# 预测测试集
logistic_test_pred = logistic_model.predict(X_test)
tree_test_pred = tree_model.predict(X_test)
knn_test_pred = knn_model.predict(X_test)

# 计算准确率
logistic_accuracy = accuracy_score(y_test, logistic_test_pred)
tree_accuracy = accuracy_score(y_test, tree_test_pred)
knn_accuracy = accuracy_score(y_test, knn_test_pred)

print(f"逻辑回归准确率: {logistic_accuracy:.2f}")
print(f"决策树准确率: {tree_accuracy:.2f}")
print(f"KNN准确率: {knn_accuracy:.2f}")

# 显示结果
fig, ax = plt.subplots()
algorithms = ['Logistic Regression', 'Decision Tree', 'KNN']
predictions = [logistic_pred, tree_pred, knn_pred]
accuracies = [logistic_accuracy, tree_accuracy, knn_accuracy]

# 绘制预测结果
ax.barh(algorithms, accuracies, color=['blue', 'green', 'orange'])
ax.set_xlabel('Accuracy')
ax.set_title('Accuracy of Different Algorithms')

# 显示准确率
for i, v in enumerate(accuracies):
    ax.text(v + 0.01, i, f'{v:.2f}', color='black', va='center')

plt.show()
