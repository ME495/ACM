#include <stdio.h>
#include <stdlib.h>
typedef int data_type;
typedef struct bst_node{
    data_type data;
    int num;
    struct bst_node *l,*r;
}bst_t,*bst_p;
bst_p find_bst(data_type x,bst_p root)
{
    if(root==NULL) return NULL;
    if(x<root->data)
        return find_bst(x,root->l);
    if(x>root->data)
        return find_bst(x,root->r);
    return root;
}
bst_p insert_bst(data_type x,int num,bst_p root)
{
    if(root==NULL)
    {
        root=malloc(sizeof(bst_t));
        root->data=x;
        root->num=num;
        root->l=root->r=NULL;
    }
    else if(x<root->data)
        root->l=insert_bst(x,num,root->l);
    else if(x>root->data)
        root->r=insert_bst(x,num,root->r);
    return root;
}
bst_p delete_bst(data_type x,bst_p root)
{
    bst_p p=root,p1,parent;
    if(!p) return NULL;
    if(p->data==x)
    {
        if(!p->l&&!p->r)
        {
            p=NULL;
            free(p);
        }
        else if(!p->r)
        {
            root=p->l;
            free(p);
        }
        else
        {
            p1=p->r;
            if(!p1->l) p1->l=p->l;
            else
            {
                while(p1->l)
                {
                    parent=p1;
                    p1=p1->l;
                }
                parent->l=p1->r;
                p1->l=p->l;p1->r=p->r;
            }
            root=p1;
            free(p);
        }
    }
    else if(x<p->data)
        root=delete_bst(x,p->l);
    else if(x>p->data)
        root=delete_bst(x,p->r);
    return root;
}
void mid_visit(bst_p root)
{
    if(root)
    {
        mid_visit(root->l);
        printf("%d %d\n",root->data,root->num);
        mid_visit(root->r);
    }
}
int main()
{
    int n,x,m;
    char ch;
    bst_p root=NULL,p;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&x);
        root=insert_bst(x,i,root);
    }
    scanf("%d",&m);
    while(m--)
    {
        getchar();
        ch=getchar();
        scanf("%d",&x);
        if(ch=='d') root=delete_bst(x,root);
        else if(ch=='i') root=insert_bst(x,++n,root);
        else if(ch=='f')
        {
            p=find_bst(x,root);
            if(p) printf("%d\n",p->num);
            else printf("No find!\n");
        }
    }
    mid_visit(root);
    return 0;
}
