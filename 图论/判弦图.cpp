/*
ZOJ 1015
题意：给定n个点m条边，判断它是否是弦图。
题解：使用陈丹琪的《弦图与区间图》中的判断弦图的算法
这里使用邻接矩阵存图，所以复杂度为O(N^2)
如果按照论文中的做法，用邻接表存边，复杂度会小一点
*/
#include <bits/stdc++.h>
using namespace std;
#define N 1010
bool g[N][N];
int n,m;
int label[N],id[N],a[N];
void MCS()//最大势算法
{
    for(int i=1;i<=n;++i) label[i]=id[i]=0;
    for(int i=n;i>=1;--i)
    {
        int mx=-1,x;
        for(int j=1;j<=n;++j)
            if(!id[j]&&mx<label[j])
            {
                mx=label[j];x=j;
            }
        id[x]=i;a[i]=x;
        for(int j=1;j<=n;++j)
            if(!id[j]&&g[x][j])
                ++label[j];
    }
}
bool check()//使用MCS算法求出序列，再判断它是否是完美消除序列
{
    MCS();
    for(int i=1;i<=n;++i)
    {
        bool flag=false;
        int x;
        for(int j=i+1;j<=n;++j)
        {
            if(!g[a[i]][a[j]]) continue;
            if(!flag)
            {
                flag=true;x=a[j];
            }
            else if(!g[x][a[j]])
                return false;
        }
    }
    return true;
}
int main()
{
    while(scanf("%d%d",&n,&m),n)
    {
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                g[i][j]=false;
        int x,y;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&y);
            g[x][y]=g[y][x]=true;
        }
        if(check()) puts("Perfect\n");
        else puts("Imperfect\n");
    }
    return 0;
}
