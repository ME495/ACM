#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define N 1000010
struct node{
    node *next[26];
    node *fail;
    int sum;
};
char st[N];
int n;
node* new_node()
{
    node *p=(node*)malloc(sizeof(node));
    memset(p,0,sizeof(node));
    return p;
}
void Insert(char s[],node *root)
{
    node *p=root;
    for(int i=0;s[i];++i)
    {
        int x=s[i]-'a';
        if(p->next[x]==NULL)
        {
            node *pp=new_node();
            memset(pp,0,sizeof(node));
            p->next[x]=pp;
        }
        p=p->next[x];
    }
    ++p->sum;
}
void build_fial_pointer(node *root)
{
    queue<node*> que;
    que.push(root);
    node *tmp;
    while(!que.empty())
    {
        tmp=que.front();que.pop();
        for(int i=0;i<26;++i)
        {
            if(tmp->next[i])
            {
                if(tmp==root) tmp->next[i]->fail=root;
                else
                {
                    node *p=tmp->fail;
                    while(p)
                    {
                        if(p->next[i])
                        {
                            tmp->next[i]->fail=p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(p==NULL) tmp->next[i]->fail=root;
                }
                que.push(tmp->next[i]);
            }
        }
    }
}
int ac_automation(char s[],node *root)
{
    node *p=root;
    int cnt=0;
    for(int i=0;s[i];++i)
    {
        int x=st[i]-'a';
        while(!p->next[x]&&p!=root)
        {
            p=p->fail;
        }
        p=p->next[x];
        if(!p) p=root;
        node *tmp=p;
        while(tmp!=root)
        {
            if(tmp->sum>=0)
            {
                cnt+=tmp->sum;
                tmp->sum=-1;
            }
            else break;
            tmp=tmp->fail;
        }
    }
    return cnt;
}
void destroy_tree(node *p)
{
    for(int i=0;i<26;++i)
        if(p->next[i]) destroy_tree(p->next[i]);
    free(p);
}
int main()
{
    int ca;
    scanf("%d",&ca);
    while(ca--)
    {
        node *root=new_node();
        scanf("%d",&n);
        for(int i=0;i<n;++i)
        {
            scanf("%s",st);
            Insert(st,root);
        }
        build_fial_pointer(root);
        scanf("%s",st);
        printf("%d\n",ac_automation(st,root));
        destroy_tree(root);
    }
    return 0;
}
