/*
利用Kosaraju算法，只需要在正反图各做一次DFS即可求出强连通分量。
面对稠密图，Kosaraju算法的瓶颈在于寻找与点x相连且未访问过的点。
可以用二进制数来表示边表$g_x$，以及未访问过的点集S。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 260
struct BIT{
    unsigned int b[8];
    /*
    如果x==0，则b数组全置为0
    如果x==0xff，则b数组全置为1
    */
    void reset(int x){memset(b,x,sizeof(b));}
    void flip(int x){b[x>>5]^=1U<<(x&31);}
    //得到BIT的x位是0还是1
    int get(int x){return (b[x>>5]>>(x&31))&1;}
}g1[N],g2[N],vis;//g1表示正图,g2表示反图，vis表示未访问过的点集
int sta[N];
int n,top,cnt;
//得到s中最右边的1之前0的个数
inline int get_x(unsigned int s)
{
    int x=0;
    while(!(s&1))
    {
        ++x;s>>=1;
    }
    return x;
}
void dfs1(int x)
{
    vis.flip(x);
    unsigned int s;
    for(int i=0;i<8;++i)
    {
        while(1)
        {
            //s位可以还未访问的点集
            s=vis.b[i]&g1[x].b[i];
            if(s==0) break;
            dfs1((i<<5)|get_x(s));
        }
    }
    sta[++top]=x;
}
void dfs2(int x)
{
    vis.flip(x);++cnt;
    unsigned s;
    int y;
    for(int i=0;i<8;++i)
    {
        while(true)
        {
            s=vis.b[i]&g2[x].b[i];
            if(s==0) break;
            dfs2((i<<5)|get_x(s));
        }
    }
}
int main()
{
    int ca,m;
    scanf("%d",&ca);
    char st[N];
    while(ca--)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;++i) g1[i].reset(0),g2[i].reset(0);
        for(int i=0;i<n;++i)
        {
            scanf("%s",st);
            for(int j=0;j<n;++j)
                if(st[j]=='1') g1[i].flip(j),g2[j].flip(i);
        }
        int k,u,v;
        while(m--)
        {
            scanf("%d",&k);
            for(int i=1;i<=k;++i)
            {
                scanf("%d%d",&u,&v);
                --u;--v;
                g1[u].flip(v);g2[v].flip(u);
            }
            vis.reset(0xff);top=0;
            for(int i=0;i<n;++i)
                if(vis.get(i))
                    dfs1(i);
            vis.reset(0xff);
            int ans=0;
            for(int i=top;i>0;--i)
                if(vis.get(sta[i]))
                {
                    //cnt表示一个强联通分量中点的数量
                    cnt=0;
                    dfs2(sta[i]);
                    ans+=cnt*(cnt-1)/2;
                }
            printf("%d\n",ans);
        }
    }
    return 0;
}
