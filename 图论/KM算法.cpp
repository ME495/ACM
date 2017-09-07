#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
#define INF 99999999
#define maxn 305

int lx[maxn],ly[maxn];//顶标
int Match[maxn];//记录匹配值
int visx[maxn],visy[maxn];
int w[maxn][maxn];//权值
int slack[maxn];//slack为修改量
int ans,n;

bool findPath(int x)//寻找最优解
{
    int temp;
    visx[x]=1;
    for(int y=1; y<=n; y++)
    {
        if(visy[y])continue;
        //temp=w[x][y]-lx[x]-ly[y];//用此TLE
        //if(temp==0)
        if(w[x][y]==lx[x]+ly[y])//说明是相等子图
        {
            visy[y]=1;
            if(!Match[y]||findPath(Match[y]))
            {
                Match[y]=x;
                return true;
            }
        }
        else
        slack[y]=min(slack[y],lx[x]+ly[y]-w[x][y]);
    }
    return false;
}
void km()
{
    memset(Match,0,sizeof(Match));
    //初始化顶标
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    /*for(int i=1; i<=n; i++)
    {
        lx[i]=-1;//若求最小权匹配了lx[i]=INF
        ly[i]=0;
    }*/
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            //if(lx[i]<w[i][j])//若求最小权匹配lx[i]>w[i][j]
                lx[i]=max(lx[i],w[i][j]);//
    for(int x=1; x<=n; x++)
    {
        for(int i=1;i<=n;i++)
        slack[i]=INF;
        while(1)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(findPath(x))break;
            int tmp=INF;
            for(int i=1;i<=n;i++)
            {
                if(!visy[i])
                {
                    if(tmp>slack[i])
                    tmp=slack[i];
                }
            }
            if(tmp==INF)return ;
            for(int i=1; i<=n; i++)
            {
                if(visx[i]) lx[i]-=tmp;//若求最小权匹配改为lx[i]+=slack;
                if(visy[i]) ly[i]+=tmp;//ly[i]-=slack;
                else
                slack[i]-=tmp;
            }
        }
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        ans=0;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                scanf("%d",&w[i][j]);
        km();
        for(int i=1; i<=n; i++)
            ans+=w[Match[i]][i];
        printf("%d\n",ans);
    }
    return 0;
}
