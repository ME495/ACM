/*
POJ 2989
题意：给出n个人，其中m对朋友，求极大团数量（若超过1000则输出“Too many maximal sets of friends.”）。
算法：Bron-Kerbosch算法(DFS)
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
const int N = 130;
int Ans, G[N][N], all[N][N], some[N][N], none[N][N];

void DFS(int n, int an, int sn, int nn){
	if(!sn && !nn) Ans++;
	if(Ans > 1000) return;
	int key = some[n][1];
	for(int j=1;j<=sn;++j){
		int v = some[n][j], tsn = 0, tnn = 0;
		if(G[key][v])continue;
		for(int i=1;i<=an;++i)
            all[n+1][i] = all[n][i];
        all[n+1][an+1] = v;
        for(int i=1;i<=sn;++i)
            if(G[v][some[n][i]])
                some[n+1][++tsn] = some[n][i];
        for(int i=1;i<=nn;++i)
            if(G[v][none[n][i]])
                none[n+1][++tnn] = none[n][i];
		DFS(n + 1, an + 1, tsn, tnn);
		some[n][j] = 0;
		none[n][++nn] = v;
	}
}

int main(){
	int n, m;
	while(scanf("%d%d", &n, &m) == 2){
		int x, y;
		memset(G,0,sizeof(G));
		Ans = 0;
		for(int i=1;i<=m;++i){
			scanf("%d%d", &x, &y);
			G[x][y] = G[y][x] = 1;
		}
		for(int i=1;i<=n;++i) some[1][i] = i;
		DFS(1, 0, n, 0);
		if(Ans > 1000) puts("Too many maximal sets of friends.");
		else printf("%d\n", Ans);
	}
	return 0;
}
