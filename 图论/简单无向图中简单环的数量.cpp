/*
题意：求出一个n(1<=n<=19)个点m个边的图（无重边，无自环），求简单环有多少（环中没有重复点和边），此题的环不包含两个点的环。
思路：dp[s][i]表示以s的最小编号为起点，以i为终点，包含s中所有点的简单路径数量。
*/
#include <bits/stdc++.h>
using namespace std;
#define N 19
typedef long long ll;
ll dp[1<<N][N];
int pos[1<<N];
bool g[N][N];
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    int x,y;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&x,&y);
        --x;--y;
        g[x][y]=g[y][x]=true;
    }
    ll ans=0;
    for(int i=0;i<n;++i) dp[1<<i][i]=1;
    for(int s=1;s<(1<<n);++s)
    {
        int beg=0;
        for(int i=0;i<n;++i)
            if((s>>i)&1)
            {
                beg=i;break;
            }
        for(int end=beg;end<n;++end)
            if((s>>end)&1)
            {
                for(int i=beg;i<n;++i)
                    if(!((s>>i)&1)&&g[end][i])
                    {
                        dp[s|(1<<i)][i]+=dp[s][end];
                    }
                if(g[beg][end]&&__builtin_popcount(s)>=3)
                    ans+=dp[s][end];
            }
    }
    cout<<ans/2<<endl;
    return 0;
}
