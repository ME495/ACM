#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1000010
int inf=0x3f3f3f3f;
int head[N],to[N*12],pre[N*12],cap[N*12],dis[N],cur[N],q[N],vis[N];
int n,m,e,cnt;
void addedge(int x,int y,int c)
{
	to[e]=y;cap[e]=c;pre[e]=head[x];head[x]=e++;
	to[e]=x;cap[e]=0;pre[e]=head[y];head[y]=e++;
}
inline int get_id(int x,int y)
{
	return x*m+y;
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
	for(int i=head[x];i!=-1;i=pre[i])
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
int solve()
{
	int ans=0,f,s=0,t=get_id(n-1,m-1);
	while(bfs(s,t))
	{
		for(int i=s;i<=t;++i) cur[i]=head[i];
		ans+=dfs(s,t,inf);
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	e=0;
	memset(head,-1,sizeof(head));
	int w;
	for(int i=0;i<n;++i)
		for(int j=0;j<m-1;++j)
		{
			scanf("%d",&w);
			addedge(get_id(i,j),get_id(i,j+1),w);
			addedge(get_id(i,j+1),get_id(i,j),w);
		}
	for(int i=0;i<n-1;++i)
		for(int j=0;j<m;++j)
		{
			scanf("%d",&w);
			addedge(get_id(i,j),get_id(i+1,j),w);
			addedge(get_id(i+1,j),get_id(i,j),w);
		}
	for(int i=0;i<n-1;++i)
		for(int j=0;j<m-1;++j)
		{
			scanf("%d",&w);
			addedge(get_id(i,j),get_id(i+1,j+1),w);
			addedge(get_id(i+1,j+1),get_id(i,j),w);
		}
	printf("%d\n",solve());
	return 0;
}
