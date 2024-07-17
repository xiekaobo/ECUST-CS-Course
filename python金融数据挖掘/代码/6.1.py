import re
#徐昊博21013134
def check_email(email):
    pattern = r'^[a-zA-Z0-9]{1,10}@[a-zA-Z0-9]{1,10}\.(com|org)$'
    return re.match(pattern, email, re.IGNORECASE) is not None

# 输入测试串
test_email = input("请输入E-mail地址：")

if check_email(test_email):
    print("符合设定规则。")
else:
    print("不符合设定规则。")
