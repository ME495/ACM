/*
此模板序列的初始元素都为0，
为单样例，如果要跑多样例，
先初始化sz,id[],v[]，tag[],rev[]
*/
#include<iostream>
#include<cstdio>
#define inf 0x7fffffff
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,sz,rt;//sz记录分配了多少个节点
/*
fa[x]表示节点x的父亲的编号，
c[x][0/1]表示节点x的左/右儿子的编号，
id[x]表示初始序列中标号为x的节点的编号，
tag[x]表示以x为根的子树的加法延迟标记，
v[x]表示节点x的值，
mx[x]表示以x为根的子树的最大值是多少，
size[x]表示以x为根的子树的节点个数，
rev[x]表示以x为根的子树的翻转延迟标记
*/
int fa[50005],c[50005][2],id[50005];
int tag[50005],v[50005],mx[50005],size[50005];
bool rev[50005];
inline void pushup(int k)
{
    int l=c[k][0],r=c[k][1];
    mx[k]=max(mx[l],mx[r]);
    mx[k]=max(mx[k],v[k]);
    size[k]=size[l]+size[r]+1;
}
void pushdown(int k)
{
    int l=c[k][0],r=c[k][1],t=tag[k];
    if(t)
    {
		tag[k]=0;
		if(l){tag[l]+=t;mx[l]+=t;v[l]+=t;}
		if(r){tag[r]+=t;mx[r]+=t;v[r]+=t;}
    }
    if(rev[k])
    {
		rev[k]=0;
		rev[l]^=1;rev[r]^=1;
		swap(c[k][0],c[k][1]);
    }
}
void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l,r;
    if(c[y][0]==x)l=0;else l=1;r=l^1;
    if(y==k)k=x;
    else
    {
        if(c[z][0]==y)c[z][0]=x;
        else c[z][1]=x;
    }
    fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
    c[y][l]=c[x][r];c[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x,int &k)
{
    while(x!=k)
    {
		int y=fa[x],z=fa[y];
		if(y!=k)
		{
			if(c[y][0]==x^c[z][0]==y)
				rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
    }
}
int find(int k,int rank)
{
    if(tag[k]||rev[k])pushdown(k);
    int l=c[k][0],r=c[k][1];
    if(size[l]+1==rank)return k;
    else if(size[l]>=rank)return find(l,rank);
    else return find(r,rank-size[l]-1);
}
/*
区间加法
要更改的区间为[l+1,r+1]，
先找到第l个节点并将其提升到根，
再找到第r+2个节点并将其提升到根节点的右儿子
第r+2个节点的左子树就是要更新的区间
*/
inline void update(int l,int r,int val)
{
    //找到第l、第r+2节点
    int x=find(rt,l),y=find(rt,r+2);
    //提升这两个节点
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    tag[z]+=val;v[z]+=val;mx[z]+=val;
}
/*
区间翻转
要翻转的区间为[l+1,r+1]，
先找到第l个节点并将其提升到根，
再找到第r+2个节点并将其提升到根节点的右儿子
第r+2个节点的左子树就是要翻转的区间
*/
inline void rever(int l,int r)
{
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    rev[z]^=1;
}
/*
区间查询
要查询的区间为[l+1,r+1]，
先找到第l个节点并将其提升到根，
再找到第r+2个节点并将其提升到根节点的右儿子
第r+2个节点的左子树就是要查询的区间
*/
inline void query(int l,int r)
{
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    printf("%d\n",mx[z]);
}
/*
构造平衡二叉树，使初始的树高度尽可能小，
[l,r]表示当前子树包含的节点区间，
f表示当前子树的父亲节点
*/
inline void build(int l,int r,int f)
{
    if(l>r)return;
    int now=id[l],last=id[f];
    if(l==r)
    {
		fa[now]=last;size[now]=1;
		if(l<f)c[last][0]=now;
		else c[last][1]=now;
		return;
    }
    int mid=(l+r)>>1;now=id[mid];
    build(l,mid-1,mid);build(mid+1,r,mid);
    fa[now]=last;pushup(now);
    if(mid<f)c[last][0]=now;
    else c[last][1]=now;
}
int main()
{
    mx[0]=-inf;
    n=read();m=read();
    //序列对应树的第2~n+1个节点
    //第1个节点相当于树的开始节点，比所有节点都小
    //第n+2个节点相当于树的结束节点，比所有节点都大
    for(int i=1;i<=n+2;i++)
		id[i]=++sz;
    build(1,n+2,0);rt=(n+3)>>1;
    for(int i=1;i<=m;i++)
    {
		int f=read(),l,r,val;
		switch(f)
		{
		case 1:l=read();r=read();val=read();update(l,r,val);break;
		case 2:l=read();r=read();rever(l,r);break;
		case 3:l=read();r=read();query(l,r);break;
		}
    }
    return 0;
}
