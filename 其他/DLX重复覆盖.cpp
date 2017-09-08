#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct DLX {
    const static int maxnode = 100010; //最多多少个‘1’
    const static int MaxM = 1010;//最大行数
    const static int MaxN = 1010;//最大列数
    int n,m,SIZE;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    //L,R,D,U四个数组记录某节点上下左右邻居
    int H[MaxN], S[MaxM];//H记录排头，S记录某列有多少个节点
    int ansd, ans[MaxN];//ansd记录覆盖所有列最少要用多少行，ans[]记录方案
    void init(int _n,int _m) {//n为行数，m为列数
        n = _n;
        m = _m;
        for(int i = 0; i <= m; i++) {
            S[i] = 0;U[i] = D[i] = i;L[i] = i-1;R[i] = i+1;
        }
        R[m] = 0;L[0] = m;SIZE = m;
        for(int i = 1; i <= n; i++) H[i] = -1;
    }
    void Link(int r,int c) {
        ++S[Col[++SIZE]=c];
        Row[SIZE] = r;
        D[SIZE] = D[c];
        U[D[c]] = SIZE;
        U[SIZE] = c;
        D[c] = SIZE;
        if(H[r] < 0)H[r] = L[SIZE] = R[SIZE] = SIZE;
        else {
            R[SIZE] = R[H[r]];
            L[R[H[r]]] = SIZE;
            L[SIZE] = H[r];
            R[H[r]] = SIZE;
        }
    }
    void exact_Remove(int c) {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }
    void repeat_remove(int c) {
        for(int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void repeat_resume(int c) {
        for(int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }

    int f() { //估价函数。
        bool vv[MaxM];
        int ret = 0, c, i, j;
        for(c = R[0]; c != 0; c = R[c]) vv[c] = 1;
        for(c = R[0]; c != 0; c = R[c])
            if(vv[c]) {
                ++ret, vv[c] = 0;
                for(i = D[c]; i != c; i = D[i])
                    for(j = R[i]; j != i; j = R[j])
                        vv[Col[j]] = 0;
            }
        return ret;
    }
    /*
    重复覆盖，d为搜索深度，ansd初始化为无穷大
    如果只要找出可行解而不是最优解，可以找到解后直接return true
    */
    bool repeat_dance(int d) {
        //求最优解时才使用
        if(d + f() >= ansd) return false; //估价函数剪枝，A*搜索
        if(R[0] == 0) {
            if(d < ansd) ansd = d;
            return true;
        }
        bool flag=false;
        int c = R[0], i, j;
        for(i = R[0]; i; i = R[i])
            if(S[i] < S[c]) c = i;
        for(i = D[c]; i != c; i = D[i]) {
            repeat_remove(i);
            ans[d] = Row[i];
            for(j = R[i]; j != i; j = R[j]) repeat_remove(j);
            //如果只要找出可行解而不是最优解，可以找到解后直接return true
            //if(repeat_dance(d+1)) return true;
            if(repeat_dance(d + 1)) flag=true;
            for(j = L[i]; j != i; j = L[j]) repeat_resume(j);
            repeat_resume(i);
        }
        //return false;
        return flag;
    }
    void exact_resume(int c) {
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                ++S[Col[U[D[j]]=D[U[j]]=j]];
        L[R[c]] = R[L[c]] = c;
    }
    /*
    精确覆盖，d为搜索深度，ansd初始化为无穷大
    如果只要找出可行解而不是最优解，可以找到解后直接return true
    */
    bool exact_Dance(int d) {
        //求最优解时才使用
        if(d + f() >= ansd) return false;
        if(R[0] == 0) {
            if(d < ansd) ansd = d;
            return true;
        }
        bool flag=false;
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(S[i] < S[c])
                c = i;
        exact_Remove(c);
        for(int i = D[c]; i != c; i = D[i]) {
            ans[d] = Row[i];
            for(int j = R[i]; j != i; j = R[j]) exact_Remove(Col[j]);
            //如果只要找出可行解而不是最优解，可以找到解后直接return true
            //if(exact_Dance(d+1)) return true;
            if(exact_Dance(d+1)) flag=true;
            for(int j = L[i]; j != i; j = L[j]) exact_resume(Col[j]);
        }
        exact_resume(c);
        //return false;
        return flag;
    }
}dlx;

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        dlx.init(n,n);
        int x,y;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&x,&y);//在(x,y)和(y,x)处都有1
            dlx.Link(x,y);dlx.Link(y,x);
        }
        for(int i=1;i<=n;++i) dlx.Link(i,i);//在(i,i)处有1
        dlx.ansd=0x3f3f3f3f;
        dlx.repeat_dance(0);
        printf("%d\n",dlx.ansd);
    }
}
