/*
ZOJ 1492
题意：求一个不超过50个点的图中最大完全子图（团）的大小。
题解：初始化的时候任意选择一个点u，然后将所有比u大且和u相连的点加入到集合st[1]，然后进行第一层dfs，在st[1]中选择一个点v，将st[1]中比v大的且和v相连的点都加入集合st[2]，再进行下一层dfs...最后终止的条件是这里某一层的st[x]集合为空集，此时说明这个团无法再增大了，此时更新最大值。当然仅仅是这样的思路肯定会超时的，这时候我们需要记忆化+剪枝。用dp[i]保存第i个点以后的点能得到的最大团的大小，免于重复计算。
有两个很重要的剪枝：
剪枝1：如果 U 集合中的点的数量+1（选择 ui 加入 U 集合中）+st[i] 中所有 ui 后面的点的数量 ≤ 当前最优值，就退出
剪枝2：如果 U 集合中的点的数量+1（理由同上）+[ui, n]这个区间中能构成的最大团的顶点数量 ≤ 当前最优值，就退出
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 105;

struct MaxClique {
	bool g[MAXN][MAXN];
	int n, dp[MAXN], st[MAXN][MAXN], ans;
	//	dp[i]表示第i个点之后能组成的最大团的大小，
	// 	st[i][j]表示算法中第i层dfs所需要的点的集合，保存有可能是最大团其中之一的点

	void init(int n) {
		this->n = n;
		memset(g, false, sizeof(g));
	}

	void addedge(int u, int v, int w) {
		g[u][v] = w;
	}

	bool dfs(int sz, int num) {
		if (sz == 0) {
			if (num > ans) {
				ans = num;
				return true;
			}
			return false;
		}
		for (int i = 0; i < sz; i++) {		// 在第num层的集合中枚举一个点i
			if (sz - i + num <= ans) return false;	// 剪枝1
			int u = st[num][i];
			if (dp[u] + num <= ans) return false;	// 剪枝2
			int cnt = 0;
			for (int j = i + 1; j < sz; j++) {	// 在第num层遍历在i之后的且与i所相连的点，并且加入第num+1层集合
				if (g[u][st[num][j]])
					st[num + 1][cnt++] = st[num][j];
			}
			if (dfs(cnt, num + 1)) return true;
		}
		return false;
	}

	int solver() {
		ans = 0;
		memset(dp, 0, sizeof(dp));
		for (int i = n; i >= 1; i--) {
			int cnt = 0;
			for (int j = i + 1; j <= n; j++) {	// 初始化第1层集合
				if (g[i][j]) st[1][cnt++] = j;
			}
			dfs(cnt, 1);
			dp[i] = ans;
		}
		return ans;
	}

}maxclique;

int main() {
	int n;
	while (scanf("%d", &n), n) {
		maxclique.init(n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int x;
				scanf("%d", &x);
				maxclique.addedge(i, j, x);
			}
		}
		printf("%d\n", maxclique.solver());
	}
	return 0;
}
