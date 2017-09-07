/*
����Kosaraju�㷨��ֻ��Ҫ������ͼ����һ��DFS�������ǿ��ͨ������
��Գ���ͼ��Kosaraju�㷨��ƿ������Ѱ�����x������δ���ʹ��ĵ㡣
�����ö�����������ʾ�߱�$g_x$���Լ�δ���ʹ��ĵ㼯S��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 260
struct BIT{
    unsigned int b[8];
    /*
    ���x==0����b����ȫ��Ϊ0
    ���x==0xff����b����ȫ��Ϊ1
    */
    void reset(int x){memset(b,x,sizeof(b));}
    void flip(int x){b[x>>5]^=1U<<(x&31);}
    //�õ�BIT��xλ��0����1
    int get(int x){return (b[x>>5]>>(x&31))&1;}
}g1[N],g2[N],vis;//g1��ʾ��ͼ,g2��ʾ��ͼ��vis��ʾδ���ʹ��ĵ㼯
int sta[N];
int n,top,cnt;
//�õ�s�����ұߵ�1֮ǰ0�ĸ���
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
            //sλ���Ի�δ���ʵĵ㼯
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
                    //cnt��ʾһ��ǿ��ͨ�����е������
                    cnt=0;
                    dfs2(sta[i]);
                    ans+=cnt*(cnt-1)/2;
                }
            printf("%d\n",ans);
        }
    }
    return 0;
}
