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
//合并操作：合并两棵左偏树, (x, y):左偏树编号，输出新左偏树编号
int Merge(int x, int y) {
    if(!x) return y;
    if(!y) return x;
    if(tree[x].val < tree[y].val) swap(x, y);  // 大堆
    tree[x].r = Merge(tree[x].r, y);
    if(tree[tree[x].l].dis < tree[tree[x].r].dis)
        swap(tree[x].l, tree[x].r);
    if(tree[x].r) tree[x].dis = tree[tree[x].r].dis + 1;
    else tree[x].dis = 0;
    return x;
}
//删除操作：删除编号为 x 的左偏树的堆顶，返回新的堆顶编号
int Pop(int x) {
    int l = tree[x].l;
    int r = tree[x].r;
    tree[x].l = tree[x].r = tree[x].dis = 0;
    return Merge(l, r);
}
//需要注意的是建立节点时，每棵左偏树的编号需要唯一。
