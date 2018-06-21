/**
��չkmp�Ƕ�KMP�㷨����չ��������������⣺
����ĸ��S�����ִ�T����S�ĳ���Ϊn��T�ĳ���Ϊm��
��T��S��ÿһ����׺�������ǰ׺��
Ҳ����˵����extend����,extend[i]��ʾT��S[i,n-1]�������ǰ׺��
Ҫ�������extend[i](0<=i<n)��
�踨������nxt[i]��ʾT[i,m-1]��T�������ǰ׺����
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
