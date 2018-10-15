/*
题意：给出一棵树，每条边有边权。有m次询问，每次询问给出k个点，问使得这k个点均不与1号点(根节点)相连的最小代价。
n<=250000,m>=1,sigma(k)<=500000
题解：对每个询问建立虚树，再跑dp。
考虑得到了询问点，如何构造出一棵虚树。
首先我们要先对整棵树dfs一遍，求出他们的dfs序，然后对每个节点以dfs序为关键字从小到大排序。
同时维护一个栈，表示从根到栈顶元素这条链。
假设当前要加入的节点为p，栈顶元素为x=s[top]，lca为他们的最近公共祖先。
因为我们是按照dfs序遍历，因此lca不可能是p，那么现在会有两种情况：
（1）lca是x，直接将p入栈。
（2）x,p分别位于lca的两棵子树中，此时x这棵子树已经遍历完毕，（如果没有，即x的子树中还有一个未加入的点y，但是dfn[y]<dfn[p]，即应先访问y）， 我们需要对其进行构建。
设栈顶元素为x，第二个元素为y：
（1）若dfn[y]>dfn[lca]，可以连边y−>x，将x出栈；
（2）若dfn[y]=dfn[lca]，即y=lca，连边lca−>x，此时子树构建完毕(break)；
（3）若dfn[y]<dfn[lca]，即lca在y,x之间，连边lca−>x，x出栈，再将lca入栈。此时子树构建完毕(break)。
不断重复这个过程，虚树就构建完成了。
另外对于此题，位于同一子树的询问点，只需要保留最顶端的节点，并维护出这个节点到根的链上的最小值，然后在虚树上dp。
*/
#include <bits/stdc++.h>
using namespace std;
#define N 250010
typedef long long ll;
const ll inf=1e15;
int head[N],to[N*2],pre[N*2],w[N*2],dfn[N],fa[N][18],dep[N],a[N],sta[N];
ll mn[N];
int n,e,top,cnt;
bool f[N];
void addedge(int x,int y,int z)
{
    to[e]=y;w[e]=z;pre[e]=head[x];head[x]=e++;
}
void dfs1(int x,int p)
{
    dfn[x]=++cnt;fa[x][0]=p;
    for(int i=1;i<18;++i)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=head[x];i!=-1;i=pre[i])
    {
        int y=to[i];
        if(y==p) continue;
        dep[y]=dep[x]+1;
        mn[y]=min(mn[x],(ll)w[i]);
        dfs1(y,x);
    }
}
int LCA(int x,int y)
{
    if(dep[x]>dep[y]) swap(x,y);
    int d=dep[y]-dep[x];
    for(int i=0;i<18;++i)
        if((d>>i)&1) y=fa[y][i];
    if(x==y) return x;
    for(int i=17;i>=0;--i)
        if(fa[x][i]!=fa[y][i])
        {
            x=fa[x][i];y=fa[y][i];
        }
    return fa[x][0];
}
bool cmp(int x,int y)
{
    return dfn[x]<dfn[y];
}
void insert(int x)
{
    if(top==1)
    {
        sta[++top]=x;return;
    }
    int lca=LCA(x,sta[top]);
    if(lca==sta[top])
    {
        // 此题只要保留同一子树中最顶端的节点，如果需要保留全部节点，去掉注释
        // sta[++top]=x;
        return;
    }
    while(top>1&&dfn[sta[top-1]]>=dfn[lca])
    {
        addedge(sta[top-1],sta[top],0);
        --top;
    }
    if(lca!=sta[top])
    {
        addedge(lca,sta[top],0);
        sta[top]=lca;
    }
    sta[++top]=x;
}
ll dfs2(int x)
{
    if(head[x]==-1) return mn[x];
    ll sum=0;
    for(int i=head[x];i!=-1;i=pre[i]) 
    {
        int y=to[i];
        sum+=dfs2(y);
    }
    head[x]=-1;
    return min(sum,mn[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) head[i]=-1;
    e=cnt=0;
    int x,y,z;
    for(int i=1;i<n;++i)
    {
        scanf("%d%d%d",&x,&y,&z);
        addedge(x,y,z);addedge(y,x,z);
    }
    mn[1]=inf;
    dfs1(1,1);
    for(int i=1;i<=n;++i) head[i]=-1;
    e=0;
    int m,k;
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d",&k);
        for(int i=1;i<=k;++i) scanf("%d",&a[i]);
        sort(a+1,a+k+1,cmp);
        sta[top=1]=1;//把根入栈
        for(int i=1;i<=k;++i) insert(a[i]);
        while(top>1)
        {
            addedge(sta[top-1],sta[top],0);
            --top;
        }
        printf("%lld\n",dfs2(1));
        e=0;
    }
    return 0;
}
