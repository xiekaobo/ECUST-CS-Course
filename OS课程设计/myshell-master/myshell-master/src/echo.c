//echo function
//实现了 echo $HOME /$USER/ $PATH 等
//      echo  字符串/filename
//      echo -n [...] 不换行输出
//      \n \t \\ \' \"
  
#include "shell.h"

// 解析并处理 $VAR 形式的变量
void parse_variables(char *str, char *result) {
    char *p = str;
    char *r = result;
    while (*p) {
        if (*p == '$') {
            p++;
            // 获取变量名
            char var_name[256];
            char *v = var_name;
            while (*p && (isalnum((unsigned char)*p) || *p == '_')) {
                *v++ = *p++;
            }
            *v = '\0';
            // 获取环境变量值
            char *var_value = getenv(var_name);
            if (var_value) {
                while (*var_value) {
                    *r++ = *var_value++;
                }
            }
        } else if (*p == '\\') {  // 检查是否遇到转义字符'\'
            p++;  // 移动到转义字符的下一个字符
            switch (*p) {  // 处理不同的转义字符
                case 'n':  // 处理 \n
                    *r++ = '\n';  // 在结果字符串中添加换行符
                    break;
                case 't':  // 处理 \t
                    *r++ = '\t';  // 在结果字符串中添加制表符
                    break;
                case '\\':  // 处理 '\\'
                    *r++ = '\\';  // 在结果字符串中添加反斜杠
                    break;
                case '\"':  // 处理 \"
                    *r++ = '\"';  // 在结果字符串中添加双引号
                    break;
                case '\'':  // 处理 \'
                    *r++ = '\'';  // 在结果字符串中添加单引号
                    break;
                default:  // 处理其他字符
                    *r++ = '\\';  // 在结果字符串中添加反斜杠
                    *r++ = *p;  // 在结果字符串中添加当前字符
            }
            p++;  // 移动到下一个字符
        } else 
        {
            *r++ = *p++;
        }
    }
    *r = '\0';
}

void echo(char **argv){
    int i = 1;
    int newline = 1;

    // 检查 -n 选项
    if (argv[i] && strcmp(argv[i], "-n") == 0) {
        newline = 0;
        i++;
    }

    while (argv[i]) {
        char result[1024];
        parse_variables(argv[i], result);
        printf("%s", result);
        if (argv[i + 1]) {
            printf(" ");
        }
        i++;
    }

    if (newline) {
        printf("\n");
    }

}