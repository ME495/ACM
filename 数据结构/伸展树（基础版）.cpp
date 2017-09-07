/*
此模板为单样例，要跑多样例，
先初始化tr[][],fa[],num[],size
*/
#include<iostream>
#include<cstdio>
using namespace std;
int n,size,rt,kind,t1,t2;//sz记录分配了多少个节点
long long ans;
/*
tr[x][0/1]表示节点x的左/右儿子节点，
num[x]表示节点x的值，
fa[x]表示节点x的父亲节点
*/
int tr[80001][2],num[80001],fa[80001];
/*
旋转操作
将节点x提升一层，节点k为节点x为要提升到的最终目标，
*/
void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l,r;
    if(tr[y][0]==x) l=0;
    else l=1;
    r=l^1;
    //如果y节点是k节点，则再将x提升一层后，x到达k
    if(y==k) k=x;
    else
    {
        if(tr[z][0]==y)tr[z][0]=x;
        else tr[z][1]=x;
    }
    fa[x]=z;fa[y]=x;fa[tr[x][r]]=y;
    tr[y][l]=tr[x][r];tr[x][r]=y;
}
/*
伸展操作
将x节点提升到k节点所在的位置
*/
void splay(int x,int &k)
{
	int y,z;
	while(x!=k)
	{
		y=fa[x],z=fa[y];
		if(y!=k)
		{
			if((tr[y][0]==x)^(tr[z][0]==y))
                rotate(x,k);//之字形
			else
                rotate(y,k);//一字形
		}
		rotate(x,k);
	}
}
/*
插入操作
将值为x的节点插入树中，
k为当前所在节点，
last为上一个节点，也就是父节点
*/
void ins(int &k,int x,int last)
{
	if(k==0)//已经找到值x应该处于的位置
    {
        size++;k=size;
        num[k]=x;fa[k]=last;
        splay(k,rt);
        return;
    }
	if(x<num[k])ins(tr[k][0],x,k);
	else ins(tr[k][1],x,k);
}
/*
删除操作
将节点x从树中删除，
先将节点x提升到根节点，
再把根节点（x节点）删除，并把右子树的父亲作为根节点，
然后把左子树接到右子树最小的节点上
*/
void del(int x)
{
	splay(x,rt);
	if(tr[x][0]*tr[x][1]==0)
        rt=tr[x][0]+tr[x][1];
	else
	{
		int k=tr[x][1];
		while(tr[k][0])k=tr[k][0];
		tr[k][0]=tr[x][0];fa[tr[x][0]]=k;
		rt=tr[x][1];
	}
	fa[rt]=0;
}
/*
找到比值x小的第一个值，并存在t1中
*/
void ask_before(int k,int x)
{
	if(k==0)return;
	if(num[k]<=x){t1=k;ask_before(tr[k][1],x);}
	else ask_before(tr[k][0],x);
}
/*
找到比值x大的第一个值，并存在t2中
*/
void ask_after(int k,int x)
{
	if(k==0)return;
	if(num[k]>=x){t2=k;ask_after(tr[k][0],x);}
	else ask_after(tr[k][1],x);
}

int main()
{
    scanf("%d",&n);
    int f,x;
    for(int i=1;i<=n;i++)
    {
		scanf("%d%d",&f,&x);
		if(!rt){kind=f;ins(rt,x,0);}
		else if(kind==f){ins(rt,x,0);}
		else
		{
			t1=t2=-1;
			ask_before(rt,x);ask_after(rt,x);
			if(t1==-1){ans+=num[t2]-x;ans%=1000000;del(t2);}
			else if(t2==-1){ans+=x-num[t1];ans%=1000000;del(t1);}
			else
			{
				if(x-num[t1]>num[t2]-x)  {ans+=num[t2]-x;ans%=1000000;del(t2);}
				else{ans+=x-num[t1];ans%=1000000;del(t1);}
			}
		}
	}
	cout<<ans<<endl;
    return 0;
}
