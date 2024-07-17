#include"shell.h"

char *common_cmd[]={
    // 文件和目录操作
        "ls", "cd", "pwd", "mkdir", "rmdir", "cp", "mv", "rm", "touch", "ln",
        // 文件内容查看
        "cat", "more", "less", "head", "tail", "tac",
        // 文件搜索和比较
        "find", "grep", "diff", "cmp",
        // 文本处理
        "echo", "sed", "awk", "cut", "sort", "uniq", "tr",
        // 压缩与解压
        "tar", "gzip", "gunzip", "zip", "unzip",
        // 系统管理
        "ps", "top", "kill", "df", "du", "free", "uname", "uptime", "who", "w", "id","exit",
        // 权限管理
        "chmod", "chown", "chgrp",
        // 网络操作
        "ping", "ifconfig", "netstat", "scp", "ssh",
        // 其他常用指令
        "man", "history", "alias", "unalias", "which", "whereis", "type",
        // 以 NULL 结尾
        NULL
};

//重置终端的状态
void reset_terminal_mode(){
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
// 设置终端状态的RAW
void set_conio_terminal_mode() {
    struct termios new_termios;

    // Take two copies - one for now, one for later
    tcgetattr(STDIN_FILENO, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    // Make one change to the copy
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    atexit(reset_terminal_mode);
}
//检测是否键入了字符
int kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}
// Get the next character input without waiting for enter
int getch() {
    int r;
    unsigned char c;
    if ((r = read(STDIN_FILENO, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}
//获取char **cmd中元素的个数
/*C    O     N     F     I     R     M*/
int get_len2(char **cmd){
   int  count = 0;
    while (cmd[count] != NULL) {
        count++;
    }
    return count;
}
//根据所给的字符串库和index的值返回匹配到的字符串
char *command_generator(const char *text,char **cmd,int current_index) {
    int len = strlen(text);
    char *name;

    for (int i = current_index + 1; i <get_len2(cmd) ; i++) {
        name = cmd[i];
        if (strncmp(name, text, len) == 0) {
            current_index = i;
            return name;
        }
    }

    // Reset if no more matches
    current_index = -1;
    return NULL;
}
// 获取目录中的所有文件名
void get_commands_from_directory(const char *dir_name, char **cmd, size_t *cmd_count) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(dir_name)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            // 跳过 '.' 和 '..'
            if (entry->d_name[0] == '.')
                continue;

            // 复制指令名称到 cmd 数组
            cmd[*cmd_count] = strdup(entry->d_name);
            if (cmd[*cmd_count] == NULL) {
                perror("strdup");
                exit(EXIT_FAILURE);
            }

            (*cmd_count)++;

            // 如果超过了最大指令数量，退出循环
            if (*cmd_count >= MAX_CMD_COUNT) {
                break;
            }
        }
        closedir(dir);
    } else {
        perror("opendir");
    }
}

// 获取所有指令名称的函数
char **get_all_commands() {
    char *directories[] = {"/usr/bin"};
    size_t dir_count = sizeof(directories) / sizeof(directories[0]);

    // 分配内存给指令数组
    char **cmd = malloc(MAX_CMD_COUNT * sizeof(char *));
    if (cmd == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    size_t cmd_count = 0;
    for (size_t i = 0; i < dir_count; i++) {
        get_commands_from_directory(directories[i], cmd, &cmd_count);
    }

    // 重新分配内存，使其只包含实际的指令数量
    cmd = realloc(cmd, cmd_count * sizeof(char *));
    if (cmd == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }

    return cmd;
}
// 获取目录中的所有文件名和文件夹名
char **get_files_and_folders(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;
    char **file = NULL;
    size_t file_count = 0;

    // 打开目录
    if ((dir = opendir(dir_path)) != NULL) {
        // 循环读取目录项
        while ((entry = readdir(dir)) != NULL) {
            // 跳过 . 和 ..
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            // 分配内存给文件名/文件夹名
            file = realloc(file, (file_count + 1) * sizeof(char *));
            if (file == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }

            // 分配内存给存储文件名/文件夹名的字符串
            file[file_count] = malloc(strlen(entry->d_name) + 2); // 加2是为了考虑添加 '\' 和 结束符 '\0'
            if (file[file_count] == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            // 如果是文件夹，添加 '\' 结尾
            if (entry->d_type == DT_DIR) {
                sprintf(file[file_count], "%s\\", entry->d_name);
            } else {
                strcpy(file[file_count], entry->d_name);
            }

            file_count++;
        }
        closedir(dir);
    } else {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // 添加一个空指针作为结束标志
    file = realloc(file, (file_count + 1) * sizeof(char *));
    if (file == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    file[file_count] = NULL;

    return file;
}

/*C    O     N     F     I     R     M*/
char **get_shell_commands() {
    char **cmd = (char **)malloc(MAX_NUM_CMDS * sizeof(char *));
    if (cmd == NULL) {
        perror("malloc");
        return NULL;
    }

    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        fprintf(stderr, "Failed to get PATH environment variable\n");
        free(cmd);
        return NULL;
    }

    char *path = strdup(path_env);
    if (path == NULL) {
        perror("strdup");
        free(cmd);
        return NULL;
    }

    char *dir = strtok(path, ":");
    int cmd_index = 0;

    while (dir != NULL) {
        struct dirent *entry;
        struct stat statbuf;
        char filepath[MAX_PATH_LEN];
        DIR *dp = opendir(dir);

        if (dp == NULL) {
            perror("opendir");
            dir = strtok(NULL, ":");
            continue;
        }

        while ((entry = readdir(dp)) != NULL && cmd_index < MAX_NUM_CMDS) {
            snprintf(filepath, MAX_PATH_LEN, "%s/%s", dir, entry->d_name);

            if (stat(filepath, &statbuf) == -1) {
                perror("stat");
                continue;
            }

            if (S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR)) {
                cmd[cmd_index] = strdup(entry->d_name);
                if (cmd[cmd_index] == NULL) {
                    perror("strdup");
                    closedir(dp);
                    free(path);
                    for (int i = 0; i < cmd_index; i++) {
                        free(cmd[i]);
                    }
                    free(cmd);
                    return NULL;
                }
                cmd_index++;
            }
        }

        closedir(dp);
        dir = strtok(NULL, ":");
    }

    cmd[cmd_index] = NULL;  // 结束标记
    free(path);
    return cmd;
}

char **list_files_in_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }

    char **file = (char **)malloc(MAX_FILE_NUM * sizeof(char *));
    if (file == NULL) {
        perror("malloc");
        closedir(dir);
        return NULL;
    }

    struct dirent *entry;
    int file_index = 0;
    while ((entry = readdir(dir)) != NULL && file_index < MAX_FILE_NUM) {
        char filepath[MAX_FILENAME_LEN];
        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

        struct stat filestat;
        if (stat(filepath, &filestat) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISREG(filestat.st_mode)) {
            file[file_index] = strdup(entry->d_name);
            if (file[file_index] == NULL) {
                perror("strdup");
                for (int i = 0; i < file_index; i++) {
                    free(file[i]);
                }
                free(file);
                closedir(dir);
                return NULL;
            }
            file_index++;
        }
    }

    file[file_index] = NULL;  // 结束标记
    closedir(dir);
    return file;
}

void free_file_list(char **file) {
    for (int i = 0; file[i] != NULL; i++) {
        free(file[i]);
    }
    free(file);
}

char *get_string_after_last_flag(const char *input, char flag) {
    char *result = NULL;

    char *last_occurrence = strrchr(input, flag);
    if (last_occurrence != NULL) {
        result = strdup(last_occurrence + 1);
    } else {
        result = strdup("");
    }

    return result;
}

/*
*type0:表示此时没有可以补全的类型 
*type1:表示此时要补全的内容为文件名，位于管道后的指令的输入重定向后（含有字符）
*type2:表示此时要补全的内容为文件名，位于管道后的指令的输入重定向后（无字符情况）
*type3:表示此时要补全的内容为文件名，位于管道后的指令的输出重定向后（含有字符）
*type4:表示此时要补全的内容为文件名，位于管道后的指令的输出重定向后（无字符情况）
*type5:表示此时要补全的内容为指令名，位于管道符号后
*type6:表示此时要补全的内容为文件名，位于管道符号后面
*/

// int jud_completion_type(char *input){
//     int flag_pipe=0; //指示是否含有管道指令
//     int flag_rediect=0; //指示是否含有重定向符号
//     //检查是否有管道符
//     int *input_tmp=input;
//     while(*input_tmp!='\0')
//     {
//         if(*input_tmp=='|') {flag_pipe=1; break;}
//         input_tmp++;
//     }
//     if(flag_pipe==1){
//         //指令中出现了管道符
//         char *input_after_last_pipe=get_string_after_last_flag(input,'|');
//         //检查剩余的部分是否有重定向符号
//         char *tmp=input_after_last_pipe;
//         while(*tmp!='\0')
//         {
//             /*flag最后为1说明只出现了输入重定向 flag最后为2说明出现了输出重定向，不用知道前面是否出现输入重定向*/
//             if(*tmp=='<'){ flag_rediect=1;}
//             else if(*tmp=='>'){flag_rediect=2;}
//             tmp++;
//         }
//         //如果出现重定向符号 
//         if(flag_rediect==1||flag_rediect==2) {
//             //获取重定向符号后面的内容
//             if(flag_rediect==1)//仅出现输入重定向
//             {
//                 char *input_after_ri=get_string_after_last_flag(input_after_last_pipe,'<');
//                 //去查看重定向符号后面的目录是否输入结束
//                 int contains_ch=0;
//                 char *after_ri=input_after_ri;
//                 while(*after_ri!='\0'){
//                     if(*after_ri!=' ')
//                     {
//                         //当前字符不是空格
//                         contains_ch=1;
//                     }else{
//                         //当前字符为空格
//                         //如果在空格前面没有字符，那么就忽略
//                         //如果在空格前出现了字符，那么认为此时已经输入完毕，没有需要补全的内容了
//                         ///type0
//                         if(contains_ch==1) return 0; 
//                     }
//                     after_ri++; //处理下一个字符
//                 }
//                 if(contains_ch==1)///type1
//                 {return 1;}
//                 else{return 2;}//没出现过任何字符
//             }else{
//                 //出现了输出重定向
//                 //获取输出重定向后面的内容
//                 char * input_after_ro=get_string_after_last_flag(input_after_last_pipe,'>');
//                 //查看重定向符号后面的内容是否完成输入
//                 int contains_ch=0;
//                 char *after_ro=input_after_ro;
//                 while(*after_ro!='\0')
//                 {
//                       if(*after_ro!=' ')
//                         {
//                             //当前字符不是空格
//                             contains_ch=1;
//                         }
//                         else{
//                             //当前字符为空格
//                             //如果在空格前面出现过字符，那么此时就认为输入已经结束，没有需要补全的内容了
//                             //如果在空格前面没有出现过字符，那么就忽略这个字符
//                             if(contains_ch==1) return 0; ///type0
//                         }
//                 }
//                 if(contains_ch==1) ///type3
//                 return 3;
//                 else return 4; ///type4


//             }
//         }else{
//             //管道指令中没有重定向符号
//             //将剩余字符进行切分
//             char **tmp_without_red=split_string_by_space(input_after_last_pipe);
//             if(*tmp_without_red==NULL)
//             {
//                 //此时表示管道符号后面没有输入了
//                 ///type5
//                 return 5;

//             }else {
//                 //意味着此时有命令字符
//                 if(!tmp_without_red[0][strlen(tmp_without_red[0])-1]==' ')
//                 {
//                     //命令字符没有输入结束
//                     ///type5
//                     return 5;
//                 }else{
//                     //命令字符输入完毕
//                    if(tmp_without_red[1]==NULL)
//                    {
//                     ///type6
//                     return 6;
//                    }
//                    if(tmp_without_red[1][0]=='-')
//                    {
//                     //第二个为选项
//                     if(tmp_without_red[1][strlen(tmp_without_red[1])-1]!=' ')
//                     //选项未输入完毕
//                     ///type0
//                     return 0;
//                     else{
//                         //选项输入完毕
//                         if(tmp_without_red[2]==NULL)
//                         ///type 6
//                         return 6;
//                         else{
//                             if(tmp_without_red[2][strlen(tmp_without_red)-1]!=' ')
//                             ///type 6
//                             return 6;
//                             else return 0; //全部输入完毕  ///type0
//                         }

//                     }
//                    }else{
//                     //没有选项
//                     if(tmp_without_red[1][strlen(tmp_without_red)-1]==' ')
//                     ///type 0
//                     return 0;
//                     else{
//                         ///type 6
//                         return 6;
//                     }
//                     return 0;
//                    }

//                 }
//                 return 0;
//             }
//             return 0;
//         }
//     }else{
//         //指令中没有管道符号

//     }

// }

/*
*type0:没有需要补全的内容
*type1:需要对指令进行补全
*type2:需要对文件名进行补全
*type3:需要对输入重定向符号后面的文件名进行补全
*type4:需要对输出重定向符号后面的文件名进行补全
*/
/*C    O     N     F     I     R     M*/
int jud_completion_simple_type(char *input)
{
    //判断是否存在重定向符号
    int flag=search_spec_last_flag(input);
    if(flag==0){
//没有重定向符号的情况
    //将输入的内容根据空格进行分割
    char **input_without_blank=split_string_by_space(input);
    if(input_without_blank[0]==NULL)
    {
        //没有输入任何内容
        ///type1
        return 1;
    }
    //存在输入的字符
    if(input_without_blank[0][strlen(input_without_blank[0])-1]!=' ')
    {
        //命令字符未输入完成
        ///type 1
        return 1;
    }
    //命令字符输入完毕
    if(input_without_blank[1]==NULL)
    {
        ///type 2
        return 2;
    }
    if(input_without_blank[1][0]=='-')
    {
        //存在选项
        if(input_without_blank[1][strlen(input_without_blank[1])-1]!=' ')
        //表示此时选项的输入未完成
        ///type0
        return 0;
        ///下面就表示选项输入完成
        if(input_without_blank[2]==NULL)
        ///type2
        return 2;
        if(input_without_blank[2][strlen(input_without_blank[2])-1]!=' ')
        ///type 2
        return 2;
        //命令全部输入完毕
        return 2;

    }
    //没有选项的情况
    if(input_without_blank[1][strlen(input_without_blank[1])-1]==' ')
    //输入完毕
    ///type0
    return 2;
    else{
    return  2;}

    }else if(flag==1||flag==2)
    {
        //当存在输入输出重定向时
        //获取重定向符号后面的字符
        char *tmp=NULL;
        if(flag==1) tmp=get_string_after_last_flag(input,'>');
        else if(flag==2) tmp=get_string_after_last_flag(input,'<');
        if(tmp[strlen(tmp)-1]==' ')
        //此时代表输入完毕
        ///type 0
        return 0;
        else{
            //此时最后一个文件名没有输入完毕
            if(flag==1) 
            ///type4
            return 4;
            if(flag==2)
            ///type 3
            return 3;
        }
    }
    return 0;
}

/*C    O     N     F     I     R     M*/
//根据输入的内容，对输入内容所含有的最后一个特殊符号进行判断
/*
*flag=0  没有特殊符号
*flag=1  最后一个为输出重定向
*flag=2  最后一个为输入重定向
*flag=3  最后一个为管道符号
*/
int search_spec_last_flag(char *input)
{
    int flag=0;
    while(*input!='\0')
    {
        if(*input=='|') flag=3;
        else if(*input=='>') flag=1;
        else if(*input=='<') flag=2;
        input++;
    }
    return flag;
}
/*C    O     N     F     I     R     M*/
//根据输入的内容，查找含有多少管道符号数
int search_pipe_flag(char *input)
{
    int flag=0;
    while(input!='\0')
    {
        if(*input=='|') flag++;
        input++;
    }
    return flag;
}
//根据所给的指令的一部分和index的值返回补全后的字符串
char *get_completion_cmd(char *input,int *current_index)
{
    //获取所有的指令名称
    char **cmd=get_shell_commands();
    char *name; 
    int len=strlen(input);
    for(int i=*current_index;i<get_len2(cmd);i++)
    {
        name=cmd[i];
        if(strncmp(name,input,len)==0)
        {
            *current_index=i;
            return name;
        }
    }
     // Reset if no more matches
    *current_index = -1;
    return NULL;
}
//根据输入的内容，得到要补全的部分的常见指令名
/*C    O     N     F     I     R     M*/
char *get_completion_common_cmd(char *input,int *current_index){
    char *name;
    int len=strlen(input);
    int len2=get_len2(common_cmd);
    for(int i=*current_index+1;i<len2;i++)
    {
        name=common_cmd[i];
        if(strncmp(name,input,len)==0)
        {
            *current_index=i;
            return name;
        }
    }
     // Reset if no more matches
    *current_index = -1;
    return NULL;
}
//根据输入的内容，得到要补全的部分的文件目录
char *get_completion_file(char *input,int *current_index){
    //获取当前目录名
    char cpath[1024];
    get_current_path(cpath,sizeof(cpath));
    //printf("cpath_before_process:%s\n",cpath);
    
    //对获得到的目录进行处理，将当前目录后面加上’/‘
    int d=strlen(cpath);
        cpath[d++]='/';
        cpath[d]='\0';
    //printf("current path=%s\n",cpath);
    //获取input的中间路径
    char *tmp=process_path(input);
    //printf("tmp:%s\n",tmp);
    if(tmp!=NULL){
        //将起始路径和中间路径合并
        strcat(cpath,tmp);
    }
    //printf("middle path:%s\n",cpath);
    //获取要补全文件名所在的目录下的所有文件名
    char **file=list_files_in_directory(cpath);
    int len_file=get_len2(file);
    //printf("len_file:%d\n",len_file);
    char *res_filename;
    //获得待补全的部分
    char *do_completion=get_string_after_last_flag(input,'/');
    if(strcmp(do_completion,"")==0) {do_completion=input;
    //printf("do_completion->NULL");
    }
    //printf("do_completion:%slen:%d\n",do_completion,strlen(do_completion));
    //进行补全
    char *name=NULL;
    int len=strlen(do_completion);
    if(*current_index+1>=len_file) {*current_index=-1;return  NULL;}
    for(int i=*current_index+1;i<len_file;i++)
    {
        name=file[i];
        if(strncmp(name,do_completion,len)==0)
        {
            *current_index=i;
            res_filename=name;
            break;
        }
        //reset if no more matches
        *current_index=-1;
        
    }
    //printf("res_filename:%s\n",res_filename);

    char *in_be;
    if(*current_index==-1)
    {return NULL;}
    else{
        if(get_substring_before_last_flag(input,'/')==NULL){return res_filename;}
        else{
        in_be=get_substring_before_last_flag(input,'/');
        in_be[strlen(in_be)]='/';
        in_be[strlen(in_be)+1]='\0';
        }
       // printf("%s\n",in_be);
        strcat(in_be,res_filename);
       // printf("%s\n",in_be);
        return in_be;
    }


}
//获取当前路径名
void get_current_path(char *cpath, size_t size) {
    if (getcwd(cpath, size) == NULL) {
        perror("getcwd");
    }
}

// 去除字符串前后的空格
void trim_whitespace(char *str) {
    char *end;

    // 去除前导空格
    while (isspace((unsigned char)*str)) str++;

    // 所有字符都是空格的情况
    if (*str == 0) return;

    // 去除尾部空格
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // 添加终止符
    *(end + 1) = 0;
}

// 处理路径并返回结果
char* process_path(const char *path) {
    // 复制路径以进行修改
    char *trimmed_path = strdup(path);
    if (trimmed_path == NULL) {
        perror("strdup");
        return NULL;
    }

    // 去除前后空格
    trim_whitespace(trimmed_path);

    // 如果第一个字符是'/'
    if (trimmed_path[0] == '/') {
        memmove(trimmed_path, trimmed_path + 1, strlen(trimmed_path));
    }

    // 找到最后一个'/'
    char *last_slash = strrchr(trimmed_path, '/');
    if (last_slash != NULL) {
        // 终止在最后一个'/'处
        *last_slash = '\0';
    } else {
        // 没有'/'返回NULL
        free(trimmed_path);
        return NULL;
    }

    // 复制结果以返回
    char *result = strdup(trimmed_path);
    //对结果进行处理
    result[strlen(result)]='/';
    result[strlen(result)+1]='\0';
    free(trimmed_path);

    if (result == NULL) {
        perror("strdup");
        return NULL;
    }

    return result;
}
char* get_substring_before_last_flag(const char *str, char flag) {
    // 查找字符串中最后一个指定字符的指针
    char *last_occurrence = strrchr(str, flag);
    
    // 如果没有找到指定字符，返回 NULL
    if (last_occurrence == NULL) {
        return NULL;
    }

    // 计算子字符串的长度
    size_t length = last_occurrence - str;

    // 分配内存给新字符串，加1是为了放终止符
    char *result = (char *)malloc(length + 1);
    if (result == NULL) {
        perror("malloc");
        return NULL;
    }

    // 复制子字符串并添加终止符
    strncpy(result, str, length);
    result[length] = '\0';

    return result;
}
int extract_last_word(const char *input, char *be, char *file) {
    if (input == NULL || be == NULL || file == NULL) {
        return 0;
    }

    int input_length = strlen(input);
    int last_word_length = 0;
    int last_word_start = 0;
    int last_word_end = input_length - 1;

    // 寻找最后一个单词的起始位置和长度
    int i;
    for (i = input_length - 1; i >= 0; i--) {
        if (input[i] == ' ') {
            if (last_word_length == 0) {
                continue; // 忽略连续的空格
            } else {
                last_word_start = i + 1;
                last_word_length = last_word_end - last_word_start + 1;
                break;
            }
        } else if (i == input_length - 1) {
            last_word_length = 0; // 最后一个字符是非空格字符，但后面有空格
            break;
        }
    }

    if (last_word_length == 0) {
        return 0; // 最后一个单词后面有空格，返回 0
    }

    // 复制前面的内容到 be
    strncpy(be, input, last_word_start);
    be[last_word_start] = '\0';

    // 复制最后一个单词到 file
    strncpy(file, input + last_word_start, last_word_length);
    file[last_word_length] = '\0';

    return 1; // 提取成功，返回 1
}


char *do_file_completion_redirect(char *input,int *current_index)
{
    char *ans=(char *)malloc(sizeof(char)*128);
    int re_loc=0;
    for(int i=0;i<strlen(input);i++)
    {
        if(input[i]=='<' || input[i]=='>')
            re_loc=i+1;
    }

    //对重定向符号后面的内容进行修改
    //skip blank
    while(input[re_loc]==' ')
        re_loc++;
    int st=re_loc; //替换可能发生的起点
    int end_dir=re_loc; //目录的终点 
    int p=re_loc;
    while(input[p]!=' ' && input[p]!='\0')
    {
        if(input[p]=='/') end_dir=p;
        p++;
    }
    //printf("re_loc=%d end_dir=%d\n",re_loc,end_dir);
    char *res=get_completion_file(&input[re_loc],current_index);
    //printf("res=%s\n",res);
    if(res==NULL) return input;
    //if(end_dir!=st) end_dir++;
    for(int i=0;i<st;i++)
        ans[i]=input[i];
    for(int i=0;i<strlen(res);i++)
    {
        ans[st++]=res[i];
    }
    ans[st]='\0';
    //printf("ans=%s\n");
    return ans;
}


char *do_file_completion_simple(char *input,int *current_index)
{
    //printf("len_input:%d input[%d]=%c\n",strlen(input),strlen(input)-1,input[strlen(input)-1]);
    char *ans=(char *)malloc(sizeof(char)*128);
    int re_loc=0;int end_dir=0;
    //从后向前搜索
    int i;
    for(i=strlen(input)-1;i>=0;i--)
    {
        //printf("%d ",i);
        if(input[i]=='/' && end_dir==0)
        {
            //记录最后一个'/'的位置，即目录的结束
            end_dir=i;
        }
        if(input[i]==' ')
        {
            //记录可能的目录的开始
            re_loc=i+1;
            break;
        }
    }
    //printf("re_loc=%d end_dir=%d\n",re_loc,end_dir);
    char *res=get_completion_file(&input[re_loc],current_index);
    //printf("res=%s\n",res);
    if(res==NULL) return input;
    for(int j=0;j<re_loc;j++)
        ans[j]=input[j];
    for(int j=0;j<strlen(res);j++)
        ans[re_loc++]=res[j];
    ans[re_loc]='\0';
    return ans;

}