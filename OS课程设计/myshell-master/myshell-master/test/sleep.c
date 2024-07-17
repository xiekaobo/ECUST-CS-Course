#include <stdio.h>
#include <unistd.h>  // 包含sleep函数

int main() {
    sleep(5);  // 延迟5秒
    printf("\n延迟5s后输出 abc\n");  // 输出abc
    return 0;
}

