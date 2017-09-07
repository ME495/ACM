#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 510
#define M 100010
const int inf=0x3f3f3f3f;
struct Edge{
    int x,c,w,nxt;
    Edge(){}
    Edge(int x,int c,int w,int nxt):x(x),c(c),w(w),nxt(nxt){}
}edge[M];
int head[N],dis[N],pre[N],pree[N];
bool inque[N];
int n,m,e,src,sink;
void addedge(int x,int y,int c,int w)
{
    edge[e]=Edge(y,c,w,head[x]);head[x]=e++;
    edge[e]=Edge(x,0,-w,head[y]);head[y]=e++;
}
bool spfa()
{
    int x,y,w;
    queue<int> que;
    memset(dis,0x3f,sizeof(dis));
    memset(inque,0,sizeof(inque));
    que.push(src);dis[src]=0;inque[src]=true;
    while(!que.empty())
    {
        x=que.front();
        que.pop();inque[x]=false;
        for(int i=head[x];i!=-1;i=edge[i].nxt)
        {
            y=edge[i].x;w=edge[i].w;
            if(edge[i].c>0&&dis[x]+w<dis[y])
            {
                dis[y]=dis[x]+w;pre[y]=x;pree[y]=i;
                if(!inque[y]&&y!=sink)
                {
                    que.push(y);inque[y]=true;
                }
            }
        }
    }
    return dis[sink]<inf;
}
int mincostflow()
{
    int ans=0,minc,x,d;
    while(spfa())
    {
        minc=inf;x=sink;
        while(x!=src)
        {
            minc=min(minc,edge[pree[x]].c);
            x=pre[x];
        }
        x=sink;
        while(x!=src)
        {
            edge[pree[x]].c-=minc;
            edge[pree[x]^1].c+=minc;
            x=pre[x];
        }
        ans+=minc*dis[sink];
    }
    return ans;
}
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d%d",&n,&m);
        e=0;
        memset(head,-1,sizeof(head));
        int x,y,w;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&x,&y,&w);
            addedge(x,n+y,1,w);
        }
        src=0;sink=2*n+1;
        for(int i=1;i<=n;++i) addedge(src,i,1,0);
        for(int i=n+1;i<=2*n;++i) addedge(i,sink,1,0);
        printf("%d\n",mincostflow());
    }
    return 0;
}
