/*
��ģ��Ϊ��������Ҫ�ܶ�������
�ȳ�ʼ��tr[][],fa[],num[],size
*/
#include<iostream>
#include<cstdio>
using namespace std;
int n,size,rt,kind,t1,t2;//sz��¼�����˶��ٸ��ڵ�
long long ans;
/*
tr[x][0/1]��ʾ�ڵ�x����/�Ҷ��ӽڵ㣬
num[x]��ʾ�ڵ�x��ֵ��
fa[x]��ʾ�ڵ�x�ĸ��׽ڵ�
*/
int tr[80001][2],num[80001],fa[80001];
/*
��ת����
���ڵ�x����һ�㣬�ڵ�kΪ�ڵ�xΪҪ������������Ŀ�꣬
*/
void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l,r;
    if(tr[y][0]==x) l=0;
    else l=1;
    r=l^1;
    //���y�ڵ���k�ڵ㣬���ٽ�x����һ���x����k
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
��չ����
��x�ڵ�������k�ڵ����ڵ�λ��
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
                rotate(x,k);//֮����
			else
                rotate(y,k);//һ����
		}
		rotate(x,k);
	}
}
/*
�������
��ֵΪx�Ľڵ�������У�
kΪ��ǰ���ڽڵ㣬
lastΪ��һ���ڵ㣬Ҳ���Ǹ��ڵ�
*/
void ins(int &k,int x,int last)
{
	if(k==0)//�Ѿ��ҵ�ֵxӦ�ô��ڵ�λ��
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
ɾ������
���ڵ�x������ɾ����
�Ƚ��ڵ�x���������ڵ㣬
�ٰѸ��ڵ㣨x�ڵ㣩ɾ���������������ĸ�����Ϊ���ڵ㣬
Ȼ����������ӵ���������С�Ľڵ���
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
�ҵ���ֵxС�ĵ�һ��ֵ��������t1��
*/
void ask_before(int k,int x)
{
	if(k==0)return;
	if(num[k]<=x){t1=k;ask_before(tr[k][1],x);}
	else ask_before(tr[k][0],x);
}
/*
�ҵ���ֵx��ĵ�һ��ֵ��������t2��
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
