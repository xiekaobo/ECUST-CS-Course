#include"shell.h"
//删除一个alias
int delete_alias(const char *nickname) {
    FILE *file = fopen(ALIAS_FILE_PATH, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    FILE *temp = fopen(ALIAS_FILE_TMP_PATH, "w");
    if (temp == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char a[MAX_LINE_LENGTH], b[MAX_LINE_LENGTH];
        if (sscanf(line, "%s %s", a, b) == 2) {
            if (strcmp(a, nickname) == 0) {
                found = 1;
                continue; // Skip this line
            }
        }
        fputs(line, temp);
    }

    fclose(file);
    fclose(temp);

    // Replace the original file with the modified file
    if (found) {
        remove(ALIAS_FILE_PATH);
        rename(ALIAS_FILE_TMP_PATH, ALIAS_FILE_PATH);
        return 1;
    } else {
        remove(ALIAS_FILE_TMP_PATH);
        return 0;
    }
}

void unalias(char *nickname){
    if(delete_alias(nickname)!=1)
    {
        printf("未找到该别名\n");
        
    }
}