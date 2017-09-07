/*
有50个点，m条边，找出欧拉回路。
先判断度，再判断所有度不为0的点是否联通，
然后用dfs2逆序输出欧拉回路
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 60
#define M 1010
int head[N],to[M*2],pre[M*2],du[N];
bool vis[N],f[M*2];//f[i]表示编号为i的边是否已被遍历
int m,e;
void addedge(int x,int y)
{
    to[e]=y;pre[e]=head[x];f[e]=true;head[x]=e++;
}
void dfs1(int x)
{
    vis[x]=true;
    int y;
    for(int i=head[x];i!=-1;i=pre[i])
    {
        y=to[i];
        if(!vis[y]) dfs1(y);
    }
}
bool check()
{
    for(int i=1;i<=50;++i)
        if(du[i]&1) return false;
    memset(vis,0,sizeof(vis));
    dfs1(1);
    for(int i=1;i<=50;++i)
        if(du[i]&&!vis[i]) return false;
    return true;
}
void dfs2(int x)//
{
    int y;
    for(int i=head[x];i!=-1;i=pre[i])
    {
        if(!f[i]) continue;
        f[i]=f[i^1]=false;
        y=to[i];
        dfs2(y);
        printf("%d %d\n",y,x);
    }
}
int main()
{
    int ca;
    scanf("%d",&ca);
    for(int cas=1;cas<=ca;++cas)
    {
        scanf("%d",&m);
        memset(du,0,sizeof(du));
        memset(head,-1,sizeof(head));
        e=0;
        int x,y;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&y);
            addedge(x,y);addedge(y,x);
            ++du[x];++du[y];
        }
        if(cas>1) printf("\n");
        printf("Case #%d\n",cas);
        if(check()) dfs2(1);
        else printf("some beads may be lost\n");
    }
    return 0;
}
