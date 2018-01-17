#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;y=0;return a;
	}
	ll res=exgcd(b,a%b,x,y);
	ll tmp=x;
	x=y;y=tmp-a/b*y;
	return res;
}
struct Hash{
    static const ll mod=10007;
    vector<pair<ll,ll> > g[mod];
    Hash()
    {
        for(int i=0;i<mod;++i) g[i].clear();
    }
    bool find(ll x)
    {
        ll h=x%mod;
        for(int i=0;i<g[h].size();++i)
            if(g[h][i].first==x) return true;
        return false;
    }
    ll get(ll x)
    {
        ll h=x%mod;
        bool flag=false;
        for(int i=0;i<g[h].size();++i)
            if(g[h][i].first==x)
                return g[h][i].second;
        return 0;
    }
    void doing(ll t,ll y)
    {
        ll h=t%mod;
        bool flag=false;
        for(int i=0;i<g[h].size();++i)
            if(g[h][i].first==t)
            {
                g[h][i].second=min(g[h][i].second,y);
                flag=true;
                break;
            }
        if(!flag) g[h].push_back(make_pair(t,y));
    }
};
/*==================================================*\
| Baby-Step-Giant-Step 大步小步算法
| 求 a^x === b (mod p) 中的 x值 -- 此处p仅为素数
| 实际运用中用自己的hash表代替map可防TLE
\*==================================================*/
ll BSGS(ll a, ll b, ll p) {
    a %= p; b %= p;
//    map<ll, ll> h;
    Hash h=Hash();
    ll m = ceil(sqrt(p)), x, y, d, t = 1, v = 1;
    for(ll i = 0; i < m; ++i) {
//        if(h.count(t)) h[t] = min(h[t], i);
//        else h[t] = i;
        h.doing(t,i);
        t = (t*a) % p;
    }
    for(ll i = 0; i < m; ++i) {
        d = exgcd(v, p, x, y);
        x = (x* b/d % p + p) % (p);
//        if(h.count(x)) return i*m + h[x];
        if(h.find(x)) return i*m + h.get(x);
        v = (v*t) % p;
    }
    return -1;
}
int main()
{
    ll a,b,p;
    while(scanf("%lld%lld%lld",&p,&a,&b)!=EOF)
    {
        ll ans=BSGS(a,b,p);
        if(ans==-1) printf("no solution\n");
        else printf("%lld\n",ans);
    }
    return 0;
}
