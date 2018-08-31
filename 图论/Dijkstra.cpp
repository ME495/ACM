/*
使用优先队列Dijkstra算法
复杂度O(ElogE)
注意对vector<Edge> E[MAXN]进行初始化后加边
*/
 
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<fstream>
#include<string.h>
using namespace std;
 
const int INF=0x3f3f3f3f;
const int MAXN=1000010;
 
struct qnode
{
    int v;
    int c;
    qnode(int _v=0,int _c=0):v(_v),c(_c){}
    bool operator <(const qnode &r)const
    {
        return c>r.c;
    }
};
 
struct Edge
{
    int v,cost;
    Edge(int _v=0,int _cost=0):v(_v),cost(_cost){}
};
 
vector<Edge> E[MAXN];
bool vis[MAXN];
int dist[MAXN];
 
void Dijkstra(int n,int start)//点的编号从1开始
{
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) dist[i]=INF;
    priority_queue<qnode> que;
    while(!que.empty()) que.pop();
    dist[start]=0;
    que.push(qnode(start,0));
    qnode tmp;
    while(!que.empty())
    {
        tmp=que.top();
        que.pop();
        int u=tmp.v;
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<E[u].size();i++)
        {
            int v=E[tmp.v][i].v;
            int cost=E[u][i].cost;
            if(!vis[v]&&dist[v]>dist[u]+cost)
            {
                dist[v]=dist[u]+cost;
                que.push(qnode(v,dist[v]));
            }
        }
    }
}
 
void addedge(int u,int v,int w)
{
    E[u].push_back(Edge(v,w));
}
 
int main()
{
    for(int i=0;i<=MAXN;i++)
        if(!E[i].empty())
            E[i].clear();
    freopen("in.txt","r",stdin);
    int n;
    cin>>n;
    int e;
    cin>>e;
    int u,v,w;
    for(int i=1;i<=e;i++)
    {
        cin>>u>>v>>w;
        addedge(u,v,w);
    }
    Dijkstra(n,1);
    for(int i=1;i<=n;i++)
        cout<<dist[i]<<" ";
    cout<<endl;
    return 0;
}
