//实现了type指令，可以区分外置指令、内置指令、fake指令

#include"shell.h"


// 检查命令类型的函数
void type(char **argv) {
    if (argv[1] == NULL) {
        fprintf(stderr, "type: 缺少操作数\n");
        return;
    }

    for (int i = 1; argv[i] != NULL; i++) {
        char *cmd = argv[i];
        char *alias_cmd[256]; //定义别名数组存储别名

        // 检查是否为内建命令
        if (strcmp(cmd, "alias") == 0 || strcmp(cmd, "unalias") == 0 || strcmp(cmd, "ls") == 0 || strcmp(cmd, "type") == 0 || strcmp(cmd,"history")==0 ||strcmp(cmd, "cat")==0 || strcmp(cmd,"grep")==0 || strcmp(cmd,"echo")==0 || strcmp(cmd,"pwd")==0) {
            printf("%s 是一个内建命令\n", cmd);
            continue;
        }

        // 检查是否为别名
        if (search_alias(cmd, alias_cmd)) {  
            printf("%s 被别名为 '%s'\n", cmd , alias_cmd);
            continue;
        }

        // 检查是否为外部命令，检查系统中是否有 PATH 环境变量。如果没有这个变量，则表示无法获取系统路径列表，因此直接输出命令未找到。
        char *path = getenv("PATH");
        if (path == NULL) {
            printf("%s 未找到\n", cmd);
            continue;
        }
        //具体遍历 PATH 环境变量中的各个目录路径，检查每个路径下是否存在指定的命令，并且该命令是否可执行。如果找到命令，就输出其路径；否则，继续检查下一个路径。
        // 创建一个临时变量保存 PATH
        char *path_dup = strdup(path);
        char *token = strtok(path_dup, ":");
        int found = 0;

        while (token != NULL) {
            char fullpath[1024];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", token, cmd);
            if (access(fullpath, X_OK) == 0) {
                printf("%s 是外置命令 %s\n", cmd, fullpath);
                found = 1;
                break;
            }
            token = strtok(NULL, ":");
        }

        free(path_dup);

        if (!found) {
            printf("%s 未找到\n", cmd);
        }
    }
}