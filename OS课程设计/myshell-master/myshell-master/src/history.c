//实现了history func
//history -c 清除
//history n 显示n条history
//history 显示所有history

#include"shell.h"
void save_history(char *hist[], int count) {
    //printf("Save_History:%d\n",count);
    //for(int i=0;i<count;i++)
    //printf("%d:%s\n",i,hist[i]);
    
    FILE *file = fopen(HISTORY_FILE_PATH, "w");
    if (file == NULL) {
        perror("fopen");
        return;
    }
    if(count!=0){
    for (int i = 0; i < count; i++) {
        
            fprintf(file, "%s\n", hist[i]);
        
    }
    }
    fclose(file);
}
void load_history(char *hist[], int *count) {
    FILE *file = fopen(HISTORY_FILE_PATH, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char line[1024];
    *count = 0;
    while (fgets(line, sizeof(line), file) != NULL && *count < hist_size) {
        line[strcspn(line, "\n")] = 0;  // 去掉换行符
        hist[*count] = strdup(line);
        (*count)++;
    }
    fclose(file);
}
//查看历史记录指令
void history(char **argv,char *hist[],int *filled,int *head)
{
    //history -c clear all history
   //printf("get_len2:%d\n",get_len2(hist));
   int n=get_len2(argv);
   if(n==1)
   {
    // 打印所有历史记录
            for (int i = 0; i < *filled; i++) {
                printf("%d  %s\n", i + 1, hist[i]);    
            }

   }else if(argv[1][0]=='-')
    {
        //存在选项
        if(argv[1][1]=='c')
        {
            *filled=0;
            *head=0;
            save_history(hist,0);
        }

    }else{
        //不存在选项
        //history n
        int n=atoi(argv[1]);
        int j=0;
        int d=*filled;
        for(int i=d-1;j<n;j++,i--)
        {
            printf("%d  %s\n",i,hist[i]);
        } 
        
    }
}