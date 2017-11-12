#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 20010
#define M 1000010
int inf=0x3f3f3f3f;
int head[N],to[M],pre[M],cap[M],dis[N],q[N],vis[N],cur[N];
int n,m,e,cnt;
void addedge(int x,int y,int c)
{
	to[e]=y;cap[e]=c;pre[e]=head[x];head[x]=e++;
	to[e]=x;cap[e]=0;pre[e]=head[y];head[y]=e++;
}
bool bfs(int s,int t)
{
	int l=0,r=0;
	memset(dis,-1,sizeof(dis));
	q[l]=s;dis[s]=0;
	int x,y;
	while(l<=r)
	{
		x=q[l++];
		for(int i=head[x];i!=-1;i=pre[i])
		{
			y=to[i];
			if(dis[y]!=-1||cap[i]==0) continue;
			dis[y]=dis[x]+1;
			if(y==t) return true;
			q[++r]=y;
		}
	}
	return false;
}
int dfs(int x,int t,int f)
{
	if(x==t||f==0) return f;
	int ans=0,flow;
	for(int &i=cur[x];i!=-1;i=pre[i])
	{
		if(dis[x]+1==dis[to[i]]&&(flow=dfs(to[i],t,min(f,cap[i])))>0)
		{
			cap[i]-=flow;cap[i^1]+=flow;ans+=flow;f-=flow;
			if(f==0) break;
		}
	}
	if(ans==0) dis[x]=-1;
	return ans;
}
int dinic(int s,int t)
{
	int ans=0,f;
	while(bfs(s,t))
	{
	    for(int i=0;i<=t;++i) cur[i]=head[i];
		ans+=dfs(s,t,inf);
	}
	return ans;
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        memset(head,-1,sizeof(head));
        e=0;
        int s=n+1,t=n+2;
        for(int i=1;i<=n;++i)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            addedge(s,i,a);addedge(i,t,b);
        }
        for(int i=1;i<=m;++i)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            addedge(x,y,z);addedge(y,x,z);
        }
        printf("%d\n",dinic(s,t));
    }
	return 0;
}
