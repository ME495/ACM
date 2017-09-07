#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 1010
int n,m;
int link[N],tlink[N],vis[N];
/*
visx[]和visy[]分别表示X集合和Y集合的点是否被覆盖，
在求最小点覆盖时才需要用到
*/
int visx[N],visy[N];
vector<int>g[N];
int a[N],b[N];
bool dfs(int x,int fa)
{
    int y;visx[x]=true;
    for(int i=0;i<g[x].size();++i)
    {
        y=g[x][i];
        if(vis[y]!=fa)
        {
            vis[y]=fa;visy[y]=true;
            if(link[y]==-1||dfs(link[y],fa))
            {
                link[y]=x;tlink[x]=y;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int x,y,k;
    while(scanf("%d%d%d",&n,&m,&k),n)
    {
        memset(link,-1,sizeof(link));
        memset(tlink,-1,sizeof(tlink));
        memset(vis,-1,sizeof(vis));
        for(int i=1;i<=n;++i) g[i].clear();
        for(int i=1;i<=k;++i)
        {
            scanf("%d%d",&x,&y);
            g[x].push_back(y);
        }
        int ans=0;
        for(int i=1;i<=n;++i)
            if(dfs(i,i)) ++ans;
        printf("%d ",ans);
        /*
        查找最小点覆盖的方案，
        满足visx[x]==false或visy[y]==true
        的点x或y就是最小的点覆盖
        */
        memset(visx,0,sizeof(visx));
        memset(visy,0,sizeof(visy));
        for(int i=1;i<=n;++i)
            if(tlink[i]==-1) dfs(i,n+1);
        for(int i=1;i<=n;++i)
            if(!visx[i]) printf("r%d ",i);
        for(int i=1;i<=m;++i)
            if(visy[i]) printf("c%d ",i);
        printf("\n");
    }
    return 0;
}

