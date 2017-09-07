#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int c[50011],n;
int lowbit(int x)//计算lowbit
{
    return x&(-x);
}
void add(int i,int val)//将第i个元素加val
{
    while(i<=n)
    {
        c[i]+=val;
        i+=lowbit(i);
    }
}
int sum(int i)//求前i项和
{
    int s=0;
    while(i>0)
    {
        s+=c[i];
        i-=lowbit(i);
    }
    return s;
}
int main()
{
int i ,j=0,a,b,v,t,num;
char str[]="Add",str1[]="Sub",str2[]="End",sub1[6];

scanf("%d",&t);
while(t--)
{  
    scanf("%d",&n);
     printf("Case %d:\n",++j);
    memset(c,0,sizeof(c));
   for(i=1;i<=n;++i)   
        {        
         scanf("%d",&v);       
         add(i,v);   
        }
   while(1)
   {  
   scanf("%s",sub1);
   if(!strcmp(str2,sub1))
   break;
if(!strcmp(sub1,str))
{
scanf("%d %d",&a,&b);
add(a,b);
}
else if(!strcmp(sub1,str1))
{
scanf("%d %d",&a,&b);
add(a,-b);
}
else {
scanf("%d %d",&a,&b);
printf("%d\n",sum(b)-sum(a-1));
}
}
}
return 0;
}