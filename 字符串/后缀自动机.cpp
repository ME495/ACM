#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1000010
typedef long long ll;
struct sam
{
    int mx[N*2],fa[N*2],a[N*2][26];
	int last,cnt;
	void init(){
		memset(mx,0,sizeof(mx));
		memset(fa,0,sizeof(fa));
		memset(a,0,sizeof(a));
		last=cnt=1;
	}
	void extend(int c){
		int p=last,np=last=++cnt;mx[np]=mx[p]+1;
		while(!a[p][c]&&p)a[p][c]=np,p=fa[p];
		if(!p)fa[np]=1;
		else
		{
			int q=a[p][c];
			if(mx[p]+1==mx[q])fa[np]=q;
			else
			{
				int nq=++cnt;mx[nq]=mx[p]+1;
			    memcpy(a[nq],a[q],sizeof(a[q]));
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				while(a[p][c]==q)a[p][c]=nq,p=fa[p];
			}
		}
	}
}sam;
char st[N];
int main()
{
    sam.init();
    scanf("%s",st);
    int n=strlen(st);
    for(int i=0;i<n;++i)
        sam.extend(st[i]-'a');
    ll ans=0;
    for(int i=1;i<=sam.cnt;++i)
        if(sam.fa[i]) ans+=sam.mx[i]-sam.mx[sam.fa[i]];
    printf("%lld\n",ans);
}
