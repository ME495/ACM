/*
tarjan算法是离线算法，复杂度为O(n+Q)，使用了并查集+dfs的操作。中间的那个并查集操作的作用，只是将已经查找过的节点捆成一个集合然后再指向一个公共的祖先。另外，如果要查询LCA(a,b)，必须把(a,b)和(b,a)都加入邻接表。
*/
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define N 10010
vector<int> g[N],que[N];
int fa[N],in[N],anse[N],rank[N];
bool vis[N];
int n;
void init()
{
    memset(in,0,sizeof(in));
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;++i)
    {
        fa[i]=i;
        rank[i]=1;
        g[i].clear();
        que[i].clear();
    }
}
int findfa(int x)
{
    if(fa[x]==x) return x;
    else return fa[x]=findfa(fa[x]);
}
void Union(int x,int y)
{
    int fx=findfa(x),fy=findfa(y);
    fa[fx]=fy;
}
void LCA(int root)
{
    anse[root]=root;
    for(int i=0;i<g[root].size();++i)
    {
        int y=g[root][i];
        LCA(y);
        Union(root,y);
        anse[findfa(y)]=root;
    }
    vis[root]=true;
    for(int i=0;i<que[root].size();++i)
        if(vis[que[root][i]])
        {
            printf("%d\n",anse[findfa(que[root][i])]);
            return;

        }
}
int main()
{
    int ca,x,y,i;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d",&n);
        init();
        for(i=1;i<n;++i)
        {
            scanf("%d%d",&x,&y);
            if(x!=y)
            {
                g[x].push_back(y);
                ++in[y];
            }
        }
        scanf("%d%d",&x,&y);
        que[x].push_back(y);
        que[y].push_back(x);
        for(i=1;i<=n;++i)
            if(in[i]==0) break;
        LCA(i);
    }
    return 0;
}
