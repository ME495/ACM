/*
���0��n-1�Ĵζ�·
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
typedef pair<ll ,int> P ;///first �Ǵ�1��second�����· second ��·�ڱ��
vector<edge>G[maxn];///�ڽӱ�
ll dist[maxn];///���·
ll dist2[maxn];///�ζ�·
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
        P p=que.top();///���ȶ��� ����.top
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
            now.to--;///��Ŵ�0��ʼ
            G[from].push_back(now);
            swap(now.to,from);
            G[from].push_back(now);
        }
        solve();
    }
    return 0;
}
