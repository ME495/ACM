/*
CF622F
�������ղ�ֵ����1^k+2^k+3^k+...+n^k��ֵ
ʱ�临�Ӷ�ΪO(k^2)
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
��1^k+2^k+3^k+...+n^k��ֵ
ʱ�临�Ӷ�ΪO(k^2)
*/
ll n_k(int n,int k)
{
    f[0]=0;
    for(int i=1;i<=k+2;++i)//����Ȼ���ݺ͵�ǰk+2��
        f[i]=(f[i-1]+Pow(i,k))%mod;
    if(n<=k+2) return f[n];
    fac[0]=1;
    for(int i=1;i<=k+2;++i)//��ǰk+2��׳�
        fac[i]=fac[i-1]*i%mod;
    ll cur=1,ans=0;
    for(int i=1;i<=k+2;++i)//Ԥ�����ʽ�ķ���
        cur=cur*(n-i)%mod;
    for(int i=1;i<=k+2;++i)
    {
        ll inv1=Pow(n-i,mod-2)%mod;//��(n-i)����Ԫ
        ll inv2=Pow(fac[i-1]%mod*fac[k+2-i]%mod,mod-2)%mod;//�Խ׳�����Ԫ
        int sign=(k+2-i)%2?-1:1;//������
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
