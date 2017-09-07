#include<cstdio>
#include<cstring>
int f[1005],a[1005],b[1005],i,j,t,n1,n2,maxx;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n1);
        for(i=1;i<=n1;i++) scanf("%d",&a[i]);
        scanf("%d",&n2);
        for(i=1;i<=n2;i++) scanf("%d",&b[i]);
        memset(f,0,sizeof(f));
        for(i=1;i<=n1;i++)
        {
            maxx=0;
            for(j=1;j<=n2;j++)
            {
                if (a[i]>b[j]&&maxx<f[j]) maxx=f[j];
                if (a[i]==b[j]) f[j]=maxx+1;
            }
        }
        maxx=0;
        for(i=1;i<=n2;i++) if (maxx<f[i]) maxx=f[i];
        printf("%d\n",maxx);
    }
}
