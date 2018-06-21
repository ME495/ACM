/**
拓展kmp是对KMP算法的扩展，它解决如下问题：
定义母串S，和字串T，设S的长度为n，T的长度为m，
求T与S的每一个后缀的最长公共前缀，
也就是说，设extend数组,extend[i]表示T与S[i,n-1]的最长公共前缀，
要求出所有extend[i](0<=i<n)，
设辅助数组nxt[i]表示T[i,m-1]和T的最长公共前缀长度
**/
#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=100010;
int nxt[N],extand[N];
char S[N],T[N];
void get_next(char T[],int tlen)
{
    int a=0;
    nxt[0]=tlen;
    while(a<tlen-1 && T[a]==T[a+1]) a++;
    nxt[1]=a;
    a=1;
    for(int k=2; k<tlen; k++)
    {
        int p=a+nxt[a]-1,L=nxt[k-a];
        if( (k-1)+L >= p)
        {
            int j = (p-k+1)>0 ? (p-k+1) : 0;
            while(k+j<tlen && T[k+j]==T[j]) j++;
            nxt[k]=j;
            a=k;
        }
        else
            nxt[k]=L;
    }
}
void get_extand(char S[],int slen,char T[],int tlen)
{
    get_next(T,tlen);
    int a=0;
    int min_len = slen < tlen ? slen : tlen;
    while(a<min_len && S[a]==T[a]) a++;
    extand[0]=a;
    a=0;
    for(int k=1; k<slen; k++)
    {
        int p=a+extand[a]-1, L=nxt[k-a];
        if( (k-1)+L >= p)
        {
            int j= (p-k+1) > 0 ? (p-k+1) : 0;
            while(k+j<slen && j<tlen && S[k+j]==T[j]) j++;
            extand[k]=j;
            a=k;
        }
        else
            extand[k]=L;
    }
}
int main(void)
{
    while(scanf("%s%s",S,T)==2)
    {
        int slen=strlen(S),tlen=strlen(T);
        get_extand(S,slen,T,tlen);
        for(int i=0; i<tlen; i++)
            printf("%d ",nxt[i]);
        puts("");
        for(int i=0; i<slen; i++)
            printf("%d ",extand[i]);
        puts("");
    }
    return 0;
}
