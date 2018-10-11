/*
有向图的强连通分量
题意：当强连通分量为1的时候输出Yes否者输出No
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 10010
#define M 100010
int head[N],pre[M],to[M];
int dfn[N],low[N],sta[N];
bool insta[N];
int n,m,e,cnt,scnt,top;
void addedge(int x,int y)
{
    to[e]=y;pre[e]=head[x];head[x]=e++;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++cnt;
    insta[x]=true;
    sta[++top]=x;
    int y;
    for(int i=head[x];i!=-1;i=pre[i])
    {
        y=to[i];
        if(!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(insta[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x])
    {
        ++scnt;
        do
        {
            y=sta[top--];
            insta[y]=false;
        }while(y!=x);
    }
}
int main()
{
    while(scanf("%d%d",&n,&m),n)
    {
        e=0;
        memset(head,-1,sizeof(head));
        int x,y;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&y);
            addedge(x,y);
        }
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(insta,0,sizeof(insta));
        cnt=scnt=top=0;
        for(int i=1;i<=n;++i)
            if(!dfn[i]) tarjan(i);
        if(scnt==1) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}

/*
有向图强连通缩点
题意：给定一张有向图，问最少添加几条边使得有向图成为一个强连通图
分析： 
Tarjan入门经典题，用tarjan缩点，然后就变成一个有向无环图(DAG)了。 
我们要考虑的问题是让它变成强连通，让DAG变成强连通就是把尾和头连起来，也就是入度和出度为0的点。 
统计DAG入度和出度，然后计算头尾，最大的那个就是所求。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 20010
#define M 50010
int head[N],to[M],pre[M];
int dfn[N],low[N],sta[N],block[N],chu[N],ru[N];
bool insta[N];
int n,m,e,cnt,scnt,top;
void addedge(int x,int y)
{
    to[e]=y;pre[e]=head[x];head[x]=e++;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++cnt;
    insta[x]=true;
    sta[++top]=x;
    int y;
    for(int i=head[x];i!=-1;i=pre[i])
    {
        y=to[i];
        if(!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(insta[y]) low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x])
    {
        ++scnt;
        do
        {
            y=sta[top--];
            insta[y]=false;
            block[y]=scnt;
        }while(y!=x);
    }
}
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        e=0;
        int x,y;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&y);
            addedge(x,y);
        }
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(insta,0,sizeof(insta));
        cnt=scnt=top=0;
        for(int i=1;i<=n;++i)
            if(!dfn[i]) tarjan(i);
        memset(chu,0,sizeof(chu));
        memset(ru,0,sizeof(ru));
        for(int i=1;i<=n;++i)
        {
            for(int j=head[i];j!=-1;j=pre[j])
            {
                x=block[i];y=block[to[j]];
                if(x!=y)
                {
                    ++chu[x];++ru[y];
                }
            }
        }
        if(scnt==1)
        {
            printf("0\n");
            continue;
        }
        int tot1=0,tot2=0;
        for(int i=1;i<=scnt;++i)
        {
            if(!chu[i]) ++tot1;
            if(!ru[i]) ++tot2;
        }
        printf("%d\n",max(tot1,tot2));
    }
    return 0;
}

/*
无向图边的双连通分量缩点
题意：给出一个无向图以及Q次询问，每次询问增加一条无向边，要求输出增加这条边后剩余的桥的数目
算法：类似于求割点的方法，先做一次dfs求出所有的桥，并且维护这棵dfs树，当一次询问加入一条边(a,b)之后，会在dfs上形成一个环，在这个环上的桥都变为非桥，这个环肯定经过a和b的LCA，此时我们只需在求LCA的过程中把经过的为桥的树边标记为非桥，同时cnt_bridge--再输出即可。
需要注意的是树边的编号是用树边指向的那个节点的编号来表示的，例如树边<u,v>用编号v表示。
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
#define N 100010
vector<int>g[N],tree[N];
stack<int>sta;
int n,m,cnt,scnt,q,ans;
int block[N],parent[N],dfn[N],low[N],dep[N],f[N];
void tarjan(int x,int fa)
{
    bool flag=true;
    int y;
    dfn[x]=low[x]=++cnt;
    sta.push(x);
    for(int i=0;i<g[x].size();++i)
    {
        y=g[x][i];
        if(y==fa&&flag)
        {
            flag=false;
            continue;
        }
        if(!dfn[y])
        {
            tarjan(y,x);
            low[x]=min(low[x],low[y]);
        }
        else low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x])
    {
        ++scnt;
        do
        {
            y=sta.top();
            sta.pop();
            block[y]=scnt;
        }while(x!=y);
    }
}
void dfs(int x)
{
    int y;
    for(int i=0;i<tree[x].size();++i)
    {
        y=tree[x][i];
        if(dep[y]) continue;
        dep[y]=dep[x]+1;
        parent[y]=x;
        ++ans;
        dfs(y);
    }
}
void LCA(int x,int y)
{
    if(x==y) return;
    while(dep[x]>dep[y])
    {
        if(!f[x]){f[x]=true;--ans;}
        x=parent[x];
    }
    while(dep[x]<dep[y])
    {
        if(!f[y]){f[y]=true;--ans;}
        y=parent[y];
    }
    while(x!=y)
    {
        if(!f[x]){f[x]=true;--ans;}
        if(!f[y]){f[y]=true,--ans;}
        x=parent[x];y=parent[y];
    }
}
int main()
{
    int x,y,ca=0;
    while(scanf("%d%d",&n,&m),n+m)
    {
        printf("Case %d:\n",++ca);
        for(int i=1;i<=n;++i)
        {
            g[i].clear();
            tree[i].clear();
        }
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&y);
            g[x].push_back(y);
            g[y].push_back(x);
        }
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        cnt=scnt=0;
        for(int i=1;i<=n;++i)
            if(!dfn[i]) tarjan(i,0);
        for(int i=1;i<=n;++i)
        {
            x=block[i];
            for(int j=0;j<g[i].size();++j)
            {
                y=block[g[i][j]];
                if(x!=y) tree[x].push_back(y);
            }
        }
        memset(parent,0,sizeof(parent));
        memset(dep,0,sizeof(dep));
        dep[1]=1;ans=0;
        dfs(1);
        memset(f,0,sizeof(f));
        scanf("%d",&q);
        for(int i=1;i<=q;++i)
        {
            scanf("%d%d",&x,&y);
            LCA(block[x],block[y]);
            printf("%d\n",ans);
        }
        printf("\n");
    }
    return 0;
}

/*
无向图求桥边数量
题意：按照题目输入顺序输出桥边
分析：当且仅当无向边（u，v）是树枝边的时候，需要满足dfn(u)<low(v)，也就是v向上翻不到u及其以上的点，那么u--v之间一定能够有1条或者多条边不能删去，因为他们之间有一部分无环，是桥。
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define N 10010
#define M 100010
struct Edge{
    int x,y,next;
}edge[M<<1];
map<string,int>mp1;
map<int,string>mp2;
int n,m,e,cnt,tot;
int dfn[N],low[N];
int head[N],a[M<<1];
bool comp(int a,int b)
{
    return a<b;
}
void addedge(int x,int y)
{
    edge[e].x=x;edge[e].y=y;
    edge[e].next=head[x];
    head[x]=e++;
}
void tarjan(int x,int fa)
{
    int y;
    dfn[x]=low[x]=++cnt;
    for(int i=head[x];i!=-1;i=edge[i].next)
    {
        y=edge[i].y;
        if(y==fa) continue;
        if(!dfn[y])
        {
            tarjan(y,x);
            low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x]) a[++tot]=i;
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
int main()
{
    int ca,x,y;
    char st1[20],st2[20];
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        mp1.clear();mp2.clear();
        int k=0;
        e=0;
        for(int i=1;i<=m;++i)
        {
            scanf("%s%s",st1,st2);
            if(mp1[st1]==0)
            {
                mp1[st1]=++k;
                mp2[k]=st1;
                x=k;
            }
            else x=mp1[st1];
            if(mp1[st2]==0)
            {
                mp1[st2]=++k;
                mp2[k]=st2;
                y=k;
            }
            else y=mp1[st2];
            addedge(x,y);
            addedge(y,x);
        }
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        cnt=tot=0;
        tarjan(1,0);
        bool flag=true;
        for(int i=1;i<=n;++i)
            if(!dfn[i])
            {
                flag=false;
                break;
            }
        if(!flag)
        {
            printf("0\n");
            continue;
        }
        printf("%d\n",tot);
        sort(a+1,a+tot+1,comp);
        for(int i=1;i<=tot;++i)
        {
            x=min(a[i],a[i]^1);
            printf("%s %s\n",mp2[edge[x].x].c_str(),mp2[edge[x].y].c_str());
        }
    }
    return 0;
}

/*
无向图求割点
分析：
1）当前节点为树根的时候，条件是“要有多余一棵子树”（如果这有一颗子树，去掉这个点也没有影响，如果有两颗子树，去掉这点，两颗子树就不连通了。）
2）当前节点U不是树根的时候，条件是“low[v]>=dfn[u]”，也就是在u之后遍历的点，能够向上翻，最多到u，如果能翻到u的上方，那就有环了，去掉u之后，图仍然连通。
*/
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define N 110
vector<int>g[N];
int dfn[N],low[N];
int n,cnt,tot,root;
bool f[N];
void tarjan(int x)
{
    int y;
    dfn[x]=low[x]=++cnt;
    for(int i=0;i<g[x].size();i++)
    {
        y=g[x][i];
        if(!dfn[y])
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);
            if(x!=1&&low[y]>=dfn[x])
                f[x]=true;
            else if(x==1) ++root;
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
int main()
{
    int x,y;
    while(scanf("%d\n",&n),n)
    {
        for(int i=1;i<=n;i++) g[i].clear();
        while(scanf("%d",&x),x)
        {
            while(getchar()!='\n')
            {
                scanf("%d",&y);
                g[x].push_back(y);
                g[y].push_back(x);
            }
        }
        memset(dfn,false,sizeof(dfn));
        memset(low,false,sizeof(low));
        memset(f,false,sizeof(f));
        cnt=tot=root=0;
        tarjan(1);
        if(root>1) ++tot;
        for(int i=2;i<=n;i++)
            if(f[i]) ++tot;
        printf("%d\n",tot);
    }
    return 0;
}

/*
无向图求点双联通分量
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
#include<vector>
using namespace std;
#define maxn 7500
#define inf 0x3f3f3f3f
int n,m;
int g[maxn][maxn];
int clock;
int low[maxn],pre[maxn];
stack<int>s;
int bc;
vector<int>bcc[maxn];
int dfs(int u,int fa){
     low[u]=pre[u]=++clock;
     s.push(u);
     for(int v=1;v<=n;v++){
        if(!g[u][v])continue;
        if(!pre[v]){
            int lowv=dfs(v,u);
            low[u]=min(low[u],lowv);
            if(lowv>=pre[u]){
                bc++;
                bcc[bc].clear();
                int tmp=-1;
                while(!s.empty()){
                    tmp=s.top();
                    s.pop();
                    bcc[bc].push_back(tmp);
                    if(tmp==u)break;
                }
                if(tmp!=-1)s.push(tmp);  //割顶要加回去，任意割顶至少是两个不同双联通分量的公共点
            }
        }
       else if(pre[v]<pre[u]&&fa!=v){
            low[u]=min(low[u],pre[v]);
        }
     }
     return low[u];
}
void inital(){
    clock=0;
    bc=0;
    memset(pre,0,sizeof pre);
    memset(low,inf,sizeof low);
    while(!s.empty()){
        s.pop();
    }
}
int main()
{
    int u,v;
    while(~scanf("%d%d",&n,&m)){
        inital();
        for(int i=0;i<m;i++){
            scanf("%d%d",&u,&v);
            g[u][v]=g[v][u]=1;
        }
        for(int i=1;i<=n;i++){
            if(!pre[i])dfs(i,-1);
        }
         for(int i=1;i<=n;i++){
            printf("%d %d\n",pre[i],low[i]);
        }
 
        printf("下面是点联通分量%d:\n",bc);
        for(int i=1;i<=bc;i++){
            printf("%d:",i);
            for(int j=0;j<bcc[i].size();j++){
                printf("%d ",bcc[i][j]);
            }
            printf("\n");
        }
 
    }
    return 0;
}