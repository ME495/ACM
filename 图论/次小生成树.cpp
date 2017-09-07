/*
���⣺����ͼ������������С�������Ƿ�Ψһ�����Ψһ�Ļ������С��������Ȩֵ�ͣ��������Not Unique!

˼·��ֱ�����С���������С�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 111;
const int inf = 0x3f3f3f3f;
int Map[maxn][maxn];//�ڽӾ����ͼ
int Max[maxn][maxn];//��ʾ��С��������i��j������Ȩ
bool used[maxn][maxn];//�жϸñ��Ƿ������С������
int pre[maxn];
int dis[maxn];
void init(int n)
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j) Map[i][j] = 0;
            else Map[i][j] = inf;
}
void read(int m)
{
    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        Map[u][v] = Map[v][u] = w;
    }
}
int prim(int n)
{
    int ans = 0;
    bool vis[maxn];
    memset(vis, false, sizeof(vis));
    memset(used, false, sizeof(used));
    memset(Max, 0, sizeof(Max));
    for (int i = 2; i <= n; i++)
    {
        dis[i] = Map[1][i];
        pre[i] = 1;
    }
    pre[1] = 0;
    dis[1] = 0;
    vis[1] = true;
    for (int i = 2; i <= n; i++)
    {
        int min_dis = inf, k;
        for (int j = 1; j <= n; j++)
        {
            if (!vis[j] && min_dis > dis[j])
            {
                min_dis = dis[j];
                k = j;
            }
        }
        if (min_dis == inf) return -1;//�����������С������
        ans += min_dis;
        vis[k] = true;
        used[k][pre[k]] = used[pre[k]][k] = true;
        for (int j = 1; j <= n; j++)
        {
            if (vis[j]) Max[j][k] = Max[k][j] = max(Max[j][pre[k]], dis[k]);
            if (!vis[j] && dis[j] > Map[k][j])
            {
                dis[j] = Map[k][j];
                pre[j] = k;
            }
        }
    }
    return ans;//��С��������Ȩֵ֮��
}
int smst(int n, int min_ans)//min_ans ����С��������Ȩֵ��
{
    int ans = inf;
    for (int i = 1; i <= n; i++)//ö����С������֮��ı�
        for (int j = i + 1; j <= n; j++)
            if (Map[i][j] != inf && !used[i][j])
                ans = min(ans, min_ans + Map[i][j] - Max[i][j]);
    if (ans == inf) return -1;
    return ans;
}
void solve(int n)
{
    int ans = prim(n);
    if (ans == -1)
    {
        puts("Not Unique!");
        return;
    }
    if (smst(n, ans) == ans)
    printf("Not Unique!\n");
    else
    printf("%d\n", ans);
}

int main()
{
    int T, n, m;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &m);
        init(n);
        read(m);
        solve(n);
    }
    return 0;
}
