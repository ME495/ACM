#include<cstdio>
#include<cstring>
#include<cctype>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int read() {
    int x=0,f=1;
    char c=getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) x=x*10+c-'0';
    return x*f;
}
const int maxn=1e3+10;
const int maxm=1e6+10;
const int inf=2147483646;
vector<int> inv[maxn];
struct edge {
    int v,w,nxt;
} e[maxm<<1];
int h[maxn],tot,d[maxn],n,m,prs[maxn],gap[maxn];
bool able[maxn];
void add(int u,int v,int w) {
    e[++tot]=(edge){v,w,h[u]};
    h[u]=tot;
    e[++tot]=(edge){u,0,h[v]};
    h[v]=tot;
}
struct cmp {
    int x,h;
    cmp (int x=0,int h=0):x(x),h(h) {}
    inline bool operator < (const cmp &a) const {return h<a.h;}
};
priority_queue<cmp> pq;
bool push(int x,int y,int p) {
    int w=min(prs[x],e[p].w);
    e[p].w-=w,e[p^1].w+=w,prs[x]-=w,prs[y]+=w;
    return w;
}
void Gap(int l,int s,int t) {
    for (int i=1;i<=n;++i) if (i!=s && i!=t && l<d[i] && d[i]<=n) d[i]=n+1;
}
int maxflow(int s,int t) {
    while (!pq.empty()) pq.pop();
    memset(prs,0,sizeof prs),memset(d,0,sizeof d),memset(gap,0,sizeof gap);
    d[s]=n,prs[s]=inf,pq.push(cmp(s,d[s]));
    while (!pq.empty()) {
        int x=pq.top().x;
        pq.pop();
        if (!prs[x]) continue;
        for (int i=h[x],v=e[i].v;i;i=e[i].nxt,v=e[i].v)
            if ((x==s||d[x]==d[v]+1)&&push(x,v,i)&&v!=t&&v!=s)
                pq.push(cmp(v,d[v]));
        if (x!=s && x!=t && prs[x]) {
            if (!(--gap[d[x]])) Gap(d[x],s,t);
            ++gap[++d[x]];
            pq.push(cmp(x,d[x]));
        }
    }
    return prs[t];
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("test.in","r",stdin);
    freopen("my.out","w",stdout);
#endif
    while (~scanf("%d%d",&m,&n)) {
        memset(h,0,sizeof h),tot=1;
        for (int i=1;i<=m;++i) {
            int x=read(),y=read(),w=read();
            if (!w) continue;
            add(x,y,w);
        }
        int ans=maxflow(1,n);
        printf("%d\n",ans);
    }
    return 0;
}
