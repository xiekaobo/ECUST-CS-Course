#include"shell.h"
//去除字符串中的额外空格
char *trim(char *string) 
{
    int i = 0;
    int j = 0;
    char *ptr = malloc(sizeof(char *) * strlen(string));
    for (i = 0; string[i] != '\0'; i++)
        if (string[i] != ' ')
        {
            ptr[j] = string[i];
            j++;
        }
    ptr[j] = '\0';
    string = ptr;
    //printf("%s\n",string);
    //printf("%d\n",j);
    return string;
}