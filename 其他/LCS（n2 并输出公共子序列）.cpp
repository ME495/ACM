#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 110
char s1[N],s2[N];
int dp[N][N],mark[N][N];
void LCS(char s1[],char s2[],int len1,int len2)
{
    for(int i=1;i<=len1;++i) mark[i][0]=1;
    for(int i=1;i<=len2;++i) mark[0][i]=-1;
    for(int i=1;i<=len1;++i)
        for(int j=1;j<=len2;++j)
            if(s1[i-1]==s2[j-1])
            {
                dp[i][j]=dp[i-1][j-1]+1;
                mark[i][j]=0;
            }
            else if(dp[i-1][j]>=dp[i][j-1])
            {
                dp[i][j]=dp[i-1][j];
                mark[i][j]=1;
            }
            else
            {
                dp[i][j]=dp[i][j-1];
                mark[i][j]=-1;
            }
}
void printLCS(int i,int j)
{
    if(!i&&!j) return;
    if(mark[i][j]==0)
    {
        printLCS(i-1,j-1);
        printf("%c",s1[i-1]);
    }
    else if(mark[i][j]==1)
    {
        printLCS(i-1,j);
        //printf("%c",s1[i-1]);
    }
    else
    {
        printLCS(i,j-1);
        //printf("%c",s2[j-1]);
    }
}
int main()
{
    while(scanf("%s%s",s1,s2)!=EOF)
    {
        memset(dp,0,sizeof(dp));
        int len1=strlen(s1),len2=strlen(s2);
        LCS(s1,s2,strlen(s1),strlen(s2));
        printLCS(len1,len2);
        printf("\n");
    }
    return 0;
}
