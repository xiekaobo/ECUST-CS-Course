//实现cat指令
//cat filename 或路径，如： cat /etc/passwd

#include "shell.h"

void cat(char **argv) {
    // 检查是否提供了文件名
    if (argv[1] == NULL) {
        fprintf(stderr, "Usage: cat filename\n");
        return;
    }

    // 遍历所有提供的文件名
    for (int i = 1; argv[i] != NULL; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            perror("fopen");
            continue;
        }

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            fputs(buffer, stdout);
        }

        fclose(file);
        printf("\n");
    }
}