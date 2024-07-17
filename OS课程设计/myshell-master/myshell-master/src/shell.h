#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <readline/readline.h>
#include <readline/history.h>

#define hist_size 1024
#define MAX_PROMPT_LEN 100 
#define MAX_ARGS 64
#define MAX_INPUT 1024
#define MAX_CMD_COUNT 1024 // 最多1024个指令
#define MAX_CMD_LENGTH 256 // 指令名称最长为256字符
#define MAX_PATH_LEN 1024
#define MAX_CMD_LEN 256
#define MAX_NUM_CMDS 1000
#define MAX_FILE_NUM 1000
#define MAX_FILENAME_LEN 256
#define HISTORY_FILE_PATH "/Users/roysmith/Documents/myshell/his.txt"
#define ALIAS_FILE_PATH "/Users/roysmith/Documents/myshell/alias.txt"
#define ALIAS_FILE_TMP_PATH "/Users/roysmith/Documents/myshell/alias_tmp.txt"  //For Roy only
//#define HISTORY_FILE_PATH "/Users/marston/ECUST/osshell/test/myshell/his.txt"
//#define ALIAS_FILE_PATH "/Users/marston/ECUST/osshell/test/myshell/alias.txt"
//#define ALIAS_FILE_TMP_PATH "/Users/marston/ECUST/osshell/test/myshell/alias_tmp.txt"  //For Marston only
#define MAX_LINE_LENGTH 1024
#define MAX_STRING_LENGTH 256




extern char *hist[hist_size];//保存历史记录信息
extern int f ; 
extern int head , filled ;
extern int asynchronous; //用于标识程序是否异步执行
struct termios orig_termios;


void printPrompt(); //打印命令提示符函数
void parse(char *command, char **argv);       //语法分析函数
char *trim(char *string); //去除字符串中额外的空格
void execute(char **arg,int asynchoronous); //执行Simple命令
void execute_file(char **argv, char *output,int asynchoronous);
void execute_input(char **argv, char *output,int asynchoronous);
void execute_pipe(char **argv, char *output,int asynchoronous);
void execute_pipe2(char *command,char *left,int asynchoronous);//解析多管道指令，并调用相应的函数进行执行
void execute_muti_pipe(char ***argus,int asynchoronous);//执行多个管道命令
int get_len3(char ***argus);//获取char***中元素的个数
void reset_terminal_mode(); //重置终端的状态
void set_conio_terminal_mode(); //设置终端为原始状态
int kbhit();    //检测是否键入了一个字符
int getch();    //Get the next character input without waiting for enter
char *command_generator(const char *text,char **cmd,int current_index);//根据所给的字符串库和index的值返回匹配到的字符串
int get_len2(char **cmd); //获取char **中元素的个数  **C  O  N  F  I  R  M**
void get_commands_from_directory(const char *dir_name, char **cmd, size_t *cmd_count); //获取目录中所有的文件名
char **get_all_commands(); //获取shell中所有指令的名称  **R E P E A L E D**
char **get_files_and_folders(const char *dir_path); //获取目录中的所有文件名和文件夹名
char **get_shell_commands(); //获取shell中所有指令的名称 **C  O  N  F  I  R  M**
char **list_files_in_directory(const char *path);//获取指定目录中所有的文件名  **C  O  N  F  I  R  M**
void free_file_list(char **file); //用于释放文件链表的空间
int jud_completion_type(char *input); //根据输入的内容，判断此时要补全内容的类型 **R E P E A L E D**
char *get_completion_file(char *input,int *current_index); //根据输入的内容，得到要补全的部分的文件目录
char *get_completion_cmd(char *input,int *current_index); //根据输入的内容，得到要补全的部分的指令名 **R E P E A L E D**
char *get_string_after_last_flag(const char *input, char flag);//获取字符串中最后一个flag后面的字符串
char **split_string_by_space(const char *input); //将字符串根据空格分割开
void free_split_result(char **res); //释放中间链表的空间
int jud_completion_simple_type(char *input); //根据输入的内容，判断要补全的内容的类型（Simple）
int search_spec_last_flag(char *input); //根据输入的内容，对输入内容最后所含有的特殊符号进行判断
int search_pipe_flag(char *input); //根据输入的内容，查找含有多少管道符号数
char *get_completion_common_cmd(char *input,int *current_index); //根据输入的内容，得到要补全的部分的常见指令名**C  O  N  F  I  R  M**
void get_current_path(char *cpath, size_t size);//获取当前路径名
void trim_whitespace(char *str); //去除字符串前后的空格
char* process_path(const char *path); //处理路径并返回出中间路径
char* get_substring_before_last_flag(const char *str, char flag);
void save_history(char *hist[], int count);//保存历史记录表
void load_history(char *hist[], int *count); //加载历史记录表
void history(char **argv,char *hist[],int *filled,int *head);
void do_alias(char* cmd,char *nickname);//设置alias别名
int search_alias(char *nickname,char *cmd); //根据别名查找是否在alias文件中
void alias(char **argv);//alias function
void split_alias(const char *input, char *name, char *command);//对alias command进行分割
void print_aliases(); //打印alias信息
void get_first_word(const char *input, char *word);
int replace_word_with_alias(const char *input, char *output);
void unalias(char *nickname);  //unalias function
int delete_alias(const char *nickname); //删除一个指定的alias
int update_alias_command(const char *name, const char *newcmd);
void ls(char **argv); //ls function
void print_file_info(const char *name, const struct stat *file_stat);   //ls -l func
void type(char **argv); // type func
void echo(char **argv); //echo func
void parse_variables(char *str, char *result);//echo parse
void pwd();//pwd func
void cat(char **argv);//cat func
void grep(const char *pattern, const char *filename);//在给定文件中搜索匹配的模式
void grep_command(char **argv);//grep_command 函数：解析命令行参数并调用 grep 函数
int extract_last_word(const char *input, char *be, char *file); //获取最后一个单词
char *do_file_completion_redirect(char *input,int *current_index);
char *do_file_completion_simple(char *input,int *current_index);

//常见指令类型
extern char *common_cmd[];








