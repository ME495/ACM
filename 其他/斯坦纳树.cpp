/*
���⣺����һ��n*m�ľ���ÿ��������һ��Ȩֵ��ѡ������K���㣬ȨֵΪ0����ʹ��K������ͨ����С˹̹�����������СȨֵ�ͣ������ѡ���ĵ㣬��'o'��ʾѡ���ĵ㣬K������'x'��ʾ
��⣺dp[i][j][s]��ʾ��(i,j)Ϊ������ѡ�㼯��״̬Ϊs����СȨֵ�ͣ�������ת�ƣ�
1��ö���Ӽ���dp[i][j][s]=min(dp[i][j][sta]+dp[i][j][s-sta]-a[i][j])������staΪs���Ӽ�
2���ɸ�ת�ƣ�dp[i][j][s]=min(dp[x][y][s]+dis{(i,j),(x,y)})��disΪ��������СȨֵ��
ʱ�临�Ӷȣ�ö���Ӽ��ĸ��Ӷ�=n*3^k��spfa�ĸ��Ӷ�=n*2^k,�ܸ��Ӷ�ΪO(n*3^k + n*2^k)
����������
4 4 
0 1 1 0 
2 5 5 1 
1 5 5 1 
0 1 1 0
���������
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
    if(x==i&&y==j) dfs(i,j,sta-s);//��������Ӽ�ת�ƣ��ٱ�������
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
                for(int s=(sta-1)&sta;s;s=(s-1)&sta)//ö���Ӽ�
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
���⣺��n���㣬m���ߣ�ÿ������Ȩֵ������k����ǰk��������ȡһ��ʹ��ͺ�k�����е�ĳһ���㣬ͨ�������ӣ����ұ�����һһ��Ӧ������С�Ĵ����Ƕ���
��⣺����K*2������С˹̹��������dp[i][s]��ʾ��iΪ������ѡ�㼯��״̬Ϊs����СȨֵ�ͣ�������ת�ƣ�
1��ö���Ӽ���dp[i][s]=min(dp[i][sta]+dp[i][s-sta])������staΪs���Ӽ�
2���ɸ�ת�ƣ�dp[i][s]=min(dp[j][sta]+dis(i,j))������dis(i,j)��ʾi��j����СȨֵ
ʱ�临�Ӷȣ�ö���Ӽ��ĸ��Ӷ�=n*3^k��spfa�ĸ��Ӷ�=n*2^k,�ܸ��Ӷ�ΪO(n*3^k + n*2^k)
������Ҫע��������������k�Ե�����һһ��Ӧ����ͨ��ϵ��Ҳ����˵������ɵĲ�һ����һ�ţ����п�����һƬɭ�֡���ô���ǿ����Ȱ���˹̹�����ķ�ʽ������DP��������е�״̬��Ȼ���ٽ���һ��״ѹdp��f[sta]=min(f[sta],f[s]+f[sta-s])������������ʾ��ǰ״̬��
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
bool check(int sta)//״̬����һһ��Ӧ
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
