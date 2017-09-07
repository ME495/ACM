#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 1000010

struct node {
    int l, r, dis;
    int val;
} tree[N];
int g[110];
//�ϲ��������ϲ�������ƫ��, (x, y):��ƫ����ţ��������ƫ�����
int Merge(int x, int y) {
    if(!x) return y;
    if(!y) return x;
    if(tree[x].val < tree[y].val) swap(x, y);  // ���
    tree[x].r = Merge(tree[x].r, y);
    if(tree[tree[x].l].dis < tree[tree[x].r].dis)
        swap(tree[x].l, tree[x].r);
    if(tree[x].r) tree[x].dis = tree[tree[x].r].dis + 1;
    else tree[x].dis = 0;
    return x;
}
//ɾ��������ɾ�����Ϊ x ����ƫ���ĶѶ��������µĶѶ����
int Pop(int x) {
    int l = tree[x].l;
    int r = tree[x].r;
    tree[x].l = tree[x].r = tree[x].dis = 0;
    return Merge(l, r);
}
//��Ҫע����ǽ����ڵ�ʱ��ÿ����ƫ���ı����ҪΨһ��
