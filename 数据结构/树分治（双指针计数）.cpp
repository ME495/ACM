/*
求树上距离小于K的点对的数量，
对于一个节点，先算出以它为根的子树的符合条件的点对的数量
再减去以它儿子为根的子树的符合条件的点对的数量，
求点对数量时用双指针
点的编号为1~n
*/
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
#define N 10005
using namespace std;
struct node{
    int x,y;
    node(int xx,int yy)
    {
        x=xx,y=yy;
    }
};
vector<node> lin[N];
vector<int> d;
int sz[N],f[N];//sz[x]-->x的树大小，f[x]-->x最大子树的节点数；
int n;
int rt;
int vis[N],dis[N];
int K;
int ans,size;
int aa,bb,cc;
void getrt(int x,int fa)//利用*sz,*f求重心
{
    sz[x]=1;
    f[x]=0;
    for(int i=0;i<lin[x].size();i++)
    {
        int u=lin[x][i].x;
        if(vis[u]||u==fa) continue;
        getrt(u,x);
        sz[x]+=sz[u];
        f[x]=max(sz[u],f[x]);
    }
    f[x]=max(f[x],size-sz[x]);//!  x最大子树的节点数=max(与此子树大小－f[x],f[x])
    if(f[x]<f[rt]) rt=x; 
}
void getdis(int x,int fa)//一遍dfs求距离＋求重心的一点预处理sz[x],求子树大小size
{
    sz[x]=1;
    d.push_back(dis[x]);
    for(int i=0;i<lin[x].size();i++)
    {
        int u=lin[x][i].x;
        if(vis[u]||u==fa) continue;     
        dis[u]=dis[x]+lin[x][i].y;
        getdis(u,x);
        sz[x]+=sz[u];       
    }
}
int cal(int x,int y)
{   
    int ret=0;
    d.clear();
    dis[x]=y;
    getdis(x,0);

    sort(d.begin(),d.end());
    int l=0;
    int r=d.size()-1;
    while(l<r)
    {
        while(d[l]+d[r]>K&l<r) r--;
        ret+=r-l;
        l++;    
    }
    return ret;
}
void solve(int x)
{
    //cout<<x<<endl;
    ans+=cal(x,0);
    vis[x]=1;
    for(int i=0;i<lin[x].size();i++)
    {
        int u=lin[x][i].x;
        if(vis[u]) continue;
        ans-=cal(u,lin[x][i].y);
        f[0]=size=sz[u];//!!! getdis中已经处理子树的全大小
        getrt(u,rt=0);
        solve(rt);
    }

}
int main()
{
    while(scanf("%d%d",&n,&K))
    {
        if(!n&&!K) return 0;
        for(int i=1;i<=n;i++)
        {
            vis[i]=0;
            lin[i].clear();
        }
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&aa,&bb,&cc);
            lin[aa].push_back(node(bb,cc));
            lin[bb].push_back(node(aa,cc)); 
        }   
        ans=0;
        f[0]=size=n;
        getrt(1,rt=0);  
        solve(rt);
        printf("%d\n",ans);
    }
}