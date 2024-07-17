//grep实现
//

#include "shell.h"


// grep 函数：在给定文件中搜索匹配的模式
void grep(const char *pattern, const char *filename) {
    FILE *file = fopen(filename, "r");  // 打开文件以供读取
    if (file == NULL) {  // 如果文件无法打开，输出错误信息
        perror("fopen");
        return;
    }

    char line[1024];  // 用于存储每行内容的缓冲区
    int line_number = 1;  // 行号，从1开始

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, pattern) != NULL) {  // 如果当前行包含模式
            printf("%s:%d: %s", filename, line_number, line);  // 打印文件名、行号和匹配的行
        }
        line_number++;  // 增加行号
    }

    fclose(file);  // 关闭文件
}

// grep_command 函数：解析命令行参数并调用 grep 函数
void grep_command(char **argv) {
    if (argv[1] == NULL || argv[2] == NULL) {  // 如果缺少参数，输出用法信息
        fprintf(stderr, "Usage: grep PATTERN FILE\n");
        return;
    }

    const char *pattern = argv[1];  // 获取模式
    for (int i = 2; argv[i] != NULL; i++) {  // 遍历所有提供的文件名
        grep(pattern, argv[i]);  // 调用 grep 函数
    }
}