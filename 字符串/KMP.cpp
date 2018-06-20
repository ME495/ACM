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
返回模式串T在主串S中首次出现的位置
返回的位置是从0开始的。
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
返回模式串T在主串S中出现的次数
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
            j=nxt[j];//子串可重叠
            //j=0;//子串不可重叠
        }
    }
    return ans;
}
