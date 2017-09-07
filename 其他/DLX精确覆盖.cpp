#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
using namespace std;
struct DLX{
    const static int maxn=1001,maxm=1010,maxnode=maxn*maxm;
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode];//十字链表
    int ans[maxn],cnt;//解
    int size;//节点数
    int row[maxnode],col[maxnode];//各点行列编号
    int S[maxm];//各列结点数
    int H[maxn];
    void del(int c){//删除一列
        L[R[c]]=L[c];R[L[c]]=R[c];
        for(int i=D[c];i!=c;i=D[i])
            for(int j=R[i];j!=i;j=R[j])
                U[D[j]]=U[j],D[U[j]]=D[j],--S[col[j]];
    }
    void add(int c){//恢复一列
        R[L[c]]=L[R[c]]=c;
        for(int i=U[c];i!=c;i=U[i])
            for(int j=L[i];j!=i;j=L[j])
                ++S[col[U[D[j]]=D[U[j]]=j]];
    }
    void init(int m){//初始化，建立虚拟节点
        for(int i=0;i<=m;i++){
            S[i]=0;
            L[i]=i-1;
            R[i]=i+1;
            U[i]=D[i]=i;
        }
        L[0]=m;R[m]=0;
        size=m+1;
        memset(H,-1,sizeof(H));
    }
    void link(int x,int y){//加入一个节点
        ++S[col[size]=y];
        row[size]=x;
        D[size]=D[y];
        U[D[y]]=size;
        U[size]=y;
        D[y]=size;
        if(H[x]<0)H[x]=L[size]=R[size]=size;
        else {
            R[size]=R[H[x]];
            L[R[H[x]]]=size;
            L[size]=H[x];
            R[H[x]]=size;
        }
        size++;
    }
    bool dfs(int k){//dfs寻找可行方案
        if(!R[0]){
            cnt=k;
            return 1;
        }
        int c=R[0];for(int i=R[0];i;i=R[i])if(S[c]>S[i])c=i;
        del(c);
        for(int i=D[c];i!=c;i=D[i]){
            for(int j=R[i];j!=i;j=R[j])del(col[j]);
            ans[k]=row[i];
            if(dfs(k+1))return true;
            for(int j=L[i];j!=i;j=L[j])add(col[j]);
        }
        add(c);
        return 0;
    }
}dlx;
int n,m;
int main()
{
     //freopen("data.in","r",stdin);
     //freopen("data.out","w",stdout);
     while(scanf("%d%d",&n,&m)!=EOF){
         int i,j,k;
         dlx.init(m);
         int c;
         for(i=1;i<=n;i++){
             scanf("%d",&c);
             while(c--)
             {
                 scanf("%d",&j);
                 dlx.link(i,j);
             }
         }
         if(dlx.dfs(0))
         {
             printf("%d ",dlx.cnt);
             for(int i=0;i<dlx.cnt;++i)
                printf("%d ",dlx.ans[i]);
         }
         else printf("NO\n");
         printf("\n");
     }
     return 0;
}
