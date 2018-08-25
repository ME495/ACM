/*
CF622F
�������ղ�ֵ����1^k+2^k+3^k+...+n^k��ֵ
ʱ�临�Ӷ�ΪO(k*log(mod))��log(mod)Ϊ�����ݵĸ��Ӷ�
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
    //��ǰN��׳˵���Ԫ
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
��1^k+2^k+3^k+...+n^k��ֵ
ʱ�临�Ӷ�ΪO(k*log(mod))��log(mod)Ϊ�����ݵĸ��Ӷ�
*/
ll n_k(int n,int k)
{
    f[0]=0;
    for(int i=1;i<=k+2;++i)//����Ȼ���ݺ͵�ǰk+2��
        f[i]=(f[i-1]+Pow(i,k))%mod;
    if(n<=k+2) return f[n];
    ll cur=1,ans=0;
    for(int i=1;i<=k+2;++i)//Ԥ�����ʽ�ķ���
        cur=cur*(n-i)%mod;
    for(int i=1;i<=k+2;++i)
    {
        ll inv1=Pow(n-i,mod-2);//��(n-i)����Ԫ
        ll inv2=fac_inv[i-1]*fac_inv[k+2-i]%mod;//�Խ׳�����Ԫ
        int sign=(k+2-i)%2?-1:1;//������
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

