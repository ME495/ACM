#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 10010
#define lson node<<1,s,mid
#define rson node<<1|1,mid+1,t
#define lnode node<<1
#define rnode node<<1|1
int son[N],sz[N],top[N],ti[N],dep[N],fa[N];
int seg[N*4];
int a[N],b[N],w[N];
int n,ca,cnt;
vector<int>g[N];
void dfs1(int x,int depth,int pa)
{
    dep[x]=depth;sz[x]=1;son[x]=0;fa[x]=pa;
    for(int i=0;i<g[x].size();++i)
    {
        int y=g[x][i];
        if(y==pa) continue;
        dfs1(y,depth+1,x);
        sz[x]+=sz[y];
        if(sz[y]>sz[son[x]]) son[x]=y;
    }
}
void dfs2(int x,int pa)
{
    ti[x]=++cnt;top[x]=pa;
    if(son[x]!=0) dfs2(son[x],top[x]);
    for(int i=0;i<g[x].size();++i)
    {
        int y=g[x][i];
        if(y!=son[x]&&y!=fa[x])
            dfs2(y,y);
    }
}
void build(int node,int s,int t)
{
    seg[node]=-0x7ffffff;
    if(s!=t)
    {
        int mid=s+t>>1;
        build(lson);
        build(rson);
    }
}
void updata(int node,int s,int t,int x,int w)
{
    if(s==t) seg[node]=w;
    else
    {
        int mid=s+t>>1;
        if(x<=mid) updata(lson,x,w);
        else updata(rson,x,w);
        seg[node]=max(seg[lnode],seg[rnode]);
    }
}
int query(int node,int s,int t,int l,int r)
{
    if(l<=s&&t<=r) return seg[node];
    int mid=s+t>>1,ans=-0x7ffffff;
    if(l<=mid) ans=max(ans,query(lson,l,r));
    if(mid<r) ans=max(ans,query(rson,l,r));
    return ans;
}
int lca(int x,int y)
{
    int ans=-0x7ffffff;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans=max(ans,query(1,2,n,ti[top[x]],ti[x]));
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    if(x!=y) ans=max(ans,query(1,2,n,ti[x]+1,ti[y]));
    return ans;
}
int main()
{
    scanf("%d",&ca);
    sz[0]=0;
    while(ca--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) g[i].clear();
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&a[i],&b[i],&w[i]);
            g[a[i]].push_back(b[i]);
            g[b[i]].push_back(a[i]);
        }
        cnt=0;
        dfs1(1,1,1);
        dfs2(1,1);
        build(1,2,n);
        for(int i=1;i<n;++i)
        {
            if(dep[a[i]]>dep[b[i]]) swap(a[i],b[i]);
            updata(1,2,n,ti[b[i]],w[i]);
        }
        char st[100];
        int x,y;
        while(1)
        {
            scanf("%s",st);
            if(st[0]=='D') break;
            if(st[0]=='Q')
            {
                scanf("%d%d",&x,&y);
                printf("%d\n",lca(x,y));
            }
            else
            {
                scanf("%d%d",&x,&y);
                updata(1,2,n,ti[b[x]],y);

            }
        }
        printf("\n");
    }
    return 0;
}
