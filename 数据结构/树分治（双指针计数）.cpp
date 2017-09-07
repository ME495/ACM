/*
�����Ͼ���С��K�ĵ�Ե�������
����һ���ڵ㣬���������Ϊ���������ķ��������ĵ�Ե�����
�ټ�ȥ��������Ϊ���������ķ��������ĵ�Ե�������
��������ʱ��˫ָ��
��ı��Ϊ1~n
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
int sz[N],f[N];//sz[x]-->x������С��f[x]-->x��������Ľڵ�����
int n;
int rt;
int vis[N],dis[N];
int K;
int ans,size;
int aa,bb,cc;
void getrt(int x,int fa)//����*sz,*f������
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
    f[x]=max(f[x],size-sz[x]);//!  x��������Ľڵ���=max(���������С��f[x],f[x])
    if(f[x]<f[rt]) rt=x; 
}
void getdis(int x,int fa)//һ��dfs����룫�����ĵ�һ��Ԥ����sz[x],��������Сsize
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
        f[0]=size=sz[u];//!!! getdis���Ѿ�����������ȫ��С
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