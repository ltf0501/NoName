#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;
int a[maxn][maxn];
bool vis1[maxn], vis2[maxn];
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
	int q;
	scanf("%d", &q);
	vis1[1] = 1;
	while(q--) {
		memset(vis2, 0, sizeof(vis2));
		int x;
		scanf("%d", &x);
		for(int i = 1; i <= n; i++) if(vis1[i]) {
			for(int j = 1; j <= n; j++) if(a[i][j] == x)
				vis2[j] = 1;
		}
		memset(vis1, 0, sizeof(vis1));
		for(int i = 1; i <= n ; i++) vis1[i] = vis2[i];
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++) cnt += vis1[i];
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++)
		if(vis1[i]) printf("%d ", i);
	return 0;
}
