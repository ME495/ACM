/*
首先我们要知道，对于一个不存在负环的图，
从起点到任意一个点最短距离经过的点最多只有 n 个
这样的话，
我们用 cnt[ i ] 表示从起点（假设就是 1）到 i 的最短距离包含点的个数，
初始化 cnt[ 1 ] = 1，那么当我们能够用点 u 松弛点 v 时，
松弛时同时更新 cnt[ v ] = cnt[ u ] + 1，
若发现此时 cnt[ v ] > n，那么就存在负环。
还有一种方法是记录每个点的入队次数，
入队次数大于 n 就说明有负环，但是这样做一般都要比上面的方法慢。
举个例子，在一个由 n 个点构成的负环中，
这个方法要绕环 n 次，而上面的方法绕环 1 次就行了
代码（Yes 是存在负环，No 是不存在负环，图是联通的）：
*/
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10005
#define M 20005
using namespace std;
int n,m,t,oo;
int v[M],w[M],next[M];
int d[N],cnt[N],first[N];
bool flag,vis[N];
void add(int x,int y,int z)
{
        t++;
        next[t]=first[x];
        first[x]=t;
        v[t]=y;
        w[t]=z;
}
bool SPFA(int s)
{
        int x,y,i,j;
        queue<int>q;
        memset(d,127,sizeof(d));
        memset(vis,false,sizeof(vis));
        while(!q.empty())  q.pop();
        d[s]=0;
        cnt[s]=1;
        q.push(s);
        vis[s]=true;
        while(!q.empty())
        {
                x=q.front();
                q.pop();
                vis[x]=false;
                for(i=first[x];i;i=next[i])
                {
                        y=v[i];
                        if(d[y]>d[x]+w[i])
                        {
                                d[y]=d[x]+w[i];
                                cnt[y]=cnt[x]+1;
                                if(cnt[y]>n)
                                  return false;
                                if(!vis[y])
                                {
                                        q.push(y);
                                        vis[y]=true;
                                }
                        }
                }
        }
        return true;
}
int main()
{
        int x,y,z,i;
        scanf("%d%d",&n,&m);
        for(i=1;i<=m;++i)
        {
	        scanf("%d%d%d",&x,&y,&z);
                add(x,y,z);
                add(y,x,z);
        }
        flag=SPFA(1);
        if(!flag)  printf("Yes\n");
        else  printf("No\n");
        return 0;
}
