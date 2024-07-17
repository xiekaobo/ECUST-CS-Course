def fib(n):
    if n <= 2:
        return 1
    else:
        return fib(n-1)+fib(n-2)
print("徐昊博21013134")
for i in range(1,31):
    print(fib(i))