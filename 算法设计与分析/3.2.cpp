#include<stdio.h>
#include<string.h>
bool ans=false;
char c[1000][1000];
bool flag[1000];
int cnt=0;
void dfs(char cl) {
    if(cl=='m')
        ans=true;
    else {
        for(int l=0; l<cnt; l++) {
            if(c[l][0]==cl&&flag[l]==0) {
                flag[l]=1;
                int t=strlen(c[l]);
                dfs(c[l][t-1]);
            }
        }
    }
}
int main() {
    while(scanf("%s",c[cnt++])!=EOF) {
        memset(flag,0,sizeof(flag));
        if(c[cnt-1][0]=='0') {
            dfs('b');
            printf("%s\n",ans?"Yes.":"No.");
            cnt=0;
            ans=false;
        }
    }
    return 0;
}
