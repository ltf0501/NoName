#include <bits/stdc++.h>
using namespace std;
const int kC = 1e7 + 10; 
const double eps = 1e-9;
const int V = 9000000;

double val[kC];
double v[kC];
int dp[kC], pre[kC];
int x[kC], idx[kC];
int main() {
	int n; scanf("%d", &n);
	int pos = 0;
	for(int i = 1;; i++) {
		double a = sin(i);
		if(a > -eps) val[++pos] = a, x[pos] = i;
		if(pos == V)break; 
	}
	//pos = 10;
	//for(int i = 1; i <= pos; i++) cin >> val[i];
	for(int i = 1; i <= pos; i++) v[i] = 100;
	for(int i = 1; i <= pos; i++) {
		//if(i % 1000 == 0) printf("i = %d\n", i);
		int k = lower_bound(v + 1, v + pos + 1, val[i]) - v;
		dp[i] = k;
		v[k] = val[i];
		idx[k] = i;
		pre[i] = idx[k - 1];
	}
	//for(int i = 1; i <= pos; i++) printf("%d ", dp[i]); puts("");
	
	int mx = 0, now = 0;
	for(int i = 1; i <= pos; i++) {
		if(mx < dp[i]) mx = dp[i], now = i;
	}
	//printf("mx = %d, now = %d\n", mx, now);

	vector<int> v;
	while(now) {
		v.push_back(now);
		now = pre[now];
	}
	vector<int> ans;
	for(int s : v) ans.push_back(-x[s]);
	ans.push_back(0);
	reverse(v.begin(), v.end());
	for(int s : v) ans.push_back(x[s]);
	//for(int s : v) printf("%d %.6f\n", x[s], sin(x[s]));
	for(int i = 0; i < int(ans.size()) - 1; i++)
		assert(sin(ans[i]) < sin(ans[i + 1]));

	for(int i = 0; i < n; i++) printf("%d\n", ans[i]);
	return 0;
} 
