/*
����һ��n���ڵ���������ϵ�ȨֵҪôΪ0��ҪôΪ1��
���һ��·���ϵ�0��1������ͬ��·���ϴ���һ���㣨��Ϊ��Ϣ�㣩����·���Ķ˵㣩��
�����������·����0��1��������ȣ��ұ�·���ϵ�0��1������Ҳ��ȣ�
�������·�������������ʷ���������·�ж�������
�⣺�Ȱ����ϵ�Ȩֵ0���-1��
�ڼ�����ʱ������treedp��˼�룬
�ڵ�ǰ���У�
la[x][0/1]��ʾ��ǰ������ǰ���ʵ�����������·��ȨֵΪx��û��/����Ϣ��Ľڵ�����
g[x][0/1]��ʾ��ǰ�������ڷ��ʵĽڵ������������·��ȨֵΪx��û��/����Ϣ��Ľڵ�����
��ı��Ϊ1~n
*/
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
#define N 100010
typedef long long ll;
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
int vis[N],dis[N],g[N*2][2],la[N*2][2],s[N*2];
ll ans,sum;
int size;
int aa,bb,cc,md;
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
    for(int i=0;i<lin[x].size();i++)
    {
        int u=lin[x][i].x;
        if(vis[u]||u==fa) continue;
        getdis(u,x);
        sz[x]+=sz[u];
    }
}
void dfs(int x,int fa,int w)//���g[][]
{
    //printf("%d %d ",x,w);
    md=max(md,max(w,-w));
    if(s[w+N]) ++g[w+N][1];
    else ++g[w+N][0];
    //printf("%d %d !!\n",g[w+N][0],g[w+N][1]);
    ++s[w+N];
    int y;
    for(int i=0;i<lin[x].size();++i)
    {
        y=lin[x][i].x;
        if(vis[y]||y==fa) continue;
        dfs(y,x,w+lin[x][i].y);
    }
    --s[w+N];
}
ll cal(int x)
{
    //printf("%d ----------\n",x);
    int y;
    ll tmp=0;
    int mdd=0;
    for(int i=0;i<lin[x].size();++i)
    {
        y=lin[x][i].x;
        if(vis[y]) continue;
        md=0;
        dfs(y,x,lin[x][i].y);
        mdd=max(mdd,md);
        tmp+=g[N][1]+(ll)g[N][0]*la[N][0];
        for(int j=-md;j<=md;++j)
        {
            tmp+=(ll)g[N-j][0]*la[N+j][1]+(ll)g[N-j][1]*la[N+j][0]+(ll)g[N-j][1]*la[N+j][1];
            //printf("%d %d %d %d %d %d ??\n",y,j,g[N+j][0],g[N+j][1],la[N+j][0],la[N+j][1]);
        }
        for(int j=N-md;j<=N+md;++j)
        {
            la[j][1]+=g[j][1];
            la[j][0]+=g[j][0];
            g[j][1]=g[j][0]=0;
        }
    }
    for(int i=N-mdd;i<=N+mdd;++i)
        la[i][0]=la[i][1]=0;
    //printf("%d ?\n",tmp);
    return tmp;
}
void solve(int x)
{
    ans+=cal(x);
    vis[x]=1;
    for(int i=0;i<lin[x].size();i++)
    {
        int u=lin[x][i].x;
        if(vis[u]) continue;
        getdis(u,0);
        size=sz[u];//!!! getdis���Ѿ�����������ȫ��С
        getrt(u,rt=0);
        solve(rt);
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            vis[i]=0;
            lin[i].clear();
        }
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&aa,&bb,&cc);
            if(cc==0) cc=-1;
            lin[aa].push_back(node(bb,cc));
            lin[bb].push_back(node(aa,cc));
        }
        ans=0;
        f[0]=n+1;size=n;
        getrt(1,rt=0);
        solve(rt);
        printf("%lld\n",ans);
    }
}
