#include <cstdio>
#include <algorithm>
using namespace std;
typedef struct avl_node{
    int data,h;
    struct avl_node *l,*r;
}avl_t,*avl_p;
int height(avl_p root)
{
    if(root==NULL) return 0;
    else return root->h;
}
int cal_height(avl_p root)
{
    return max(height(root->l),height(root->r))+1;
}
avl_p single_rotate_l(avl_p k2)
{
    avl_p k1=k2->l;
    k2->l=k1->r;
    k1->r=k2;
    k1->h=cal_height(k1);
    k2->h=cal_height(k2);
    return k1;
}
avl_p single_rotate_r(avl_p k2)
{
    avl_p k1=k2->r;
    k2->r=k1->l;
    k1->l=k2;
    k1->h=cal_height(k1);
    k2->h=cal_height(k2);
    return k1;
}
avl_p double_rotate_l(avl_p k3)
{
    k3->l=single_rotate_r(k3->l);
    return single_rotate_l(k3);
}
avl_p double_rotate_r(avl_p k3)
{
    k3->r=single_rotate_l(k3->r);
    return single_rotate_r(k3);
}
avl_p insert_avl(int x,avl_p root)
{
    if(root==NULL)
    {
        root=(avl_p)malloc(sizeof(avl_t));
        root->data=x;root->h=1;
        root->l=root->r=NULL;
    }
    else if(x<root->data)
    {
        root->l=insert_avl(x,root->l);
        if(height(root->l)-height(root->r)>1)
            if(x<root->l->data)
                root=single_rotate_l(root);
            else root=double_rotate_l(root);
    }
    else if(x>root->data)
    {
        root->r=insert_avl(x,root->r);
        if(height(root->r)-height(root->l)>1)
            if(x>root->r->data)
                root=single_rotate_r(root);
            else root=double_rotate_r(root);
    }
    root->h=max(height(root->l),height(root->r))+1;
    return root;
}
avl_p delete_avl(int x,avl_p root)
{
    if(!root) return NULL;
    if(x<root->data)
    {
        root->l=delete_avl(x,root->l);
        if(height(root->r)-height(root->l)>1)
            if(root->r->l!=NULL&&height(root->r->l)>height(root->r->r))
                root=double_rotate_r(root);
            else root=single_rotate_r(root);
    }
    else if(x>root->data)
    {
        root->r=delete_avl(x,root->r);
        if(height(root->r)-height(root->l)>1)
            if(root->l->r!=NULL&&height(root->l->r)>height(root->l->l))
                double_rotate_l(root);
            else single_rotate_l(root);
    }
    else
    {
        avl_p p=root,p1;
        if(p->l&&p->r)
        {
            p1=p->r;
            while(p1->l) p1=p1->l;
            p->data=p1->data;
            p1->data=x;
            root=delete_avl(x,root->r);
            if(height(root->r)-height(root->l)>1)
                if(root->l->r!=NULL&&height(root->l->r)>height(root->l->l))
                    double_rotate_l(root);
                else single_rotate_l(root);
        }
        else if(p->l)
        {
            root=p->l;
            free(p);
        }
        else if(p->r)
        {
            root=p->r;
            free(p);
        }
    }
    root->h=cal_height(root);
    return root;
}
avl_p find_avl(int x,avl_p root)
{
    if(root==NULL) return NULL;
    if(x==root->data) return root;
    else if(x<root->data) return find_avl(x,root->l);
    else if(x>root->data) return find_avl(x,root->r);
}
int main()
{
    freopen("1.txt","r",stdin);
    avl_p root=NULL,p;
    int n,x;
    char ch;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        getchar();
        ch=getchar();
        printf("%c\n",ch);
        scanf("%d",&x);
        if(ch=='i') root=insert_avl(x,root);
        else if(ch=='d') root=delete_avl(x,root);
        else if(ch=='f')
        {
            p=find_avl(x,root);
            if(p) printf("Find %d\n",x);
            else printf("No find\n");
        }
    }
    return 0;
}
