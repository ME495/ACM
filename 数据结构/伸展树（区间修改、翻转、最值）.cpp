/*
��ģ�����еĳ�ʼԪ�ض�Ϊ0��
Ϊ�����������Ҫ�ܶ�������
�ȳ�ʼ��sz,id[],v[]��tag[],rev[]
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
int n,m,sz,rt;//sz��¼�����˶��ٸ��ڵ�
/*
fa[x]��ʾ�ڵ�x�ĸ��׵ı�ţ�
c[x][0/1]��ʾ�ڵ�x����/�Ҷ��ӵı�ţ�
id[x]��ʾ��ʼ�����б��Ϊx�Ľڵ�ı�ţ�
tag[x]��ʾ��xΪ���������ļӷ��ӳٱ�ǣ�
v[x]��ʾ�ڵ�x��ֵ��
mx[x]��ʾ��xΪ�������������ֵ�Ƕ��٣�
size[x]��ʾ��xΪ���������Ľڵ������
rev[x]��ʾ��xΪ���������ķ�ת�ӳٱ��
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
����ӷ�
Ҫ���ĵ�����Ϊ[l+1,r+1]��
���ҵ���l���ڵ㲢��������������
���ҵ���r+2���ڵ㲢�������������ڵ���Ҷ���
��r+2���ڵ������������Ҫ���µ�����
*/
inline void update(int l,int r,int val)
{
    //�ҵ���l����r+2�ڵ�
    int x=find(rt,l),y=find(rt,r+2);
    //�����������ڵ�
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    tag[z]+=val;v[z]+=val;mx[z]+=val;
}
/*
���䷭ת
Ҫ��ת������Ϊ[l+1,r+1]��
���ҵ���l���ڵ㲢��������������
���ҵ���r+2���ڵ㲢�������������ڵ���Ҷ���
��r+2���ڵ������������Ҫ��ת������
*/
inline void rever(int l,int r)
{
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    rev[z]^=1;
}
/*
�����ѯ
Ҫ��ѯ������Ϊ[l+1,r+1]��
���ҵ���l���ڵ㲢��������������
���ҵ���r+2���ڵ㲢�������������ڵ���Ҷ���
��r+2���ڵ������������Ҫ��ѯ������
*/
inline void query(int l,int r)
{
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    printf("%d\n",mx[z]);
}
/*
����ƽ���������ʹ��ʼ�����߶Ⱦ�����С��
[l,r]��ʾ��ǰ���������Ľڵ����䣬
f��ʾ��ǰ�����ĸ��׽ڵ�
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
    //���ж�Ӧ���ĵ�2~n+1���ڵ�
    //��1���ڵ��൱�����Ŀ�ʼ�ڵ㣬�����нڵ㶼С
    //��n+2���ڵ��൱�����Ľ����ڵ㣬�����нڵ㶼��
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
