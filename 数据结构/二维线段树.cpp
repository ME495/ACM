/*
给定一个n*n的矩阵,每次给定一个子矩阵区域(x,y,l),求出该区域内的最大值(A)和最小值(B),输出(A+B)/2,并用这个值更新矩阵[x,y]的值
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 810
#define lx x<<1
#define rx x<<1|1
#define lsx lx,s,mid
#define rsx rx,mid+1,t
#define ly y<<1
#define ry y<<1|1
#define lsy ly,s,mid
#define rsy ry,mid+1,t
int maxv[N*4][N*4],minv[N*4][N*4],a[N][N];
int n,xL,xR,yL,yR,ans_max,ans_min,ans,idx,idy;
void pushup(int x,int y)
{
    maxv[x][y]=max(maxv[x][ly],maxv[x][ry]);
    minv[x][y]=min(minv[x][ly],minv[x][ry]);
}
void buildY(int x,int id,int y,int s,int t)
{
    if(s==t)
    {
        if(id!=-1)
        {
            maxv[x][y]=minv[x][y]=a[id][s];
        }
        else
        {
            maxv[x][y]=max(maxv[lx][y],maxv[rx][y]);
            minv[x][y]=min(minv[lx][y],minv[rx][y]);
        }
        return;
    }
    int mid=s+t>>1;
    buildY(x,id,lsy);buildY(x,id,rsy);
    pushup(x,y);
}
void buildX(int x,int s,int t)
{
    if(s==t)
    {
        buildY(x,s,1,1,n);
        return;
    }
    int mid=s+t>>1;
    buildX(lsx);buildX(rsx);
    buildY(x,-1,1,1,n);
}
void queryY(int x,int y,int s,int t)
{
    if(yL<=s&&t<=yR)
    {
        ans_min=min(ans_min,minv[x][y]);
        ans_max=max(ans_max,maxv[x][y]);
        return;
    }
    int mid=s+t>>1;
    if(yL<=mid) queryY(x,lsy);
    if(mid<yR) queryY(x,rsy);
}
void queryX(int x,int s,int t)
{
    if(xL<=s&&t<=xR)
    {
        queryY(x,1,1,n);
        return;
    }
    int mid=s+t>>1;
    if(xL<=mid) queryX(lsx);
    if(mid<xR) queryX(rsx);
}
void updataY(int x,int id,int y,int s,int t)
{
    if(s==t)
    {
        if(id!=-1) maxv[x][y]=minv[x][y]=ans;
        else
        {
            maxv[x][y]=max(maxv[lx][y],maxv[rx][y]);
            minv[x][y]=min(minv[lx][y],minv[rx][y]);
        }
        return;
    }
    int mid=s+t>>1;
    if(idy<=mid) updataY(x,id,lsy);
    else updataY(x,id,rsy);
    pushup(x,y);
}
void updataX(int x,int s,int t)
{
    if(s==t)
    {
        updataY(x,s,1,1,n);return;
    }
    int mid=s+t>>1;
    if(idx<=mid) updataX(lsx);
    else updataX(rsx);
    updataY(x,-1,1,1,n);
}
int main()
{
    int ca;
    scanf("%d",&ca);
    for(int cas=1;cas<=ca;++cas)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                scanf("%d",&a[i][j]);
        buildX(1,1,n);
        int m,l,x1,y1,x2,y2;
        scanf("%d",&m);
        printf("Case #%d:\n",cas);
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d%d",&idx,&idy,&l);
            l>>=1;
            xL=max(1,idx-l);xR=min(n,idx+l);
            yL=max(1,idy-l);yR=min(n,idy+l);
            ans_min=1e9;ans_max=0;
            queryX(1,1,n);
            ans=ans_min+ans_max>>1;
            updataX(1,1,n);
            printf("%d\n",ans);
        }
    }
}
