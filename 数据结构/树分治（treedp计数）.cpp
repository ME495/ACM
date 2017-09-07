/*
给定一棵n个节点的树，树上的权值要么为0，要么为1，
如果一条路径上的0和1数量相同且路径上存在一个点（称为休息点）（非路径的端点），
在这个点的左边路径上0和1的数量相等，右边路径上的0和1的数量也相等，
则称这条路径符合条件，问符合条件的路有多少条。
解：先把树上的权值0变成-1，
在计数的时候，运用treedp的思想，
在当前根中，
la[x][0/1]表示当前根中以前访问的子树到根的路径权值为x的没有/有休息点的节点数量
g[x][0/1]表示当前根中现在访问的节点的子树到根的路径权值为x的没有/有休息点的节点数量
点的编号为1~n
*/
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
#define N 100010
typedef long long ll;
using namespace std;
struct node{
    int x,y;
    node(int xx,int yy)
    {
        x=xx,y=yy;
    }
};
vector<node> lin[N];
vector<int> d;
int sz[N],f[N];//sz[x]-->x的树大小，f[x]-->x最大子树的节点数；
int n;
int rt;
int vis[N],dis[N],g[N*2][2],la[N*2][2],s[N*2];
ll ans,sum;
int size;
int aa,bb,cc,md;
void getrt(int x,int fa)//利用*sz,*f求重心
{
    sz[x]=1;
    f[x]=0;
    for(int i=0;i<lin[x].size();i++)
    {
        int u=lin[x][i].x;
        if(vis[u]||u==fa) continue;
        getrt(u,x);
        sz[x]+=sz[u];
        f[x]=max(sz[u],f[x]);
    }
    f[x]=max(f[x],size-sz[x]);//!  x最大子树的节点数=max(与此子树大小－f[x],f[x])
    if(f[x]<f[rt]) rt=x;
}
void getdis(int x,int fa)//一遍dfs求距离＋求重心的一点预处理sz[x],求子树大小size
{
    sz[x]=1;
    for(int i=0;i<lin[x].size();i++)
    {
        int u=lin[x][i].x;
        if(vis[u]||u==fa) continue;
        getdis(u,x);
        sz[x]+=sz[u];
    }
}
void dfs(int x,int fa,int w)//求出g[][]
{
    //printf("%d %d ",x,w);
    md=max(md,max(w,-w));
    if(s[w+N]) ++g[w+N][1];
    else ++g[w+N][0];
    //printf("%d %d !!\n",g[w+N][0],g[w+N][1]);
    ++s[w+N];
    int y;
    for(int i=0;i<lin[x].size();++i)
    {
        y=lin[x][i].x;
        if(vis[y]||y==fa) continue;
        dfs(y,x,w+lin[x][i].y);
    }
    --s[w+N];
}
ll cal(int x)
{
    //printf("%d ----------\n",x);
    int y;
    ll tmp=0;
    int mdd=0;
    for(int i=0;i<lin[x].size();++i)
    {
        y=lin[x][i].x;
        if(vis[y]) continue;
        md=0;
        dfs(y,x,lin[x][i].y);
        mdd=max(mdd,md);
        tmp+=g[N][1]+(ll)g[N][0]*la[N][0];
        for(int j=-md;j<=md;++j)
        {
            tmp+=(ll)g[N-j][0]*la[N+j][1]+(ll)g[N-j][1]*la[N+j][0]+(ll)g[N-j][1]*la[N+j][1];
            //printf("%d %d %d %d %d %d ??\n",y,j,g[N+j][0],g[N+j][1],la[N+j][0],la[N+j][1]);
        }
        for(int j=N-md;j<=N+md;++j)
        {
            la[j][1]+=g[j][1];
            la[j][0]+=g[j][0];
            g[j][1]=g[j][0]=0;
        }
    }
    for(int i=N-mdd;i<=N+mdd;++i)
        la[i][0]=la[i][1]=0;
    //printf("%d ?\n",tmp);
    return tmp;
}
void solve(int x)
{
    ans+=cal(x);
    vis[x]=1;
    for(int i=0;i<lin[x].size();i++)
    {
        int u=lin[x][i].x;
        if(vis[u]) continue;
        getdis(u,0);
        size=sz[u];//!!! getdis中已经处理子树的全大小
        getrt(u,rt=0);
        solve(rt);
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            vis[i]=0;
            lin[i].clear();
        }
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&aa,&bb,&cc);
            if(cc==0) cc=-1;
            lin[aa].push_back(node(bb,cc));
            lin[bb].push_back(node(aa,cc));
        }
        ans=0;
        f[0]=n+1;size=n;
        getrt(1,rt=0);
        solve(rt);
        printf("%lld\n",ans);
    }
}
