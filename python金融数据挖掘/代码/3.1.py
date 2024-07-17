import statistics

# 定义数据列表
data = [32, 45, 67, 12, 89, 23, 56, 78, 91, 54]

# 1. 实现数据的从大到小排序，输出排序结果
sorted_data = sorted(data, reverse=True)
print("数据从大到小排序结果：", sorted_data)

# 2. 计算最大值、最小值、平均值和众数
max_value = max(data)
min_value = min(data)
mean_value = statistics.mean(data)
mode_value = statistics.mode(data)

print("最大值：", max_value)
print("最小值：", min_value)
print("平均值：", mean_value)
print("众数：", mode_value)
