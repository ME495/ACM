#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define N 1000010
struct Trie{
    const static int maxn=500010;
    const static int sigma=26;
    int next[maxn][sigma],fail[maxn],end[maxn];
    int root,cnt;
    int idx(char c){return c-'a';}
    int new_node()
    {
        memset(next[cnt],-1,sizeof(next[cnt]));
        end[cnt]=0;
        return cnt++;
    }
    void init()
    {
        cnt=0;
        root=new_node();
    }
    void insert(char st[])
    {
        int now=root;
        for(int i=0;st[i];++i)
        {
            int x=idx(st[i]);
            if(next[now][x]==-1)
                next[now][x]=new_node();
            now=next[now][x];
        }
        ++end[now];
    }
    void build()
    {
        queue<int> que;
        for(int i=0;i<sigma;++i)
            if(next[root][i]==-1)
                next[root][i]=root;
            else
            {
                fail[next[root][i]]=root;
                que.push(next[root][i]);
            }
        while(!que.empty())
        {
            int x=que.front();que.pop();
            for(int i=0;i<sigma;++i)
            {
                if(next[x][i]==-1)
                    next[x][i]=next[fail[x]][i];
                else
                {
                    fail[next[x][i]]=next[fail[x]][i];
                    que.push(next[x][i]);
                }
            }
        }
    }
    int query(char st[])
    {
        int ans=0,now=root;
        for(int i=0;st[i];++i)
        {
            int x=idx(st[i]);
            now=next[now][x];
            int tmp=now;
            while(tmp!=root&&end[tmp]!=-1)
            {
                ans+=end[tmp];
                end[tmp]=-1;
                tmp=fail[tmp];
            }
        }
        return ans;
    }
}ac;
int n;
char st[N];
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        ac.init();
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%s",st);
            ac.insert(st);
        }
        ac.build();
        scanf("%s",st);
        printf("%d\n",ac.query(st));
    }
    return 0;
}
