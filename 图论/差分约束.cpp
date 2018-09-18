/*
差分约束系统：如果一个系统由n个变量和m个约束条件组成，其中每个约束条件形如 xj - xi<= bk ( i , j ∈ [1，n]，k ∈ [1，m])，则称其为差分约束系统。 
例如如下的约束条件： 
X1 - X2 <= 0 X1 - X5 <= -1 
X2 - X5 <= 1 X3 - X1 <= 5 
X4 - X1 <= 4 X4 - X3 <= -1 
X5 - X3 <= -3 X5 - X4 <= -3 
全都是两个未知数的差小于等于某个常数（大于等于也可以，因为左右乘以-1就可以化成小于等于）。这样的不等式组就称作差分约束系统。 
差分约束系统求解过程： 
1.新建一个图，N个变量看作N个顶点，M个约束条件作为M条边。每个顶点Vi分别对于一个未知量，每个有向边对应两个未知量的不等式。 
2.为了保证图的连通性，在图中新加一个节点Vs，图中每个节点Vi都能从Vs可达，建立边w(Vs，Vi) = 0。 
3.对于每个差分约束Xj - Xi <= Bk(这里是小于等于号)，则建立边w(Xi，Xj) = Bk。 
4.初始化Dist[] = INF，Dist[Vs] = 0. 
5.求解以Vs为源点的单源最短路径，推荐用SPFA，因为一般可能存在负值。 
如果图中存在负权回路，则该差分约束系统不存在可行解。 
Vs到某点如果不存在最短路径，即最短路为INF，则对于该点表示的变量可以取任意值，都能满足差分约束的要求，如果存在最短路径，则得到该变量的最大值。 
上述过程最终得到的解为满足差分约束系统各项的最大值。 
注意点： 
1. 如果要求最大值想办法把每个不等式变为标准 x - y <= k 的形式,然后建立一条从 y 到 x 权值为 k 的边，求出最短路径即可，变得时候注意 x - y < k => x - y <= k-1。 
2. 如果要求最小值的话，变为 x - y >= k 的标准形式，然后建立一条从 y到 x 权值为 k 的边，求出最长路径即可。 
3. 如果权值为正，用Dijkstra，SPFA，BellmanFord都可以，如果为负不能用Dijkstra，并且需要判断是否有负环，有的话就不存在。
*/
/*
POJ 3169
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 1010
#define M 20010
const int inf=0x3f3f3f3f;
int head[N],to[M],w[M],pre[M],num[N],d[N];
bool inque[N];
int n,m1,m2,e;
void addedge(int x,int y,int z)
{
    to[e]=y;w[e]=z;pre[e]=head[x];head[x]=e++;
}
int spfa(int s,int t,int K)//K为图中点的数量，用来判负环
{
    memset(inque,0,sizeof(inque));
    memset(d,0x3f,sizeof(d));//求最短路赋值为inf，最长路则赋值为-inf
    deque<int> que;
    que.push_back(s);d[s]=0;inque[s]=true;num[s]=1;
    while(!que.empty())
    {
        int x=que.front();
        que.pop_front();
        inque[x]=false;
        for(int i=head[x];i!=-1;i=pre[i])
        {
            int y=to[i],cost=d[x]+w[i];
            if(cost<d[y])//求最短路时用小于号，最长路则用大于号
            {
                d[y]=cost;
                num[y]=num[x]+1;
                if(num[y]>K) return -1;//如果起点到y之间点的数量超过K，形成负环
                if(!inque[y])
                {
                    inque[y]=true;
                    if(!que.empty()&&d[y]<=d[que.front()])//求最短路用小于等于号，求最长路用大于等于号
                        que.push_front(y);
                    else que.push_back(y);
                }
            }
        }
    }
    if(d[t]==inf) return -2;//s无法到达t，如果求最长路，则改为-inf
    else return d[t];
}
int main()
{
    scanf("%d%d%d",&n,&m1,&m2);
    memset(head,-1,sizeof(head));
    e=0;
    int x,y,z;
    for(int i=1;i<=m1;++i)
    {
        scanf("%d%d%d",&x,&y,&z);
        if(x>y) swap(x,y);
        addedge(x,y,z);
    }
    for(int i=1;i<=m2;++i)
    {
        scanf("%d%d%d",&x,&y,&z);
        if(x>y) swap(x,y);
        addedge(y,x,-z);
    }
    printf("%d\n",spfa(1,n,n));
    return 0;
}