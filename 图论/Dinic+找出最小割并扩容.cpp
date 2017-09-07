/*
大白P368，例题30
给你一些边和容量限制，问是否存在从1到N大小为C的流，
不存在的话能否通过增加某一条边的容量来实现。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;
#define N 210
#define M 500010
const ll inf=0x3f3f3f3f3f3f3f3f;
int head[N],from[M],to[M],pre[M],dis[N],q[N],vis[N];
ll cap[M],backup[M];
int n,m,e,cnt;
ll C;
vector<pair<int,int> > ans;
vector<int> cut;
void addedge(int x,int y,ll c)
{
	from[e]=x;to[e]=y;cap[e]=c;pre[e]=head[x];head[x]=e++;
	from[e]=y;to[e]=x;cap[e]=0;pre[e]=head[y];head[y]=e++;
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
ll dfs(int x,int t,ll f)
{
	if(x==t||f==0) return f;
	ll ans=0,flow;
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
ll dinic(ll c)
{
	ll ans=0;
	int s=1,t=n;
	while(bfs(s,t))
	{
		ans+=dfs(s,t,inf);
		if(ans>=C) break;
	}
	return ans;
}
void get_cut()//找出最小割的边
{
    cut.clear();
    for(int i=0;i<e;i+=2)
    {
        int x=from[i],y=to[i];
        if(dis[x]!=-1&&dis[y]==-1)
            cut.push_back(i);
    }
}
void solve(ll c)
{
    get_cut();
    for(int i=0;i<e;++i) backup[i]=cap[i];
    for(int i=0;i<cut.size();++i)
    {
        int id=cut[i];
        cap[id]+=c;//将边的容量增大c
        ll flow=dinic(c);
        if(flow>=c) ans.push_back(make_pair(from[id],to[id]));
        for(int j=0;j<e;++j) cap[j]=backup[j];//还原边
    }
}
int main()
{
    int ca=0;
	while(scanf("%d%d%lld",&n,&m,&C),n)
	{
	    e=0;
        memset(head,-1,sizeof(head));
        int x,y;ll z;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%lld",&x,&y,&z);
            addedge(x,y,z);
        }
        printf("Case %d: ",++ca);
        ll flow=dinic(C);
        if(flow>=C) printf("possible\n");
        else
        {
            ans.clear();
            solve(C-flow);
            if(ans.size())
            {
                sort(ans.begin(),ans.end());
                printf("possible option:");
                for(int i=0;i<ans.size();++i)
                {
                    printf("(%d,%d)",ans[i].first,ans[i].second);
                    if(i==ans.size()-1) printf("\n");
                    else printf(",");
                }
            }
            else printf("not possible\n");
        }
	}
	return 0;
}

