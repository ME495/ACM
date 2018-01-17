#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
ll a, b, c, ans;
struct MAP
{
    const static ll mod=10007;
    vector<pair<ll,ll> > g[mod];
    void clear()
    {
        for(int i=0;i<mod;++i) g[i].clear();
    }
    int count(ll x)
    {
        ll pos = x%mod;
        for(int i=0;i<g[pos].size();++i)
            if(g[pos][i].first==x) return true;
        return false;
    }
    void insert(ll x,ll y)
    {
        ll pos = x%mod;
        for(int i=0;i<g[pos].size();++i)
            if(g[pos][i].first==x)
            {
                g[pos][i].second=y;
                return;
            }
        g[pos].push_back(make_pair(x,y));
    }
    ll query(ll x)
    {
        ll pos = x%mod;
        for(int i=0;i<g[pos].size();++i)
            if(g[pos][i].first==x)
                return g[pos][i].second;
        return -1;
    }
} mp;
ll Pow(ll x, ll n, ll mod)
{
    ll ans = 1;
    while(n)
    {
        if(n&1) ans = ans*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return ans;
}
/*==================================================*\
| Baby-Step-Giant-Step 大步小步算法
| 求 a^x === b (mod c) 中的 x值 -- 此处p无限制
| 实际运用中用自己的hash表代替map可防TLE
\*==================================================*/
ll exBSGS(ll a, ll b, ll c)
{
    if (b == 1)
        return 0;
    ll cnt = 0, d = 1, t;
    while ((t = __gcd(a, c)) != 1)
    {
        if (b%t)
            return -1;
        ++cnt, b /= t, c /= t, d = d*(a/t)%c;
        if (d == b)
            return cnt;
    }
    mp.clear();
    ll tim = ceil(sqrt(c)), tmp = b%c;
    for (int i = 0; i <= tim; i++)
    {
        mp.insert(tmp, i);
        tmp = tmp*a%c;
    }
    t = tmp = Pow(a, tim, c);
    tmp = (tmp*d)%c;
    for (int i = 1; i <= tim; i++)
    {
        if (mp.count(tmp))
            return tim*i-mp.query(tmp)+cnt;
        tmp = tmp*t%c;
    }
    return -1;
}
int main()
{
    while (scanf("%lld%lld%lld", &a, &c, &b),a||b||c)
    {
        if ((ans = exBSGS(a%c, b%c, c)) == -1)
            printf("No Solution\n");
        else printf("%lld\n",ans);
    }
    return 0;
}
