#include"shell.h"

//设置alias别名
void do_alias(char* cmd,char *nickname)
{
    //将别名保存在文件中
    FILE *file;
    file=fopen(ALIAS_FILE_PATH,"a");//用追加的方式打开文件
    if (file == NULL) {
        perror("Error opening file");
    }
    // 将两个字符串写入文件
    fprintf(file, "%s %s\n", nickname, cmd);
    // 关闭文件
    fclose(file);
}
//根据别名查找别名对应的指令，如果查找到就返回1，否则返回0
/*C   O   N   F   I   R   M*/
int search_alias(char *nickname,char *cmd)
{
    FILE *file = fopen(ALIAS_FILE_PATH, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    char line[MAX_LINE_LENGTH];
    char a1[MAX_STRING_LENGTH];
    char a2[MAX_STRING_LENGTH];
     // 逐行读取文件
    while (fgets(line, sizeof(line), file)) {
        // 使用 sscanf 解析每行的两个字符串
        if (sscanf(line, "%s %s", a1, a2) == 2) {
            // 比较 a1 与 nickname 是否一致
            if (strcmp(a1, nickname) == 0) {
                // 将 cmd 设置为 a2
                strcpy(cmd, a2);
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}
//分割alias字符串
/*C   O   N   F   I   R   M*/
void split_alias(const char *input, char *name, char *command) {
    const char *equals_sign = strchr(input, '=');
    if (equals_sign == NULL) {
        fprintf(stderr, "Invalid input format: no '=' found\n");
        return;
    }

    // 复制 name 部分
    size_t name_length = equals_sign - input;
    strncpy(name, input, name_length);
    name[name_length] = '\0';

    // 跳过等号后的空白字符
    const char *cmd_start = equals_sign + 1;
    while (*cmd_start && isspace((unsigned char)*cmd_start)) {
        cmd_start++;
    }

    // 处理引号
    if (*cmd_start == '\'') {
        cmd_start++;
    }

    // 复制 command 部分，跳过末尾的引号和空白字符
    const char *cmd_end = cmd_start + strlen(cmd_start) - 1;
    while (cmd_end > cmd_start && (isspace((unsigned char)*cmd_end) || *cmd_end == '\'')) {
        cmd_end--;
    }

    size_t command_length = cmd_end - cmd_start + 1;
    strncpy(command, cmd_start, command_length);
    command[command_length] = '\0';

    // 去除 name 中的空白字符
    char temp_name[256];
    size_t j = 0;
    for (size_t i = 0; i < name_length; i++) {
        if (!isspace((unsigned char)name[i])) {
            temp_name[j++] = name[i];
        }
    }
    temp_name[j] = '\0';
    strcpy(name, temp_name);
}
//更新别名文件
/*C   O   N   F   I   R   M*/
int update_alias_command(const char *name, const char *newcmd) {
    FILE *file = fopen(ALIAS_FILE_PATH, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    char nickname[MAX_STRING_LENGTH];
    char cmd[MAX_STRING_LENGTH];
    FILE *temp_file = fopen(ALIAS_FILE_TMP_PATH, "w");
    if (temp_file == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return 0;
    }

    int found = 0;

    // 逐行读取文件并检查
    while (fgets(line, sizeof(line), file)) {
        // 使用 sscanf 解析每行的两个字符串
        if (sscanf(line, "%s %s", nickname, cmd) == 2) {
            if (strcmp(nickname, name) == 0) {
                // 找到匹配项，更新 cmd
                fprintf(temp_file, "%s %s\n", nickname, newcmd);
                found = 1;
            } else {
                // 不修改的行写回临时文件
                fprintf(temp_file, "%s", line);
            }
        } else {
            // 非法格式行直接写回临时文件
            fprintf(temp_file, "%s", line);
        }
    }

    fclose(file);
    fclose(temp_file);

    // 用临时文件替换原文件
    if (found) {
        if (remove(ALIAS_FILE_PATH) != 0) {
            perror("Error removing original file");
            return 0;
        }
        if (rename(ALIAS_FILE_TMP_PATH, "alias.txt") != 0) {
            perror("Error renaming temporary file");
            return 0;
        }
        return 1;
    } else {
        remove(ALIAS_FILE_TMP_PATH);
        return 0;
    }
}
//print alias
void print_aliases() {
    FILE *file = fopen(ALIAS_FILE_PATH, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char a[MAX_STRING_LENGTH];
    char b[MAX_STRING_LENGTH];

    // 逐行读取文件并输出
    while (fgets(line, sizeof(line), file)) {
        // 使用 sscanf 解析每行的两个字符串
        if (sscanf(line, "%s %s", a, b) == 2) {
            printf("%s=%s\n", a, b);
        }
    }
    fclose(file);
}
//alias function
void alias(char **argv){
    //alias
    if(argv[1]==NULL)
    {
        //输出所有的alias信息
        print_aliases();
    }
    //alias cdt='cd tab'
    else{
        //split alias cmd
        char name[64];
        char command[64];
        split_alias(argv[1],name,command);
        printf("argv[1]:%s\n",argv[1]);
        //查看是否有重名alias
        if(update_alias_command(name,command)==0)
        {
            //没有重名
            do_alias(command,name);
        }
    }
    




}
//获取第一个单词
void get_first_word(const char *input, char *word) {
    // Skip leading whitespace
    while (isspace((unsigned char)*input)) {
        input++;
    }

    // Copy the first word to the output parameter
    while (*input && !isspace((unsigned char)*input)) {
        *word++ = *input++;
    }

    // Null-terminate the output string
    *word = '\0';
}
//利用alias修改原指令语句
int replace_word_with_alias(const char *input, char *output) {
    char word[256];
    get_first_word(input, word);

    FILE *file = fopen(ALIAS_FILE_PATH, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[1024];
    char a[256];
    char b[256];
    int found = 0;

    // Read file line by line and look for matching alias
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s %s", a, b) == 2) {
            if (strcmp(a, word) == 0) {
                found = 1;
                break;
            }
        }
    }

    fclose(file);

    // Construct the output string
    if (found) {
        const char *remaining = input + strlen(word);
        while (isspace((unsigned char)*remaining)) {
            remaining++;
        }
        snprintf(output, 1024, "%s %s", b, remaining);
        return 1;
    } else {
        snprintf(output, 1024, "%s", input);
        return 0;
    }
}


