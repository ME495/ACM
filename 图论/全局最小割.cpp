//复杂度(n^3)，适合稠密图，稀疏图可以用堆优化的算法
//点下标从0开始
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 510, INF = 0x3f3f3f3f;    
int mpa[N][N], dis[N], v[N];//v数组是马甲数组，dis数组用来表示该点与A集合中所有点之间的边的长度之和    
bool vis[N];//用来标记是否该点加入了A集合    
int stoer_wagner(int n)    
{    
    int res = INF;    
    for(int i = 0; i < n; i++) v[i] = i;//初始马甲为自己    
    while(n > 1)    
    {    
        int k, pre = 0;//pre用来表示之前加入A集合的点，我们每次都以0点为第一个加入A集合的点    
        memset(vis, 0, sizeof vis);    
        memset(dis, 0, sizeof dis);  
        vis[v[pre]] = true;  ////  
        for(int i = 1; i < n; i++)    
        {    
            k = -1;    
            for(int j = 1; j < n; j++)//根据之前加入的点，要更新dis数组，并找到最大的dis    
                if(! vis[v[j]])    
                {    
                    dis[v[j]] += mpa[v[pre]][v[j]];    
                    if(k == -1 || dis[v[k]] < dis[v[j]]) k = j;    
                }    
            vis[v[k]] = true;//标记该点已经加入A集合    
            if(i == n - 1)//最后一次加入的点就要更新答案了    
            {    
                res = min(res, dis[v[k]]);    
                for(int j = 0; j < n; j++)//将该点合并到pre上，相应的边权就要合并    
                {    
                    mpa[v[pre]][v[j]] += mpa[v[j]][v[k]];    
                    mpa[v[j]][v[pre]] += mpa[v[j]][v[k]];    
                }    
                v[k] = v[--n];//删除点v[k]，把最后一个点扔到v[k]上    
            }    
            pre = k;    
        }    
    }    
    return res;    
}    
int main()    
{    
    int n, m, a, b, c;    
    while(~ scanf("%d%d", &n, &m))    
    {    
        memset(mpa, 0, sizeof mpa);    
        for(int i = 0; i < m; i++)    
        {    
            scanf("%d%d%d", &a, &b, &c);    
            mpa[a][b] += c, mpa[b][a] += c;//合并重边
        }    
        printf("%d\n", stoer_wagner(n));    
    }    
    return 0;    
} 

//复杂度(nmlogm)，因此适合稀疏图，稠密图直接用没有堆优化的算法
//点下标从1开始
typedef pair<int, int> pii;
const int N = 3000 + 10, M = 20000 + 10, INF = 0x3f3f3f3f;
struct edge
{
    int to, cost, next;
}g[M];
int cnt, head[N], link[N];//link类似于链表
int par[N];
int dis[N];//dis数组用来表示该点与A集合中所有点之间的边的长度之和
bool vis[N];//用来标记是否该点加入了A集合  
void init(int n)
{
    for(int i = 1; i <= n; i++) par[i] = i;
    cnt = 0;
    memset(head, -1, sizeof head);
    memset(link, -1, sizeof link);
}
void add_edge(int v, int u, int cost)
{
    g[cnt].to = u, g[cnt].cost = cost, g[cnt].next = head[v], head[v] = cnt++;
}
int ser(int x)
{
    int r = x, i = x, j;
    while(r != par[r]) r = par[r];
    while(par[i] != r) j = par[i], par[i] = r, i = j;
    return r;
}
void unite(int x, int y)
{//把y合并到x中，反过来也对
    int p = x;
    while(~ link[p]) p = link[p];
    link[p] = y;
    par[y] = x;
}
int min_cut_phase(int n, int &s, int &t)
{
    memset(vis, 0, sizeof vis);
    memset(dis, 0, sizeof dis);
    priority_queue<pii> que;
    t = 1;
    while(--n)
    {
        vis[s = t] = true;
        for(int i = s; ~i; i = link[i])//更新dis数组，把合并到s中的点全部取出来
            for(int j = head[i]; ~j; j = g[j].next)
            {
                int v = ser(g[j].to);//g[j].to可能已经合并到其他点上了
                if(! vis[v]) que.push(make_pair(dis[v] += g[j].cost, v));
            }
        t = 0;
        while(! t)
        {
            if(que.empty()) return 0; //图不联通
            pii p = que.top(); que.pop();
            if(dis[p.second] == p.first) t = p.second;
        }
    }
    return dis[t];
}
int stoer_wagner(int n)
{
    int ans = INF, s, t;
    for(int i = n; i > 1; i--)
    {
        ans = min(ans, min_cut_phase(i, s, t));
        if(ans == 0) break;
        unite(s, t);
    }
    return ans;
}
int main()
{
    int n, m;
    while(~ scanf("%d%d", &n, &m))
    {
        init(n);
        int a, b, c;
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, c), add_edge(b, a, c);
        }
        printf("%d\n", stoer_wagner(n));
    }
    return 0;
}