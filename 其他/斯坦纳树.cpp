/*
给一个有n个节点带权完全图，编号从1~n，
现在有一个0节点，可以与m个节点相连，且给出了权值，
求0和这m个节点组成的最小斯坦纳树。
令s表示m个节点的子集，
dp[s][i]表示包含s中节点且以i为根的树的最小权值
dp[s][i]=min(dp[s1][i]+dp[s2][i],dp[s][j]+g[i][j]),
其中s1+s2=s,
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 60
int g[N][N],a[N],dp[(1<<10)+10][N];
int n,m;
const int inf=0x3f3f3f3f;
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&g[i][j]);
        int x,w;
        for(int i=1;i<=n;++i)
            g[0][i]=g[i][0]=inf;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&w);
            g[0][x]=g[x][0]=w;
            a[i]=x;
        }
        for(int k=0;k<=n;++k)
            for(int i=0;i<=n;++i)
                for(int j=0;j<=n;++j)
                    g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
        memset(dp,0x3f,sizeof(dp));
        for(int i=1;i<=m;++i)
            for(int j=0;j<=n;++j)
                dp[1<<i-1][j]=g[a[i]][j];
        for(int s=1;s<(1<<m);++s)
        {
            if(s&(s-1)==0) continue;
            for(int i=0;i<=n;++i)
                for(int ss=s;ss;ss=(ss-1)&s)
                    dp[s][i]=min(dp[s][i],dp[ss][i]+dp[s-ss][i]);
            for(int i=0;i<=n;++i)
                for(int j=0;j<=n;++j)
                    dp[s][i]=min(dp[s][i],dp[s][j]+g[i][j]);
        }
        printf("%d\n",dp[(1<<m)-1][0]);
    }
    return 0;
}
