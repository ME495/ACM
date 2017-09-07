/*
����n���㣬��m��ѯ��
1 x y ����һ���ڵ�
2 x y ѯ��������ڵ�����ĵ�
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 500010
const int inf=0x3f3f3f3f;
int D;//��ǰά
struct Point{
    //d[0/1]��ʾһά/��ά����
    //mn[0/1],mx[0/1]��ʾ��С�����һά/��ά����
    //l,r��ʾ����Ӻ��Ҷ���
    int d[2],mn[2],mx[2],l,r;
    bool operator==(const Point a)const
    {
        return d[0]==a.d[0]&&d[1]==a.d[1];
    }
    bool operator<(const Point a)const
    {
        return d[D]<a.d[D];
    }
}p[N];
struct KDtree{
    Point t[N*2],P,Q;
    int rt,cnt,ans;
    void updata(int k)
    {
        int l=t[k].l,r=t[k].r;
        for(int i=0;i<2;++i)
        {
            t[k].mn[i]=t[k].mx[i]=t[k].d[i];
            if(l) t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]);
            if(l) t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
            if(r) t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]);
            if(r) t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
        }
    }
    int build(int l,int r,int f)
    {
        if(l>r) return 0;
        int mid=l+r>>1;
        D=f;nth_element(p+l,p+mid,p+r+1);
        t[mid]=p[mid];
        t[mid].l=build(l,mid-1,f^1);
        t[mid].r=build(mid+1,r,f^1);
        updata(mid);
        return mid;
    }
    void insert(int &k,int f,Point &now)
    {
        if(!k)
        {
            k=++cnt;
            t[k].d[0]=t[k].mn[0]=t[k].mx[0]=now.d[0];
            t[k].d[1]=t[k].mn[1]=t[k].mx[1]=now.d[1];
            t[k].l=t[k].r=0;
        }
        if(t[k]==now) return;
        if(now.d[f]<t[k].d[f]) insert(t[k].l,f^1,now);
        else insert(t[k].r,f^1,now);
        updata(k);
    }
    int dis(Point &Q)
    {
        int d=0;
        for(int i=0;i<2;++i) d+=abs(Q.d[i]-P.d[i]);
        return d;
    }
    int getmn(Point &Q)//���Ƶ���С���ܶ��پ���
    {
        int mn=0;
        for(int i=0;i<2;++i)
        {
            mn+=max(0,P.d[i]-Q.mx[i]);
            mn+=max(0,Q.mn[i]-P.d[i]);
        }
        return mn;
    }
    int getmx(Point &Q)//���Ƶ������ܶ��پ���
    {
        int mx=0;
        for(int i=0;i<2;++i)
            mx+=max(abs(P.d[i]-Q.mn[i]),abs(P.d[i]-Q.mx[i]));
        return mx;
    }
    void querymn(int k)//������С�Ĺ��ܶ��پ���
    {
        //������ҵĵ㼯�а����Լ��������Լ�
        //int tmp=dis(t[k]);
        //if(tmp) ans=min(ans,tmp);
        ans=min(ans,dis(t[k]));
        int l=t[k].l,r=t[k].r,dl=inf,dr=inf;
        if(l) dl=getmn(t[l]);
        if(r) dr=getmn(t[r]);
        if(dl<dr)
        {
            if(dl<ans) querymn(l);
            if(dr<ans) querymn(r);
        }
        else
        {
            if(dr<ans) querymn(r);
            if(dl<ans) querymn(l);
        }
    }
    void querymx(int k)//�������Ĺ��ܶ��پ���
    {
        ans=max(ans,dis(t[k]));
        int l=t[k].l,r=t[k].r,dl=-inf,dr=-inf;
        if(l) dl=getmx(t[l]);
        if(r) dr=getmx(t[r]);
        if(dl>dr)
        {
            if(dl>ans) querymx(l);
            if(dr>ans) querymx(r);
        }
        else
        {
            if(dr>ans) querymx(r);
            if(dl>ans) querymx(l);
        }
    }
    /*
    f=0Ϊ�������,f=1Ϊ������С
    */
    int query(int f,int x,int y)
    {
        P.d[0]=x;P.d[1]=y;
        if(f==0) {ans=inf;querymn(rt);}
        else {ans=-inf;querymx(rt);}
        return ans;
    }
    /*
    ������Ľڵ�̫��ʱ�����ܵ�������ƽ�⣬��ʱ�ؽ�
    */
    int rebuild(int l,int r,int f)
    {
        if(l>r) return 0;
        int mid=l+r>>1;
        D=f;nth_element(t+l,t+mid,t+r+1);
        t[mid].l=rebuild(l,mid-1,f^1);
        t[mid].r=rebuild(mid+1,r,f^1);
        updata(mid);
        return mid;
    }
}T;
int n,m;
int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int main()
{
    //freopen("BZOJ2716.in","r",stdin);
    n=read();m=read();
    for(int i=1;i<=n;++i){p[i].d[0]=read();p[i].d[1]=read();}
    T.rt=T.build(1,n,0);T.cnt=n;
    int t,z=n+50000;Point tmp;
    for(int i=1;i<=m;++i)
    {
        t=read();tmp.d[0]=read();tmp.d[1]=read();
        if(t==1)
        {
            T.insert(T.rt,0,tmp);
            if(T.cnt==z){T.rt=T.rebuild(1,T.cnt,0);n+=50000;}
        }
        else printf("%d\n",T.query(0,tmp.d[0],tmp.d[1]));
    }
    return 0;
}
