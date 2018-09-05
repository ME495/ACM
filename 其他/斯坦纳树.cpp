/*
题意：给定一个n*m的矩阵，每个方格有一个权值，选定其中K个点，权值为0，求使这K个点联通的最小斯坦纳树，输出最小权值和，并输出选出的点，用'o'表示选出的点，K个点用'x'表示
题解：dp[i][j][s]表示以(i,j)为根，已选点集合状态为s的最小权值和，有两种转移：
1、枚举子集：dp[i][j][s]=min(dp[i][j][sta]+dp[i][j][s-sta]-a[i][j])，其中sta为s的子集
2、由根转移：dp[i][j][s]=min(dp[x][y][s]+dis{(i,j),(x,y)})，dis为两点间的最小权值和
时间复杂度：枚举子集的复杂度=n*3^k，spfa的复杂度=n*2^k,总复杂度为O(n*3^k + n*2^k)
输入样例：
4 4 
0 1 1 0 
2 5 5 1 
1 5 5 1 
0 1 1 0
输出样例：
6 
xoox 
___o 
___o 
xoox

*/
#include <bits/stdc++.h>
using namespace std;
#define N 10
typedef pair<int,int> pii;
typedef pair<int,pair<int,int> > tup;
const int fx[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
const int inf=0x3f3f3f3f;
int dp[N][N][1<<N],g[N][N];
tup pre[N][N][1<<N];
int n,m,K;
queue<pii> que;
bool vis[N][N];
bool check(int x,int y)
{
    return 0<=x&&x<n&&0<=y&&y<m;
}
void spfa(int sta)
{
    while(!que.empty())
    {
        pii p=que.front();que.pop();
        vis[p.first][p.second]=false;
        for(int i=0;i<4;++i)
        {
            int x=p.first+fx[i][0],y=p.second+fx[i][1];
            if(!check(x,y)) continue;
            int cost=dp[p.first][p.second][sta]+g[x][y];
            if(cost<dp[x][y][sta])
            {
                dp[x][y][sta]=cost;
                pre[x][y][sta]={p.first,{p.second,sta}};
                if(!vis[x][y])
                {
                    vis[x][y]=true;
                    que.push({x,y});
                }
            }
        }
    }
}
void dfs(int x,int y,int sta)
{
    if(sta==0) return;
    tup tp=pre[x][y][sta];
    int i=tp.first,j=tp.second.first,s=tp.second.second;
    if(s==0) return;
    vis[i][j]=true;
    dfs(i,j,s);
    if(x==i&&y==j) dfs(i,j,sta-s);//如果是由子集转移，再遍历补集
}
int main()
{
    memset(dp,0x3f,sizeof(dp));
    scanf("%d%d",&n,&m);
    int x,y;K=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
        {
            scanf("%d",&g[i][j]);
            if(g[i][j]==0) dp[i][j][1<<K++]=0;
        }    
    for(int sta=1;sta<(1<<K);++sta)
    {
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            {
                for(int s=(sta-1)&sta;s;s=(s-1)&sta)//枚举子集
                    if(dp[i][j][sta]>dp[i][j][s]+dp[i][j][sta^s]-g[i][j])
                    {
                        dp[i][j][sta]=dp[i][j][s]+dp[i][j][sta^s]-g[i][j];
                        pre[i][j][sta]={i,{j,s}};
                    }
                if(dp[i][j][sta]!=inf)
                {
                    que.push({i,j});vis[i][j]=true;
                }
            }
        spfa(sta);
    }
    int ans=inf;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(dp[i][j][(1<<K)-1]<ans)
            {
                ans=dp[i][j][(1<<K)-1];x=i;y=j;
            }
    printf("%d\n",ans);
    memset(vis,0,sizeof(vis));
    dfs(x,y,(1<<K)-1);
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<m;++j)
            if(g[i][j]==0) printf("x");
            else
            {
                if(vis[i][j]) printf("o");
                else printf("_");
            }
        printf("\n");
    }
    return 0;
}

/*
题意：给n个点，m条边，每条边有权值，给定k，从前k个点中任取一个使其和后k个点中的某一个点，通过边连接，并且必须是一一对应，问最小的代价是多少
题解：先求K*2个点最小斯坦纳树，设dp[i][s]表示以i为根，已选点集合状态为s的最小权值和，有两种转移，
1、枚举子集：dp[i][s]=min(dp[i][sta]+dp[i][s-sta])，其中sta为s的子集
2、由根转移：dp[i][s]=min(dp[j][sta]+dis(i,j))，其中dis(i,j)表示i到j的最小权值
时间复杂度：枚举子集的复杂度=n*3^k，spfa的复杂度=n*2^k,总复杂度为O(n*3^k + n*2^k)
但是需要注意的是这道题是让k对点满足一一对应的联通关系，也就是说最后生成的不一定是一颗，而有可能是一片森林。那么我们可以先按照斯坦纳树的方式来进行DP，求出所有的状态，然后再进行一次状压dp，f[sta]=min(f[sta],f[s]+f[sta-s])，用两棵树表示当前状态。
*/
#include <bits/stdc++.h>
using namespace std;
#define N 60
#define M 2010
const int inf=0x3f3f3f3f;
int dp[N][1<<10],f[1<<10];
int head[N],to[M],pre[M],w[M];
int n,m,e,K;
queue<int> que;
bool vis[N];
void addedge(int x,int y,int z)
{
    to[e]=y;w[e]=z;pre[e]=head[x];head[x]=e++;
}
void spfa(int sta)
{
    while(!que.empty())
    {
        int x=que.front();
        que.pop();vis[x]=false;
        for(int i=head[x];i!=-1;i=pre[i])
        {
            int y=to[i],cost=dp[x][sta]+w[i];
            if(cost<dp[y][sta])
            {
                dp[y][sta]=cost;
                if(!vis[y])
                {
                    que.push(y);vis[y]=true;
                }
            }
        }
    }
}
bool check(int sta)//状态满足一一对应
{
    int cnt1=0,cnt2=0;
    for(int i=0;i<K;++i)
        if((sta>>i)&1) ++cnt1;
    for(int i=K;i<K*2;++i)
        if((sta>>i)&1) ++cnt2;
    return cnt1==cnt2;
}
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d%d%d",&n,&m,&K);
        for(int i=0;i<n;++i) head[i]=-1;
        e=0;
        int x,y,z;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            --x;--y;
            addedge(x,y,z);addedge(y,x,z);
        }
        for(int i=0;i<n;++i)
            for(int j=0;j<(1<<K*2);++j)
                dp[i][j]=inf;
        for(int i=0;i<K;++i) dp[i][1<<i]=0;
        for(int i=0;i<K;++i) dp[n-i-1][1<<i+K]=0;
        for(int sta=1;sta<(1<<K*2);++sta)
        {
            for(int i=0;i<n;++i)
            {
                for(int s=(sta-1)&sta;s;s=(s-1)&sta)
                    dp[i][sta]=min(dp[i][sta],dp[i][s]+dp[i][sta^s]);
                if(dp[i][sta]!=inf)
                {
                    que.push(i);vis[i]=true;
                }
            }
            spfa(sta);
        }
        for(int sta=1;sta<(1<<K*2);++sta)
        {
            f[sta]=inf;
            if(!check(sta)) continue;
            for(int i=0;i<n;++i)
                f[sta]=min(f[sta],dp[i][sta]);
            for(int s=(sta-1)&sta;s;s=(s-1)&sta)
                f[sta]=min(f[sta],f[s]+f[sta^s]);
        }
        if(f[(1<<K*2)-1]==inf) printf("No solution\n");
        else printf("%d\n",f[(1<<K*2)-1]);
    }
    return 0;
}
