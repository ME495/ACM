/*
CF622F
拉格朗日插值法求1^k+2^k+3^k+...+n^k的值
时间复杂度为O(k*log(mod))，log(mod)为快速幂的复杂度
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
#define N 1000010
const ll mod=1e9+7;
ll f[N],fac_inv[N],inv[N];
void init()
{
    inv[1] = 1;
    for(int i=2;i<N;i++)
    {
        if(i>=mod) break;
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    }
    //求前N项阶乘的逆元
    fac_inv[0]=1;
    for(int i=1;i<N;++i) fac_inv[i]=fac_inv[i-1]*inv[i]%mod;
}
ll Pow(ll x,ll n)
{
    ll ans=1;
    while(n)
    {
        if(n&1) ans=ans*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return ans;
}
/*
求1^k+2^k+3^k+...+n^k的值
时间复杂度为O(k*log(mod))，log(mod)为快速幂的复杂度
*/
ll n_k(int n,int k)
{
    f[0]=0;
    for(int i=1;i<=k+2;++i)//求自然数幂和的前k+2项
        f[i]=(f[i-1]+Pow(i,k))%mod;
    if(n<=k+2) return f[n];
    ll cur=1,ans=0;
    for(int i=1;i<=k+2;++i)//预处理分式的分子
        cur=cur*(n-i)%mod;
    for(int i=1;i<=k+2;++i)
    {
        ll inv1=Pow(n-i,mod-2);//对(n-i)求逆元
        ll inv2=fac_inv[i-1]*fac_inv[k+2-i]%mod;//对阶乘求逆元
        int sign=(k+2-i)%2?-1:1;//判正负
        ans=(ans+sign*inv1*inv2%mod*f[i]%mod*cur%mod)%mod;
    }
    ans=ans+mod;
    if(ans>=mod) ans-=mod;
    return ans;
}
int main()
{
    init();
    int n,k;
    cin>>n>>k;
    cout<<n_k(n,k)<<endl;
    return 0;
}

