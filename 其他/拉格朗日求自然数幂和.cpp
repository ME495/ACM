/*
CF622F
拉格朗日插值法求1^k+2^k+3^k+...+n^k的值
时间复杂度为O(k^2)
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
#define N 1000010
const ll mod=1e9+7;
ll f[N],fac[N];
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
时间复杂度为O(k^2)
*/
ll n_k(int n,int k)
{
    f[0]=0;
    for(int i=1;i<=k+2;++i)//求自然数幂和的前k+2项
        f[i]=(f[i-1]+Pow(i,k))%mod;
    if(n<=k+2) return f[n];
    fac[0]=1;
    for(int i=1;i<=k+2;++i)//求前k+2项阶乘
        fac[i]=fac[i-1]*i%mod;
    ll cur=1,ans=0;
    for(int i=1;i<=k+2;++i)//预处理分式的分子
        cur=cur*(n-i)%mod;
    for(int i=1;i<=k+2;++i)
    {
        ll inv1=Pow(n-i,mod-2)%mod;//对(n-i)求逆元
        ll inv2=Pow(fac[i-1]%mod*fac[k+2-i]%mod,mod-2)%mod;//对阶乘求逆元
        int sign=(k+2-i)%2?-1:1;//判正负
        ans=(ans+sign*inv1*inv2%mod*f[i]%mod*cur%mod)%mod;
    }
    ans=(ans+mod)%mod;
    return ans;
}
int main()
{
    int n,k;
    cin>>n>>k;
    cout<<n_k(n,k)<<endl;
    return 0;
}
