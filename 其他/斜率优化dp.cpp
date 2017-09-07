/*
原始dp方程：dp[i]=min(dp[i], dp[j]+sqr(sum[i]-sum[j-1])+m)
转换后：dp[j]+sqr(sum[j-1]) = 2*sum[i] * sum[j-1] + dp[i]-sqr(sum[i])-M
                 y          =     k    *    x     +        b
总结：与j有关的且系数与i有关的项作为x，
      其他与j有关的项作为y，
	  dp[i]一定要在b中，
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 500010
typedef long long ll;
struct Point{
    ll x,y;
    Point(){}
    Point(ll x,ll y):x(x),y(y){}
}q[N];
int n,m;
ll dp[N],c[N],sum[N];
ll cross(Point &p0,Point &p1,Point &p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;++i) scanf("%lld",&c[i]);
        sum[0]=0;
        for(int i=1;i<=n;++i) sum[i]=sum[i-1]+c[i];
        dp[0]=0;
        q[0]=Point(0,0);
        int s=0,t=0;
        ll k,z;
        Point p;
        for(int i=1;i<=n;++i)
        {
            k=2*sum[i];z=sum[i]*sum[i]+m;
            while(s<t&&q[s].y-k*q[s].x+z>=q[s+1].y-k*q[s+1].x+z) ++s;
            dp[i]=q[s].y-k*q[s].x+z;
            p=Point(sum[i],dp[i]+sum[i]*sum[i]);
            while(s<t&&cross(q[t-1],q[t],p)<=0) --t;
            q[++t]=p;
        }
        printf("%lld\n",dp[n]);
    }
    return 0;
}