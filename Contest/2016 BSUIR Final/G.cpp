#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


bool check(const vector<int> &v) {
	int n = v.size();
	ll now = 0;
	for(int i = n - 1; i >= 0; i--) {
		now = (now * 10 + v[i]) & ((1LL << n) - 1);
	}
	return now == 0;
}
int main() {
	int n; scanf("%d", &n);
	vector<int> ans;
	for(int i = 0; i < n; i++) {
		ans.push_back(1);
		if(check(ans)) continue;
		else {
			ans.pop_back();
			ans.push_back(2);
		}
	}
	assert(check(ans));
	reverse(ans.begin(), ans.end());
	for(int x : ans) printf("%d", x); puts("");
	return 0;
}
