#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
struct P {
	int x, y, id;
	bool operator < (const P& rhs) const {
		if(x != rhs.x) return x < rhs.x;
		return y > rhs.y;
	}
};
P a[maxn];
int n;
int lis[maxn];
int r[maxn];
int vis[maxn];
int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].id = i;
	}
	sort(a + 1, a + n + 1);
	vector<int> v(n);
	for(int i = 0; i < n; i++) v[i] = 1e9;
	int mx = 0;
	for(int i = 1; i <= n; i++) {
		int k = lower_bound(v.begin(), v.end(), a[i].y) - v.begin();
		v[k] = a[i].y;
		lis[i] = k + 1;
		mx = max(mx, lis[i]);
	}
//	for(int i = 1; i <= n; i++) printf("%d ", lis[i]); puts("");
	for(int i = 1; i <= mx; i++) r[i] = -1e9;
	r[mx + 1] = 1e9;
	vector<int> A, B;
	for(int i = n; i >= 1; i--) {
		if(a[i].y < r[lis[i] + 1]) {
			A.push_back(a[i].id);
			r[lis[i]] = max(r[lis[i]], a[i].y);
			if(vis[lis[i]]) vis[lis[i]] = -1;
			else vis[lis[i]] = a[i].id;
		}
	}
	for(int i = 1; i <= n; i++) 
		if(vis[i] != -1 && vis[i] != 0) B.push_back(vis[i]);
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	printf("%d ", (int)A.size());
	for(int x : A) printf("%d ", x); puts("");
	printf("%d ", (int)B.size());
	for(int x : B) printf("%d ", x); puts("");
	return 0;
}
