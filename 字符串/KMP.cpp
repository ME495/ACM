#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1000010
int nxt[N];
char S[N],T[N];
void get_next(char T[N],int tlen)
{
    int i=0,j=-1;
    nxt[0]=-1;
    while(i<tlen)
        if(j==-1||T[i]==T[j]) nxt[++i]=++j;
        else j=nxt[j];
}
/*
����ģʽ��T������S���״γ��ֵ�λ��
���ص�λ���Ǵ�0��ʼ�ġ�
*/
int kmp_index(char S[],int slen,char T[],int tlen)
{
    get_next(T,tlen);
    int j=0;
    for(int i=0;i<slen;++i)
    {
        while(j>0&&S[i]!=T[j]) j=nxt[j];
        if(S[i]==T[j]) ++j;
        if(j==tlen) return i-tlen+1;
    }
    return -1;
}
/*
����ģʽ��T������S�г��ֵĴ���
*/
int kmp_count(char S[],int slen,char T[],int tlen)
{
    get_next(T,tlen);
    int ans=0,j=0;
    for(int i=0;i<slen;++i)
    {
        while(j>0&&S[i]!=T[j]) j=nxt[j];
        if(S[i]==T[j]) ++j;
        if(j==tlen)
        {
            ++ans;
            j=nxt[j];//�Ӵ����ص�
            //j=0;//�Ӵ������ص�
        }
    }
    return ans;
}
