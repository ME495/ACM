/*
2-sat 输出任意解
题意：有一对新人结婚，邀请n对夫妇去参加婚礼。有一张很长的桌子，人只能坐在桌子的两边，还要满足下面的要求：
1.每对夫妇不能坐在同一侧 
2.m对夫妇之中可能有通奸关系（包括男男，男女，女女），有通奸关系的不能同时坐在新娘的对面，可以分开坐，可以同时坐在新娘这一侧。如果存在一种可行的方案，输出与新娘同侧的人。
求解的时候去选择和新郎同一侧的人，输出的时候换一下就是新娘同一侧的人。如果i和j有奸情，则增加一条i到j',j到i'的边，同时增加一条新娘到新郎的边，表示必须选新郎。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 20010
#define M 100010
int head[N],to[M],pre[M];
int dfn[N],low[N],sta[N],block[N],ru[N],opp[N],col[N];
bool insta[N];
int n,m,e,cnt,scnt,top;
vector<int> g[N];
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
    while(scanf("%d%d",&n,&m),n)
    {
        memset(head,-1,sizeof(head));
        e=0;
        addedge(0,1);
        int x,y;
        char st[20];
        for(int i=1;i<=m;++i)
        {
            scanf("%s",st);
            int l=strlen(st);
            char c=st[l-1];
            st[l-1]='\0';
            x=atoi(st)<<1;
            if(c=='h') x|=1;
            scanf("%s",st);
            l=strlen(st);
            c=st[l-1];
            st[l-1]='\0';
            y=atoi(st)<<1;
            if(c=='h') y|=1;
            addedge(x,y^1);
            addedge(y,x^1);
        }
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(insta,0,sizeof(insta));
        cnt=scnt=top=0;
        for(int i=0;i<n*2;++i)
            if(!dfn[i]) tarjan(i);
        bool flag=true;
        for(int i=0;i<n*2;i+=2)//判断是否有可行解
            if(block[i]==block[i^1])
            {
                flag=false;break;
            }
            else//记录相反的联通块
            {
                opp[block[i]]=block[i^1];
                opp[block[i^1]]=block[i];
            }
        if(!flag)//无可行解
        {
            puts("bad luck");
            continue;
        }
        for(int i=1;i<=scnt;++i) 
        {
            g[i].clear();ru[i]=0;
        }
        for(int x=0;x<n*2;++x)
            for(int i=head[x];i!=-1;i=pre[i])
            {
                int y=to[i];
                if(block[x]==block[y]) continue;
                g[block[y]].push_back(block[x]);//建立反向边
                ++ru[block[x]];
            }
        memset(col,0,sizeof(col));
        //拓扑排序
        top=0;
        for(int i=1;i<=scnt;++i)
            if(ru[i]==0) sta[++top]=i;
        while(top)
        {
            int x=sta[top--];
            if(!col[x])//0表示为染色，-1表示假，1表示真
            {
                col[x]=1;col[opp[x]]=-1;
            }
            for(int i=0;i<g[x].size();++i)
            {
                int y=g[x][i];
                if(--ru[y]==0) sta[++top]=y;
            }
        }
        for(int i=1;i<n;++i)
            if(col[block[i<<1]]==-1) printf("%dw ",i);
            else printf("%dh ",i);
        printf("\n");
    }
    return 0;
}

/*
2-sat 求字典序最小的解，代码量比求任意解小，但效率慢一点
题意：每个党派需要在两个代表中选一个，这2*n个代表中有彼此讨厌的m对人，输出n个去开会的代表
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 16010
#define M 100010
int head[N],to[M],pre[M],sta[N];
bool mark[N];
int n,m,e,top;
void addedge(int x,int y)
{
    to[e]=y;pre[e]=head[x];head[x]=e++;
}
bool dfs(int x)
{
    if(mark[x^1]) return false;
    if(mark[x]) return true;
    mark[x]=true;
    sta[++top]=x;
    for(int i=head[x];i!=-1;i=pre[i])
        if(!dfs(to[i])) return false;
    return true;
}
bool solve()
{
    for(int i=0;i<n*2;i+=2)
    {
        if(!mark[i]&&!mark[i^1])
        {
            top=0;
            if(!dfs(i))
            {
                while(top>0) mark[sta[top--]]=false;
                if(!dfs(i+1)) return false;
            }
        }
    }
    return true;
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=0;i<n*2;++i)
        {
            head[i]=-1;mark[i]=0;
        }
        e=0;
        int x,y;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&y);
            --x;--y;
            addedge(x,y^1);
            addedge(y,x^1);
        }
        if(!solve()) puts("NIE");
        else
        {
            for(int i=0;i<n*2;++i)
                if(mark[i]) printf("%d\n",i+1);
        }
    }
    return 0;
}