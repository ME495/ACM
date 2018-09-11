/**
题意：给你n*m（1<=n,m<=11）的方格矩阵，要求用1*2的多米诺骨牌去填充，问有多少种填充方法
使用2进制编码，1表示有向下延伸的插头
**/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 11
typedef long long ll;
ll dp[N][1<<N];
int n,m;
bool check(int s)//状态s中的0是否能全部放横着的骨牌
{
    int cnt=0;
    for(int i=0;i<m;++i)
        if((s>>i)&1)
        {
            if(cnt&1)//如果连续的0的数量为奇数，则放不下 
                return false;
            cnt=0;
        }
        else ++cnt;
    if(cnt&1)//如果连续的0的数量为奇数，则放不下
        return false;
    return true;
}
int sub(int s1,int s2)
{
    if(s1==0) return -1;
    return (s1-1)&s2; 
}
int main()
{
    while(scanf("%d%d",&n,&m),n)
    {
        memset(dp,0,sizeof(dp));
        for(int s=0;s<(1<<m);++s)
            if(check(s)) dp[0][s]=1;
        int z=(1<<m)-1;
        for(int i=0;i<n-1;++i)
            for(int s1=0;s1<(1<<m);++s1)
            {
                if(dp[i][s1]==0) continue;
                int tmp=s1^z;
                for(int s2=tmp;s2>=0;s2=sub(s2,tmp))//枚举tmp的子集
                    if(check(s1|s2))//把s2中上方为插头的位置变为1，再判断 
                        dp[i+1][s2]+=dp[i][s1];
            }
        printf("%lld\n",dp[n-1][0]);
    }
    return 0;
}

/*
题意：给你一个m * n的棋盘，有的格子是障碍，找一条或多条回路使得经过每个非障碍格子恰好一次，问有多少中方法．m, n ≤ 12
使用二进制编码，1表示有插头，参考cdq的论文
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 12
ll dp[N][N][1<<N];
int g[N][N];
int n,m;
int main()
{
	int ca;
	scanf("%d",&ca);
	for(int cas=1;cas<=ca;++cas)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				scanf("%d",&g[i][j]);
		memset(dp,0,sizeof(dp));
		dp[0][m][0]=1;
		for(int i=1;i<=n;++i)
		{
			for(int s=0;s<(1<<m);++s)
				dp[i][0][s<<1]=dp[i-1][m][s];
			for(int j=1;j<=m;++j)
				for(int s=0;s<(1<<m+1);++s)
				{
					int x=(s>>j-1)&1;//(i,j)左方的插头
					int y=(s>>j)&1;//(i,j)上方的插头
					if(g[i][j])//如果为空白方格
					{
						if(x^y)//左方和上方只有一个方向有插头，此时接上插头，并向下或或向右延伸
							dp[i][j][s]=dp[i][j-1][s]+dp[i][j-1][s^(1<<j-1)^(1<<j)];
						else//左方和上方都有插头，此时把两个插头联通
							dp[i][j][s]=dp[i][j-1][s^(1<<j-1)^(1<<j)];
					}
					else//如果为障碍 
					{
						if(x==0&&y==0)//障碍方格只能从左方和上方没有插头的状态转移
							dp[i][j][s]=dp[i][j-1][s];
					}
				}
		}
		printf("Case %d: There are %I64d ways to eat the trees.\n",cas,dp[n][m][0]);
	}
	return 0;
}

/*
题意：给你一个m * n的棋盘，有的格子是障碍，找一条回路使得经过每个非障碍格子恰好一次，问有多少中方法．m, n ≤ 12
使用8进制编码，非0值表示插头属于的联通块，参考cdq的论文
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 12
#define M 1000010
typedef long long ll;
struct Hash{
    const static int mod=(1<<15)-1;
    int head[mod+1],pre[M],sz;
    ll status[M],f[M];
    void init()
    {
        sz=0;
        memset(head,-1,sizeof(head));
    }
    void insert(ll s,ll w)
    {
        ll h=s&mod;
        for(int i=head[h];i!=-1;i=pre[i])
        {
            if(status[i]==s)
            {
                f[i]+=w;return;
            }
        }
        status[sz]=s;f[sz]=w;pre[sz]=head[h];head[h]=sz++;
    }
}ha[2];
bool g[N+2][N+2];
char st[N+10];
int n,m,ex,ey;
void decode(ll s,int code[],int m)//按8进制解码
{
    for(int i=0;i<=m;++i)
    {
        code[i]=s&7;
        s>>=3;
    }
}
ll encode(int code[],int m)//按8进制编码，联通块用最小表示法表示
{
    int fa[10],cnt=0;
    memset(fa,-1,sizeof(fa));
    fa[0]=0;
    ll s=0;
    for(int i=0;i<=m;++i)
    {
        if(fa[code[i]]==-1) fa[code[i]]=++cnt;
        code[i]=fa[code[i]];
        s|=(ll)code[i]<<i*3;
    }
    return s;
}
void shift(int code[],int m)
{
    for(int i=m;i>0;--i) code[i]=code[i-1];
    code[0]=0;
}
void dpblank(int x,int y,int cur)//对空白方格dp
{
    int code[N+1];
    ll s;
    for(int i=0;i<ha[cur].sz;++i)
    {
        decode(ha[cur].status[i],code,m);
		int left=code[y-1],up=code[y];//(x,y)左方的插头和上方的插头
        /*
		if(...)
		{
			//可以把要特殊考率的点写在这里
			continue;
		}
		*/
		if(left&&up)//如果左方和右方的插头存在
        {
            if(left==up)//如果两个插头属于同一个联通块，则只有位于最后一个空白方格才能进行转移
            {
                if(x==ex&&y==ey)//(x,y)位于最后一个方格
                {
                    code[y-1]=code[y]=0;
                    if(y==m) shift(code,m);//最后一列
                    ha[cur^1].insert(encode(code,m),ha[cur].f[i]);
                }
            }
            else//两个插头属于不同的联通块，则合并这两个联通块
            {
                code[y-1]=code[y]=0;
                for(int i=0;i<=m;++i)
                    if(code[i]==left) code[i]=up;
                if(y==m) shift(code,m);
                ha[cur^1].insert(encode(code,m),ha[cur].f[i]);
            }
        }
        else if((left&&!up)||(!left&&up))//左方或上方有一个插头
        {
            int t;
            if(left) t=left;
            else t=up;
            if(g[x][y+1])//向右延伸
            {
                code[y-1]=0;code[y]=t;
                ha[cur^1].insert(encode(code,m),ha[cur].f[i]);
            }
            if(g[x+1][y])//向下延伸
            {
                code[y-1]=t;code[y]=0;
                if(y==m) shift(code,m);//最后一列
                ha[cur^1].insert(encode(code,m),ha[cur].f[i]);
            }
        }
        else//左方和上方都没有插头
        {
            if(g[x+1][y]&&g[x][y+1])//产生一个新联通块，向左和向右都要延伸
            {
                code[y-1]=code[y]=9;//新联通块的编号不能与当前的重复
                ha[cur^1].insert(encode(code,m),ha[cur].f[i]);
            }
			/*
			//如果(x,y)是可选点
			code[y-1]=code[y]=0;
            if(y==m) shift(code,m);
            ha[cur^1].insert(encode(code,m),ha[cur].f[i]);
			*/
        }
    }
}
void dpblock(int x,int y,int cur)//对障碍方格进行dp
{
    ll s;
    int code[N+1];
    for(int i=0;i<ha[cur].sz;++i)
    {
        decode(ha[cur].status[i],code,m);
        if(y==m) shift(code,m);//会于最后一列
        ha[cur^1].insert(encode(code,m),ha[cur].f[i]);
    }
}
ll solve()
{
    int cur=0;
    ha[cur].init();
    ha[cur].insert(0,1);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            ha[cur^1].init();
            if(g[i][j]) dpblank(i,j,cur);
            else dpblock(i,j,cur);
            cur^=1;
        }
    ll ans=0;
    for(int i=0;i<ha[cur].sz;++i)
        ans+=ha[cur].f[i];
    return ans;
}
int main()
{
    scanf("%d%d",&n,&m);
    ex=0;
    memset(g,0,sizeof(g));
    for(int i=1;i<=n;++i)
    {
        scanf("%s",st+1);
        for(int j=1;j<=m;++j)
            if(st[j]=='.') 
            {
                g[i][j]=true;
                ex=i;ey=j;
            }
    }
    if(ex==0) printf("0\n");
    else printf("%I64d\n",solve());
    return 0;
}