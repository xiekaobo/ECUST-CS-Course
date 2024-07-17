#include"shell.h"
//打印命令提示符
void printPrompt()
{
    size_t offset;
    char tmpStr[100];

    // 打印shell标头
    printf("\033[38;5;34m\033[1m[SHELL]\033[m"); // 蓝色

    // 用户名和主机名
    offset = 0; 
    getlogin_r(tmpStr + offset, MAX_PROMPT_LEN - offset);//获取用户名
    offset += strlen(tmpStr + offset);
    tmpStr[offset++] = '@';
    gethostname(tmpStr + offset, MAX_PROMPT_LEN - offset);//获取主机名
    offset += strlen(tmpStr + offset);
    tmpStr[offset] = '\0';
    printf("\033[38;5;30m\033[1m%s\033[m", tmpStr); 
    printf(":");

    // 打印当前目录
    offset = 0;
    getcwd(tmpStr + offset, MAX_PROMPT_LEN - offset);
    offset += strlen(tmpStr + offset);
    tmpStr[offset] = '\0';
    printf("\e[1;34m%s\033[m", tmpStr);

    // 根据用户权限打印提示符
    printf((!geteuid()) ? "# " : "$ ");
}