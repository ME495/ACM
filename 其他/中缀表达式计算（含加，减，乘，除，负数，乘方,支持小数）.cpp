#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#define N 1000
char st[N];
int slove(char *st,double *ans)
{
    double stai[N];
    char stac[N],stt[N];
    int ti,tc,i,l,ll;
    double x;
    l=strlen(st);
    ti=tc=ll=0;
    stt[0]='\0';
    for(i=0;i<l;++i)
    {
        if(('0'<=st[i]&&st[i]<='9')||st[i]=='.')
        {
            stt[ll++]=st[i];stt[ll]='\0';
        }
        else
        {
            if(stt[0]!='\0')
            {
                //puts(stt);
                x=atof(stt);stt[ll=0]='\0';
                stai[++ti]=x;
                //printf("%f\n",x);
            }
            if(st[i]=='+'||st[i]=='-')
            {
                if(st[i]=='-'&&(i==0||st[i-1]<'0'||st[i-1]>'9')){stt[ll++]='-';stt[ll]='\0';}
                else
                {
                    while(tc&&stac[tc]!='(')
                    {
                        if(ti>1)
                        {
                            switch(stac[tc--])
                            {
                                case '+':stai[ti-1]+=stai[ti];break;
                                case '-':stai[ti-1]-=stai[ti];break;
                                case '*':stai[ti-1]*=stai[ti];break;
                                case '/':stai[ti-1]/=stai[ti];break;
                                case '^':stai[ti-1]=pow(stai[ti-1],stai[ti]);break;
                            }
                            --ti;
                        }
                        else return 1;
                    }
                    stac[++tc]=st[i];
                }
            }
            else if(st[i]=='*'||st[i]=='/')
            {
                while(tc&&stac[tc]=='*'||stac[tc]=='/'||stac[tc]=='^')
                {
                    if(ti>1)
                    {
                        switch(stac[tc--])
                        {
                            case '*':stai[ti-1]*=stai[ti];break;
                            case '/':stai[ti-1]/=stai[ti];break;
                            case '^':stai[ti-1]=pow(stai[ti-1],stai[ti]);break;
                        }
                        --ti;
                    }
                    else return 2;
                }
                stac[++tc]=st[i];
            }
            else if(st[i]=='^'||st[i]=='(') stac[++tc]=st[i];
            else if(st[i]==')')
            {
                while(stac[tc]!='(')
                {
                    if(tc==0) return 3;
                    if(ti>1)
                    {
                        switch(stac[tc--])
                        {
                            case '+':stai[ti-1]+=stai[ti];break;
                            case '-':stai[ti-1]-=stai[ti];break;
                            case '*':stai[ti-1]*=stai[ti];break;
                            case '/':stai[ti-1]/=stai[ti];break;
                            case '^':stai[ti-1]=pow(stai[ti-1],stai[ti]);break;
                        }
                        --ti;
                    }
                    else return 4;
                }
                --tc;
            }
            else return 5;
        }
    }
    if(stt[0]!='\0') stai[++ti]=atof(stt);
    //puts(stt);
    //printf("%f %d %d %c\n",stai[ti],ti,tc,stac[tc]);
    while(tc)
    {
        if(ti>1)
        {
            switch(stac[tc--])
            {
                case '+':stai[ti-1]+=stai[ti];break;
                case '-':stai[ti-1]-=stai[ti];break;
                case '*':stai[ti-1]*=stai[ti];break;
                case '/':stai[ti-1]/=stai[ti];break;
                case '^':stai[ti-1]=pow(stai[ti-1],stai[ti]);break;
                default:return 6;
            }
            --ti;
        }
        else return 7;
    }
    if(ti==1){*ans=stai[1];return 0;}
    else return 8;
}
int main()
{
    double ans;
    gets(st);
    //puts(st);
    int k=slove(st,&ans);
    if(k==0) printf("%g\n",ans);
    else printf("error %d\n",k);
    return 0;
}
