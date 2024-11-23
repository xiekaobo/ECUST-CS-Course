#include<bits/stdc++.h>
using namespace std;
int main()
{
    FILE *input_file;
    FILE *output_file;
    int T[2000][2000][200]={0};
    int a[1000],b[1000],n,i,j,k,Min=99999999,asum=0,bsum=0,m=0;
    input_file = fopen("input.txt", "r");
    fscanf(input_file,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(input_file,"%d",&a[i]);
        asum+=a[i];
    }
    for(i=1;i<=n;i++)
    {
        fscanf(input_file,"%d",&b[i]);
        bsum+=b[i];
    }
    fclose(input_file);
    for(k=1;k<=n;k++)
    {
        for(i=0;i<=asum;i++)
        {
            for(j=0;j<=bsum;j++)
            {
                if (i>=a[k]&&T[i-a[k]][j][k-1]==1)
                {
                    T[i][j][k] = 1;
                }
                if (j>=b[k]&&T[i][j-b[k]][k-1]==1)
                {
                    T[i][j][k] = 1;
                }
        }
    }
    }
    for(i=0;i<=asum;i++)
    {
        for(j=0;j<=bsum;j++)
        {
            if(T[i][j][n]==1)
            {
                m=i>j?i:j;
                if(k<Min) Min=m;
            }
        }
    }
    output_file = fopen("output.txt", "w");
    fprintf(output_file,"%d",Min);
    fclose(output_file);
    return 0;
}
