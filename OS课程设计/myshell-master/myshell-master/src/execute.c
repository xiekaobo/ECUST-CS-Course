#include"shell.h"


//执行simple命令 asyn=1 异步
void execute(char **argv,int asynchoronous)
{
    if(strcmp(argv[0],"history")==0)//查看历史命令
    {   
        history(argv,hist,&filled,&head);
        return; 
    }
    if (strcmp(argv[0], "cd") == 0)//改变路径
    {
        int retChdir = chdir(argv[1]); //直接更改当前工作目录
        if (retChdir==-1)
            printf("No such file or directory. %d,%s\n",retChdir,argv[1]);
        f = 1;
        return;
    }
    if(strcmp(argv[0],"alias")==0)//重命名
    {
        alias(argv);
        return;
    }
    if(strcmp(argv[0],"unalias")==0)
    {
        int i=1;
        while(argv[i])
        {
            unalias(argv[i]);
            i++;
        }
        return;
    }
    if(strcmp(argv[0],"ls")==0)//执行ls命令
    {
        ls(argv);
        return;
    }
    if(strcmp(argv[0],"type")==0)//执行type命令
    {
        type(argv);
        return;
    }
    if(strcmp(argv[0],"echo")==0)// 执行echo命令
    {
        echo(argv);
        return;
    }
    if(strcmp(argv[0],"pwd")==0)//执行pwd命令
    {
        pwd();
        return;
    }
    if(strcmp(argv[0],"cat")==0)//执行cat命令
    {   
        cat(argv);
        return;
    }
    if(strcmp(argv[0],"grep")==0)//grep命令
    {
        grep_command(argv);
        return;
    }
    pid_t pid;
    int status;
    if ((pid = fork()) < 0)
    {
        printf("error:fork failed.\n");
        exit(1);
    }
    else if (pid == 0)
    {
        if (execvp(argv[0], argv) < 0 && strcmp(argv[0], "cd"))
            printf("error:invalid command.\n");
        exit(0);
    }
    else
    {
        if(!asynchoronous)
        {
            //printf("PID: %d\n",pid);
            while (wait(&status) != pid)
            ;}
            else
            {
                //后台执行输出PID进程号
                printf("PID: %d\n",pid);
            }
    }
}

//执行指定的命令，并进行重定向和管道操作
void execute_file(char **argv, char *output,int asynchoronus)
{
   
    pid_t pid;
    int status, flag;
    char *file = NULL;
    if ((pid = fork()) < 0)//创建子进程
    {
        printf("error:fork failed.\n");
        exit(1);
    }
    else if (pid == 0)
    {
        //一般不会出现在输出重定向符号后面又出现一个输出重定向符号
        if (strstr(output, ">") > 0) //输出重定向
        {
            char *p = strtok_r(output, ">", &file);
            //重定向符号后的为文件名
            output += 1;       
            file = trim(file); 
            flag = 1;
            //备份标准输出
            int old_stdout = dup(1);
            //将文件重定向到标准输出上
            FILE *fp1 = freopen(output, "w+", stdout);
            execute_file(argv, file,asynchoronus);
            fclose(stdout);
            //恢复
            FILE *fp2 = fdopen(old_stdout, "w");
            *stdout = *fp2;
            exit(0);
        }
        if (strstr(output, "<") > 0) //输入重定向
        {
            char *p = strtok_r(output, "<", &file);
            file = trim(file);
            flag = 1;
            int fd = open(file, O_RDONLY);
            if (fd < 0)
            {
                printf("No such file or directory.");
                exit(0);
            }
        }
        if (strstr(output, "|") > 0) //管道操作
        {
            fflush(stdout);
            //printf("here");
            fflush(stdout);
            char *p = strtok_r(output, "|", &file);
            file = trim(file);
            flag = 1;
            char *args[64];
            parse(file, args);//解析command
            execute(args,asynchoronus);//执行
        }
      
        int old_stdout = dup(1);
        FILE *fp1 = freopen(output, "w+", stdout);
        if(strcmp(argv[0],"ls")==0)
        {ls(argv);printf("self-function!");}
        else if (execvp(argv[0], argv) < 0)
            printf("error:in exec\n");
        fclose(stdout);
        FILE *fp2 = fdopen(old_stdout, "w");
        *stdout = *fp2;
        exit(0);
    }
    else
    {
        if(!asynchoronus)
        while (wait(&status) != pid)
            ;
    }
}

void execute_input(char **argv, char *output,int asynchoronous)
{
    pid_t pid;
    int fd;
    char *file;
    int flag = 0;
    int status;
    if ((pid = fork()) < 0)
    {
        printf("error:fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        if (strstr(output, "<") > 0) //输入重定向
        {
            char *p = strtok_r(output, "<", &file);
            file = trim(file);
            flag = 1;
            fd = open(output, O_RDONLY);
            if (fd < 0)
            {
                printf("No such file or directory.");
                exit(0);
            }
            output = file;//指令
        }
        if (strstr(output, ">") > 0)//输出重定向
        {
            char *p = strtok_r(output, ">", &file);
            file = trim(file);
            flag = 1;
            fflush(stdout);
            int old_stdout = dup(1);
            FILE *fp1 = freopen(file, "w+", stdout);
            execute_input(argv, output,asynchoronous);
            fclose(stdout);
            FILE *fp2 = fdopen(old_stdout, "w");
            *stdout = *fp2;
            exit(0);
        }
        if (strstr(output, "|") > 0) //管道操作
        {
            char *p = strtok_r(output, "|", &file);
            file = trim(file);
            flag = 1;
            char *args[64];
            parse(file, args);//解析命令
            //创建管道
            int pfds[2]; 
            pid_t pid, pid2;
            int status, status2;
            pipe(pfds);
            int fl = 0;
            if ((pid = fork()) < 0)
            {
                printf("error:fork failed\n");
                exit(1);
            }
            if ((pid2 = fork()) < 0)
            {
                printf("error:fork failed\n");
                exit(1);
            }
            if (pid == 0 && pid2 != 0)
            {
                /*   第一个命令
                *关闭标准输出，并将管道的写端复制到标准输出，关闭不需要的管道端口和文件描述符。
                *然后将第一个命令的输入重定向到指定的文件，使用execvp函数执行第一个命令
                */
                close(1);
                dup(pfds[1]);
                close(pfds[0]);
                close(pfds[1]);
                fd = open(output, O_RDONLY);
                close(0);
                dup(fd);
                if (execvp(argv[0], argv) < 0)
                {
                    close(pfds[0]);
                    close(pfds[1]);
                    printf("error:in exec\n");
                    fl = 1;
                    exit(0);
                }
                close(fd);
                exit(0);
            }
            else if (pid2 == 0 && pid != 0 && fl != 1)
            {
                /*
                *关闭标准输入，并将管道的读端复制到标准输入，关闭不需要的管道端口和文件描述符。
                *然后使用execvp函数执行第二个命令
                */
                close(0);
                dup(pfds[0]);
                close(pfds[1]);
                close(pfds[0]);
                if (execvp(args[0], args) < 0)
                {
                    close(pfds[0]);
                    close(pfds[1]);
                    printf("error:in exec\n");
                    exit(0);
                }
            }
            else
            {
                close(pfds[0]);
                close(pfds[1]);
                if(!asynchoronous){
                while (wait(&status) != pid)
                    ;
                while (wait(&status2) != pid2)
                    ;}
            }
            exit(0);
        }
        fd = open(output, O_RDONLY);
        close(0);
        dup(fd);
        if (execvp(argv[0], argv) < 0)
        {
            printf("error:in exec\n");
        }
        close(fd);
        exit(0);
    }
    else
    {   if(!asynchoronous)
        while (wait(&status) != pid)
            ;
    }
}


//执行管道操作
void execute_pipe(char **argv, char *output,int asynchoronous)
{
    int pfds[2], pf[2], flag;
    char *file;
    pid_t pid, pid2, pid3;
    int status, status2, old_stdout;
    pipe(pfds); //create pipe
    //pfds[0]:read        pfds[1]:write
    int blah = 0;
    char *args[64];
    char *argp[64];
    int fl = 0;
    if ((pid = fork()) < 0)
    {
        printf("error:fork failed\n");
        exit(1);
    }
    if ((pid2 = fork()) < 0)
    {
        printf("error:fork failed\n");
        exit(1);
    }
    if (pid == 0 && pid2 != 0)
    {
        close(1);
        dup(pfds[1]);
        close(pfds[0]);
        close(pfds[1]);
        if (execvp(argv[0], argv) < 0) //run the command
        {
            close(pfds[0]);
            close(pfds[1]);
            printf("error:in exec\n");
            fl = 1;
            kill(pid2, SIGUSR1);
            exit(0);
        }
    }
    else if (pid2 == 0 && pid != 0)
    {
        if (fl == 1)
        {
            exit(0);
        }
        if (strstr(output, "<") > 0)
        {
            char *p = strtok_r(output, "<", &file);
            file = trim(file);
            flag = 1;
            parse(output, args); //divide output to the array args
            execute_input(args, file,asynchoronous);
            close(pfds[0]);
            close(pfds[1]);
            exit(0);
        }
        if (strstr(output, ">") > 0)
        {
            char *p = strtok_r(output, ">", &file);
            file = trim(file);
            flag = 1;
            parse(output, args);
            blah = 1;
        }

        else
        {
            parse(output, args);
        }
        close(0);
        dup(pfds[0]);
        close(pfds[1]);
        close(pfds[0]);
        if (blah == 1)
        {
            old_stdout = dup(1);
            FILE *fp1 = freopen(file, "w+", stdout);
        }
        if (execvp(args[0], args) < 0)
        {
            fflush(stdout);
            printf("error:in exec %d\n",pid);
            kill(pid, SIGUSR1);
            close(pfds[0]);
            close(pfds[1]);
        }
        fflush(stdout);
        //printf("HERE");
        if (blah == 1)
        {
            fclose(stdout);
            FILE *fp2 = fdopen(old_stdout, "w");
            *stdout = *fp2;
        }
    }
    else
    {
        close(pfds[0]);
        close(pfds[1]);
        if(!asynchoronous){
        while (wait(&status) != pid)
            ;
        while (wait(&status2) != pid2)
            ;}
    }
}

//解析多管道命令，然后调用execute_muti_cmd()函数去执行
void execute_pipe2(char *left,char *command,int asynchoronous)
{
    //printf("left=%s command=%s\n",left,command);
   
    //计算command中有多少管道命令
    char *tmp=command;
    int count=1;
    int num_cmd;
    while(*tmp!='\0')
    {
        //printf("entering while loop!\n");
        if(*tmp=='|')
        count++;
        tmp++;
    }
    num_cmd=count+1;
    //printf("num of cmd:%d\n",num_cmd);
    //新建一个char ***argus，存放所有的管道命令
    char ***argus=(char***)malloc(sizeof(char **)*num_cmd);
    //parse第一个指令
    char **argu1=(char**)malloc(sizeof(char*)*64);
    parse(left,argu1);
    argus[0]=argu1;
    //parse之后的每一个指令，将其放到 char *** argus内
    for(int i=1;i<num_cmd;i++)
    {
        char **argu=(char**)malloc(sizeof(char *)*64);
        char *cmd=(char*)malloc(strlen(command));
        char *p = strtok_r(command, "|", &cmd);
        command=cmd;
        parse(p,argu);
        argus[i]=argu;
    }
    argus[num_cmd]=NULL;
    //调用函数执行
    execute_muti_pipe(argus,asynchoronous);

}
//获取char***argus中的元素的个数，在多管道指令中也就是获取指令的数目
int get_len3(char ***argus){
    int count=0;
    while(*argus!=NULL)
    {
        count++;
        argus++;
    }
    return count;
}

//多管道指令的执行
void execute_muti_pipe(char *** argus,int asynchoronous)
{
    //printf("excute_muti_pipe\n");
    int status;
    int i;
    int num_cmd=get_len3(argus); //调用get_len3()函数获取指令的数目
    int num_pipe=num_cmd-1;     //管道的数目就是指令的数目-1
    int *pipes=(int *)malloc(sizeof(int)*2*num_pipe); //动态分配一个长度为2*num_pipe的数组
    int  re_in=0,re_out=0; //表示第一个指令是否有输入重定向 管道指令是否存在输出重定向
    char *in_file=NULL; char *out_file=NULL;
    int ori_stdin=dup(0);
    int ori_stdout=dup(1);
    //检查第一个指令是否存在输入重定向
    int a=0; int re_loc=0;
    for(int z=0;z<get_len2(argus[0]);z++)
    {
        if(argus[0][z][0]=='<' && argus[0][z+1])
        {
            a=z; re_in=1;
            in_file=argus[0][z+1];
            argus[0][z]=NULL;
            break;
        }else if(argus[0][z][0]=='<'&& argus[0][z][1]!='\0')
        {
            a=z; re_in=1;
            in_file=++argus[0][z];
            argus[0][z]=NULL;
            break;
        }
    }
    //检查最后一个指令是否存在输出重定向
    for(int z=0;z<get_len2(argus[num_cmd-1]);z++)
    {
        if(argus[num_cmd-1][z][0]=='>' && argus[num_cmd-1][z+1])
        {
            re_out=1;
            out_file=argus[num_cmd-1][z+1];
            argus[num_cmd-1][z]=NULL;
            break;
        }else if(argus[num_cmd-1][z][0]=='>' && argus[num_cmd-1][z][1]!='\0')
        {
            re_out=1;
            out_file=++argus[num_cmd-1][z];
            argus[num_cmd-1][z]=NULL;
        }
    }
    //printf("re_in:%s",in_file);
    //printf("re_out:%s",out_file);
    //循环创建num_pipe个管道
    for(int j=0;j<num_pipe;j++)
    pipe(pipes+2*j);
    //printf("create %d pipes\n",num_pipe);

   
    //创建子进程，执行所有的管道命令 此处将第一个指令和最后一个指令单独处理
    // 创建子进程，执行所有的管道命令
    for (int i = 0; i < num_cmd; i++) {
        if (fork() == 0) {
            if(i==num_cmd-1)
            if(re_out){
            int output_fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (output_fd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
            }   
            dup2(output_fd, 1);
            close(output_fd);
            }
            if(i==0)
            {
                //printf("i==0 argu[0][1]:%s argu[0][2]:%s argu[0][3]:%s\n",argus[0][1],argus[0][2],argus[0][3]);
                 if(re_in){
                int input_fd = open(in_file, O_RDONLY);
                if (input_fd < 0) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(input_fd, 0);
                close(input_fd);
    }
            }
            // 如果不是第一个命令，则重定向标准输入到前一个管道的读取端
            if (i != 0) {
                dup2(pipes[(i - 1) * 2], 0);
            }
            // 如果不是最后一个命令，则重定向标准输出到当前管道的写入端
            if (i != num_cmd - 1) {
                dup2(pipes[i * 2 + 1], 1);
            }
            // 关闭所有管道描述符
            for (int j = 0; j < 2 * num_pipe; j++) {
                close(pipes[j]);
            }
            // 执行命令
            
            if (execvp(argus[i][0], argus[i]) < 0) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
    }

    // 关闭所有管道描述符
    for (int i = 0; i < 2 * num_pipe; i++) {
        close(pipes[i]);
    }
    free(pipes);

    // 等待所有子进程结束      
    if(!asynchoronous){
    for (int i = 0; i < num_cmd; i++) {
        wait(&status);
        //printf("Waiting for process %d to finish\n", i);
    }
    }
     // 恢复标准输入和标准输出
    dup2(ori_stdin, 0);
    dup2(ori_stdout, 1);
    close(ori_stdin);
    close(ori_stdout);
}