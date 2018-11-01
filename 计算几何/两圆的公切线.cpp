#include<bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(int i=a;i<b;i++)
#define per(i,a,b) for(int i=b-1;i>=a;i--)
 
const double eps=1e-9;
const double pi=acos(-1.0);
class Point;
typedef Point Vec;
//三态函数比较;精度问题
int dcmp(double x){
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}
struct Point{
    double x,y;
    Point(double _x=0,double _y=0):x(_x),y(_y){}
    //向量与常数 注意常数要放在后面
    Vec operator*(double p) {return Vec(x*p,y*p);}
    Vec operator/(double p) {return Vec(x/p,y/p);}
    Vec operator-(Vec obj)  {return Vec(x-obj.x,y-obj.y);}
    Vec operator+(Vec obj)  {return Vec(x+obj.x,y+obj.y);}
    //点积
    double operator*(Vec obj) {return x*obj.x+y*obj.y;}
    //叉积
    double operator^(Vec obj) {return x*obj.y-y*obj.x;}
    //两个向量的夹角 A*B=|A|*|B|*cos(th)
    double Angle(Vec B)  {return acos((*this)*B/(*this).len()/B.len());}
    //两条向量平行四边形的面积
    double Area(Vec B)   {return fabs((*this)^B);}
    //向量旋转
    //旋转公式
    //  Nx     (cos  -sin) x
    //  Ny     (sin   cos) y
    Vec Rotate(double rad)  {return Vec(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));}
    //返回向量的法向量，即旋转pi/2
    Vec Normal()  {return Vec(-y,x);}
    //返回向量的长度,或者点距离原点的距离
    double len()  {return hypot(x,y);}
    double len2() {return x*x+y*y;}
    //返回两点之间的距离
    double dis(Point obj)   {return hypot(x-obj.x,y-obj.y);} //hypot 给定直角三角形的两条直角边，返回斜边边长
    //向量的极角 atan2(y,x)
     bool operator==(Point obj) {return dcmp(x-obj.x)==0&&dcmp(y-obj.y)==0;}
     bool operator<(Point obj)  {return x<obj.x||(x==obj.x&&y<obj.y);}
};
 
struct Circle{
    Point c; double r;
    Circle(Point c,double r):c(c),r(r){}
    Point getpoint(double a){return Point(c.x+cos(a)*r,c.y+sin(a)*r);}
};
/*
求圆的公切线
*/
int getTan(Circle A,Circle B,Point*  va,Point* vb){
    int cnt=0;
    if(A.r<B.r){swap(A,B);swap(va,vb);}
    double d=(A.c-B.c).len();
    double rdif=A.r-B.r,rsum=A.r+B.r;
    //内含，没有公切线
    if(dcmp(d-rdif)<0)return 0;
    //内切，有一条公切线
    double base=atan2(B.c.y-A.c.y,B.c.x-A.c.x);
    if(dcmp(d)==0&&dcmp(A.r-B.r)==0)return -1;
    if(dcmp(d-rdif)==0){
        va[cnt]=A.getpoint(base);vb[cnt]=B.getpoint(base);cnt++;
        return cnt;
    }
    //一定有两条外公切线
    double th=acos((A.r-B.r)/d);
    va[cnt]=A.getpoint(base+th);vb[cnt]=B.getpoint(base+th);cnt++;
    va[cnt]=A.getpoint(base-th);vb[cnt]=B.getpoint(base-th);cnt++;
    //可能有一条公切线
    if(dcmp(d-rsum)==0){
        va[cnt]=A.getpoint(base);vb[cnt]=B.getpoint(base+pi);cnt++;
    }
    else if(dcmp(d-rsum)>0){
        double th2=acos((A.r+B.r)/d);
        va[cnt]=A.getpoint(base+th2);vb[cnt]=B.getpoint(base+th2+pi);cnt++;
        va[cnt]=A.getpoint(base-th2);vb[cnt]=B.getpoint(base-th2+pi);cnt++;
    }
    return cnt;
}
 
/*
1.精度  要学着用dcmp
2.引用  不能交换两个引用swap（）,引用中间不能变
*/
 
Point va[10],vb[10];
struct Line{
    Point A,B;
    double l;
    bool operator<(const Line& b)const{
        if(dcmp(A.x-b.A.x)==0)return A.y<b.A.y;
        return A.x<b.A.x;
    }
}L[10];
 
int main(){
    double x1,y1,r1;double x2,y2,r2;
    while(scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&r1,&x2,&y2,&r2)==6){
         if(!dcmp(x1)&&!dcmp(y1)&&!dcmp(r1)&&!dcmp(x2)&&!dcmp(y2)&&!dcmp(r2))break;
         Point A=Point(x1,y1),B=Point(x2,y2);
         Circle AA=Circle(A,r1),BB=Circle(B,r2);
         int num=getTan(AA,BB,va,vb);
         rep(i,0,num){L[i].A=va[i],L[i].B=vb[i];L[i].l=va[i].dis(vb[i]);}
        // printf("sa:%d sb:%d\n",va.size(),vb.size());
         //rep(i,0,num) printf("%f %f %f %f\n",va[i].x,va[i].y,vb[i].x,vb[i].y);
         printf("%d\n",num);
         if(num==-1||num==0)continue;
         sort(L,L+num);
         rep(i,0,num)  printf("%.5f %.5f %.5f %.5f %.5f\n",L[i].A.x,L[i].A.y,L[i].B.x,L[i].B.y,L[i].l);
    }
    return 0;
}
