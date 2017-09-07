#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 20010
struct Point{
    double x,y;
    Point(){}
    Point(double a,double b):x(a),y(b){}
    void f(double &a,double &b)
    {
        a=x;b=y;
    }
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    void output()
    {
        printf("%.1f %.1f\n",x,y);
    }
}b[N];
struct Line{
    Point s,t;
    double angle;
    Line(){}
    Line(Point a,Point b):s(a),t(b){}
    void get_angle()
    {
        angle=atan2(t.y-s.y,t.x-s.x);
    }
}a[N];
int n,m;
int que[N];
const double eps=1e-8;
int sig(double x)
{
    if(x>eps) return 1;
    if(x<-eps) return -1;
    return 0;
}
double cross(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
bool cmp(Line l1,Line l2)
{
    int t=sig(l1.angle-l2.angle);
    if(t>0) return true;
    else if(t<0) return false;
    else if(sig(cross(l1.s,l1.t,l2.s))>0) return true;
    else return false;
}
Point intersect(Line l1,Line l2)
{
    double x1,x2,x3,x4,y1,y2,y3,y4,d,dx,dy;
    l1.s.f(x1,y1);l1.t.f(x2,y2);
    l2.s.f(x3,y3);l2.t.f(x4,y4);
    d=(y2-y1)*(x3-x4)-(y4-y3)*(x1-x2);#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 20010
struct Point{
    double x,y;
    Point(){}
    Point(double a,double b):x(a),y(b){}
    void f(double &a,double &b)
    {
        a=x;b=y;
    }
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    void output()
    {
        printf("%.1f %.1f\n",x,y);
    }
}b[N];
struct Line{
    Point s,t;
    double angle;
    Line(){}
    Line(Point a,Point b):s(a),t(b){}
    void get_angle()
    {
        angle=atan2(t.y-s.y,t.x-s.x);
    }
}a[N];
int n,m;
int que[N];
const double eps=1e-8;
int sig(double x)
{
    if(x>eps) return 1;
    if(x<-eps) return -1;
    return 0;
}
double cross(Point p0,Point p1,Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}
bool cmp(Line l1,Line l2)
{
    int t=sig(l1.angle-l2.angle);
    if(t>0) return true;
    else if(t<0) return false;
    else if(sig(cross(l1.s,l1.t,l2.s))>0) return true;
    else return false;
}
Point intersect(Line l1,Line l2)
{
    double x1,x2,x3,x4,y1,y2,y3,y4,d,dx,dy;
    l1.s.f(x1,y1);l1.t.f(x2,y2);
    l2.s.f(x3,y3);l2.t.f(x4,y4);
    d=(y2-y1)*(x3-x4)-(y4-y3)*(x1-x2);
    dx=(x1*y2-x2*y1)*(x3-x4)-(x3*y4-x4*y3)*(x1-x2);
    dy=(y2-y1)*(x3*y4-x4*y3)-(y4-y3)*(x1*y2-x2*y1);
    return Point(dx/d,dy/d);
}
void solve(Line a[],int n)
{
    sort(a+1,a+n+1,cmp);
    int cnt=1;
    for(int i=2;i<=n;++i)
        if(sig(a[i].angle-a[i-1].angle)!=0)
            a[++cnt]=a[i];
    n=cnt;
    int head=1,tail=2;
    que[1]=1;que[2]=2;
    for(int i=3;i<=n;++i)
    {
        while(head<tail&&sig(cross(a[i].s,a[i].t,intersect(a[que[tail]],a[que[tail-1]])))>0) --tail;
        while(head<tail&&sig(cross(a[i].s,a[i].t,intersect(a[que[head]],a[que[head+1]])))>0) ++head;
        que[++tail]=i;
    }
    while(head<tail&&sig(cross(a[que[head]].s,a[que[head]].t,intersect(a[que[tail]],a[que[tail-1]])))>0) --tail;
    while(head<tail&&sig(cross(a[que[tail]].s,a[que[tail]].t,intersect(a[que[head]],a[que[head+1]])))>0) ++head;
    m=0;
    if(head==tail) return;
    que[tail+1]=que[head];
    for(int i=head;i<=tail;++i)
        b[++m]=intersect(a[que[i]],a[que[i+1]]);
}
double area(Point a[],int n)
{
    a[n+1]=a[1];
    double ans=0;
    for(int i=1;i<=n;++i)
        ans+=cross(a[1],a[i],a[i+1]);
    return -ans/2;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        a[1]=Line(Point(0,0),Point(0,10000));a[1].get_angle();
        a[2]=Line(Point(0,10000),Point(10000,10000));a[2].get_angle();
        a[3]=Line(Point(10000,10000),Point(10000,0));a[3].get_angle();
        a[4]=Line(Point(10000,0),Point(0,0));a[4].get_angle();
        for(int i=5;i<=n+4;++i)
        {
            a[i].t.input();a[i].s.input();a[i].get_angle();
        }
        solve(a,n+4);
        printf("%.1f\n",area(b,m)+eps);
    }
    return 0;
}

    dx=(x1*y2-x2*y1)*(x3-x4)-(x3*y4-x4*y3)*(x1-x2);
    dy=(y2-y1)*(x3*y4-x4*y3)-(y4-y3)*(x1*y2-x2*y1);
    return Point(dx/d,dy/d);
}
void solve(Line a[],int n)
{
    sort(a+1,a+n+1,cmp);
    int cnt=1;
    for(int i=2;i<=n;++i)
        if(sig(a[i].angle-a[i-1].angle)!=0)
            a[++cnt]=a[i];
    n=cnt;
    int head=1,tail=2;
    que[1]=1;que[2]=2;
    for(int i=3;i<=n;++i)
    {
        while(head<tail&&sig(cross(a[i].s,a[i].t,intersect(a[que[tail]],a[que[tail-1]])))>0) --tail;
        while(head<tail&&sig(cross(a[i].s,a[i].t,intersect(a[que[head]],a[que[head+1]])))>0) ++head;
        que[++tail]=i;
    }
    while(head<tail&&sig(cross(a[que[head]].s,a[que[head]].t,intersect(a[que[tail]],a[que[tail-1]])))>0) --tail;
    while(head<tail&&sig(cross(a[que[tail]].s,a[que[tail]].t,intersect(a[que[head]],a[que[head+1]])))>0) ++head;
    m=0;
    if(head==tail) return;
    que[tail+1]=que[head];
    for(int i=head;i<=tail;++i)
        b[++m]=intersect(a[que[i]],a[que[i+1]]);
}
double area(Point a[],int n)
{
    a[n+1]=a[1];
    double ans=0;
    for(int i=1;i<=n;++i)
        ans+=cross(a[1],a[i],a[i+1]);
    return -ans/2;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        a[1]=Line(Point(0,0),Point(0,10000));a[1].get_angle();
        a[2]=Line(Point(0,10000),Point(10000,10000));a[2].get_angle();
        a[3]=Line(Point(10000,10000),Point(10000,0));a[3].get_angle();
        a[4]=Line(Point(10000,0),Point(0,0));a[4].get_angle();
        for(int i=5;i<=n+4;++i)
        {
            a[i].t.input();a[i].s.input();a[i].get_angle();
        }
        solve(a,n+4);
        printf("%.1f\n",area(b,m)+eps);
    }
    return 0;
}
