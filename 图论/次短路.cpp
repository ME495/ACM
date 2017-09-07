/*
求从0到n-1的次短路
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
const ll inf=0x3f3f3f3f3f3f3f3fLL;
int N,R;
struct edge
{
    int to,cost;
};
typedef pair<ll ,int> P ;///first 是从1到second的最短路 second 是路口标号
vector<edge>G[maxn];///邻接表
ll dist[maxn];///最短路
ll dist2[maxn];///次短路
void solve()
{
    priority_queue<P ,vector<P>,greater<P> >que;
    fill(dist,dist+N,inf);
    fill(dist2,dist2+N,inf);
    dist[0]=0;
    //dist2[0]=0;
    que.push(P(0,0));
    while(!que.empty())
    {
        P p=que.top();///优先队列 ，用.top
        que.pop();
        int v=p.second;
        ll d=p.first;
        if(dist2[v]<d)continue;
        for(int i=0; i<G[v].size(); i++)
        {
            edge e=G[v][i];
            ll d2=d+e.cost;
            if(dist[e.to]>d2)
            {
                swap(dist[e.to],d2);
                que.push(P(dist[e.to],e.to));
            }
            if(dist2[e.to]>d2&&dist[e.to]<d2)
            {
                dist2[e.to]=d2;
                que.push(P(dist2[e.to],e.to));
            }
        }
    }
    printf("%lld\n",dist2[N-1]);
}
int main()
{
    int from;
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d%d",&N,&R);
        for(int i=0;i<N;++i) G[i].clear();
        edge now;
        for(int i=0;i<R;i++)
        {
            scanf("%d%d%d",&from,&now.to,&now.cost);
            from--;
            now.to--;///编号从0开始
            G[from].push_back(now);
            swap(now.to,from);
            G[from].push_back(now);
        }
        solve();
    }
    return 0;
}
