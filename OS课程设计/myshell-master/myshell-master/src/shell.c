#include"shell.h"
char *hist[hist_size];
int f = 0; //to save change in directory
int head = 0, filled = 0;
int asynchoronus=0;

int main()
{
    char line[1024];
    char *argv[64];
    char *args[64];
    char *left;
    size_t size = 0;
    char ch;
    int count = 0;
    char *tri;
    char *second;
    char *file;
    int i;
    int current_index = -1; // To keep track of the current completion
    for (i = 0; i < hist_size; i++)
    {
        hist[i] = (char *)malloc(150);
    }
    //加载历史记录表
    load_history(hist,&filled);
    head=filled;
    while (1)
    {
        int i = 0; // for loop
        count = 0;
        int flag = 0;
        int len = 0;          // length of the complete command
        char *command = NULL; // the complete command
        char *dire[] = {"pwd"};
        int tab=0; //标记上一次操作是否为TAB操作
        char input_tmp[MAX_INPUT];
        fflush(stdout);
        //printPrompt();
        asynchoronus=0;//初始化
        //len = getline(&command, &size, stdin); // read line
        /*命令补全部分代码*/
        ////////////////////////////////////////////////////////////////////////////
        char input[MAX_INPUT];
        int input_len=0; //len
        set_conio_terminal_mode();
        printPrompt();//打印标头
        fflush(stdout);
        //循环拾取输入字符
        while(1)
        {
             if (kbhit()){
                char c=getch();
                if(c=='\t') //TAB Button
                {
                     input[input_len] = '\0';
                    //将当前的的input保存
                    //根据输入的内容判断要补全的类型
                    int type=jud_completion_simple_type(input);
                    //备份input
                    if(tab==0) strcpy(input_tmp,input);
                    if(tab==0) current_index=-1;
                    if(tab==0){
                        //首次进行TAB操作
                        if(type==1)
                        {
                            //对指令进行补全
                            char *completion=get_completion_common_cmd(input,&current_index);
                            if(completion){
                                printf("\r\033[K");
                                printPrompt();
                                printf("%s", completion);
                                fflush(stdout);
                                strcpy(input, completion);
                                input_len = strlen(input);
                                tab=1;
                            }

                        }
                        if(type==2){
                            //对文件名进行补全
                                char *completion=do_file_completion_simple(input,&current_index);
                                //printf("completion:%s\n",completion);
                                printf("\r\033[K");
                                printPrompt();
                                printf("%s", completion);
                                fflush(stdout);
                                strcpy(input, completion);
                                input_len = strlen(input);
                                tab=1;
                        
                            



                        }else if(type==3 ||type==4){
                            //对重定向符号后的文件名进行补全
                            char * completion=do_file_completion_redirect(input,&current_index);
                            //printf("completion:%s\n",completion);
                                printf("\r\033[K");
                                printPrompt();
                                printf("%s", completion);
                                fflush(stdout);
                                strcpy(input, completion);
                                input_len = strlen(input);
                                tab=1;
                        }
                    }else if(tab==1){
                        if(type==1)
                        {
                            //对指令进行补全
                            char *completion=get_completion_common_cmd(input_tmp,&current_index);
                            if(completion){
                                printf("\r\033[K");
                                printPrompt();
                                printf("%s", completion);
                                fflush(stdout);
                                strcpy(input, completion);
                                input_len = strlen(input);
                                tab=1;
                            }

                        }else if(type==3|| type==4)
                        {
                            char * completion=do_file_completion_redirect(input_tmp,&current_index);
                            //printf("completion:%s\n",completion);
                                printf("\r\033[K");
                                printPrompt();
                                printf("%s", completion);
                                fflush(stdout);
                                strcpy(input, completion);
                                input_len = strlen(input);
                                tab=1;

                        }else if(type==2)
                        {
                             char *completion=do_file_completion_simple(input_tmp,&current_index);
                                printf("\r\033[K");
                                printPrompt();
                                printf("%s", completion);
                                fflush(stdout);
                                strcpy(input, completion);
                                input_len = strlen(input);
                                tab=1;
                        }
                    }

                    
                }else if(c == 127 || c == '\b'){
                    //Backspace Key
                     if (input_len > 0) {
                    input_len--;
                    input[input_len] = '\0';
                    printf("\r\033[K");
                    printPrompt();
                    printf("%s", input);
                    //printf("\b");
                    fflush(stdout);
                    tab=0;
                }
                }else if(isprint(c)){
                input[input_len++] = c;
                input[input_len] = '\0';
                printf("%c", c);
                fflush(stdout);
                tab=0;
                }else if (c == '\n' || c == '\r') {
                printf("\n");
                fflush(stdout);
                input[input_len] = '\0';
                command=input;
                break;
                // Reset for next input
                //printsth();
               
            }else{tab=0;}

             }

        }
         reset_terminal_mode();

        ////////////////////////////////////////////////////////////

        if (*command == '\n') // just press enter
            continue;

        command[len - 1] = '\0'; // replace \n with \0
        //保存历史记录和历史记录表
        strcpy(hist[head],command);
        head=(head+1)%hist_size;
        filled++;
        save_history(hist,filled);
        //首先进行是否异步执行的检查
        if(strstr(command,"&")>0)
        {
            char *nothing=(char*)malloc(64);
            //当在指令中出现&时
            char *tmp=strtok_r(command, "&",&nothing);
            asynchoronus=1;
            command=tmp;
            //printf("asynchronous=%d\n",asynchoronus);
        }
        //对指令进行alias别名替换
        //////////////////////////////////
        char output[256];
        int ali=replace_word_with_alias(command,output);
        //printf("ali:%d,output:%s\n",ali,output);
        if(ali==1)
        {//存在alias别名
        //将^转化为空格
        char *cur=output;
        while(*cur!='\0')
        {if(*cur=='^')
        *cur=' ';
        if(*cur=='(')
        *cur='<';
        if(*cur==')')
        *cur='>';
        if(*cur=='!')
        *cur='|';
        cur++;
        }
        command=output;
        }
        //printf("cmd:%s\n",command);
    /////////////////////////////////////////////////////////////////////
        char *file = NULL;

        char *tempCommand = (char *)malloc(150);


        strcpy(tempCommand, command);
        parse(tempCommand, argv); // split the command by space
        int num_p=0;
        for (i = 0; command[i] != '\0'; i++)
        {
            if(command[i]=='|')
                num_p++;
        }
        if(num_p>1)
        {
            char *p = strtok_r(command, "|", &left);
            execute_pipe2(command,left,asynchoronus);
        }else{

        for (i = 0; command[i] != '\0'; i++)
        {
            //标记相应的重定向或管道操作，并解析指令 
            //获得第一个重定向或管道符号，然后调用相应的函数进行处理
            if (command[i] == '>') 
            {
                char *p = strtok_r(command, ">", &file);
                file = trim(file);
                flag = 1;
                break;
            }
            else if (command[i] == '<')
            {
                char *p = strtok_r(command, "<", &file);
                file = trim(file);
                flag = 2;
                break;
            }
            else if (command[i] == '|')
            {
                char *p = strtok_r(command, "|", &left);
                flag = 3;
                break;
            }
        }
        //当指令为exit，就直接退出shell
        if (strcmp(command, "exit") == 0)
        {
            exit(0);
        }
        
        //对重定向和管道操作进行处理
        if (flag == 1) //输出重定向
        {
            parse(command, argv);
            execute_file(argv, file,asynchoronus);
        }
        else if (flag == 2) //输入重定向
        {
            parse(command, argv);
            execute_input(argv, file,asynchoronus);
        }
        else if (flag == 3) //管道操作
        {
            char *argp[64];
            char *output, *file;
            if (strstr(left, "|") > 0)
            {
                //此时表示有多个管道操作
                //解析命令，然后执行多管道指令
                execute_pipe2(command,left,asynchoronus);
            }
            else
            {
                parse(command, argv);
                execute_pipe(argv, left,asynchoronus);
            }
        }
        else
        {
            parse(command, argv);
            execute(argv,asynchoronus);
        }
        }
    }
}