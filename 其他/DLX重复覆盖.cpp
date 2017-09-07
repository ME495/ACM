//题意：有N个城市，M个雷达站，K个操作员，从M个雷达站中选择K个，来覆盖所有的N城市，每个雷达有相同的覆盖半径，问：最小的覆盖半径是多少
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int MaxM = 15*15+10;
const int MaxN = 15*15+10;
const int maxnode = MaxN * MaxM;
const int INF = 0x3f3f3f3f;
#define eps 1e-8
struct DLX
{
    int n,m,size;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode];//十字链表
    int Row[maxnode],Col[maxnode];//各个节点再那行那列
    int H[MaxN];//每行的第一个节点的编号
    int S[MaxM];//每列的剩余节点
    int ansd;//答案
    void init(int _n,int _m)//初始化
    {
        n = _n;
        m = _m;
        for(int i = 0;i <= m;i++)
        {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        for(int i = 1;i <= n;i++)H[i] = -1;
    }
    void Link(int r,int c)//再r行c列加入节点
    {
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)H[r] = L[size] = R[size] = size;
        else
        {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    void remove(int c)//删除一列
    {
        for(int i = D[c];i != c;i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c)//恢复一列
    {
        for(int i = U[c];i != c;i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    bool v[MaxM];//记录各列有没有被标记
    int f()//评估函数
    {
        int ret = 0;
        for(int c = R[0]; c != 0;c = R[c])v[c] = true;
        for(int c = R[0]; c != 0;c = R[c])
            if(v[c])
            {
                ret++;
                v[c] = false;
                for(int i = D[c];i != c;i = D[i])
                    for(int j = R[i];j != i;j = R[j])
                        v[Col[j]] = false;
            }
        return ret;
    }
    void Dance(int d)//dfs搜索可能情况
    {
        if(d + f() >= ansd)return;
        if(R[0] == 0)
        {
            if(d < ansd)ansd = d;
            return;
        }
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        for(int i = D[c];i != c;i = D[i])
        {
            remove(i);
            for(int j = R[i];j != i;j = R[j])remove(j);
            Dance(d+1);
            for(int j = L[i];j != i;j = L[j])resume(j);
            resume(i);
        }
    }
};
DLX g;
double x[58],y[58],x2[58],y2[58];
bool vis[58];
int main()
{
	//freopen("in.txt","r",stdin);
	int n,m,k,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&n,&m,&k);
		for(int i = 1;i <= n;i++)
			scanf("%lf%lf",&x[i],&y[i]);
		for(int i = 1;i <= m;i++)
			scanf("%lf%lf",&x2[i],&y2[i]);
		double l = 0,r = 2000;
		while(l+eps < r)
		{
			double mid = (l+r)/2;
			int num = 0;
			memset(vis,0,sizeof(vis));
			g.init(m,n);
			for(int i = 1;i <= m;i++)
			{
				for(int j = 1;j <= n;j++)
				{
					if(((x2[i]-x[j])*(x2[i]-x[j])+(y2[i]-y[j])*(y2[i]-y[j])) <= mid*mid)
					{
						g.Link(i,j);
						if(!vis[j])	num++;
						vis[j] = 1;
					}
				}
			}
			if(num < n)	l = mid;
			else
			{
				g.ansd = INF;
				g.Dance(0);
				if(g.ansd <= k)	r = mid;
				else l = mid;
			}
		}
		printf("%.6f\n",l);
	}
}
