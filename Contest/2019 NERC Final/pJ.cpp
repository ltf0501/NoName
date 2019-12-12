bool debug = false;
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
 
#define PB push_back
 
const int kN = 2e6 + 10;
 
int cnt[kN]; 
bool went[kN];
 
int ok(int tot, int n) {
	if(tot % (n + 1) == 0) return tot / (n + 1);
	int num = tot / (n + 1) + 1;
	int res = num * (n + 1) - tot;	
	if(res > num) return -1;
	return num;
}
 
void solve() {
	vector<int> v;
	int n, tmp, sz, ans;	
	bool f;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &tmp);
		v.PB(tmp);
		cnt[tmp]++;
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	sz = int(v.size());
	went[v[0]] = true;
	for (int i = cnt[v[0]]; i >= 0; i--) {
		tmp = ok(cnt[v[0]], i);
 
		
		if (tmp == -1) continue;
		f = true;
		ans = tmp;
		
		for (int j = 0; j < sz; j++) if (!went[v[j]]) {
			went[v[j]] = true;
			if (debug) printf("ok(%d, %d) = %d\n", cnt[v[j]], i, ok(cnt[v[j]], i));
			
			tmp = ok(cnt[v[j]], i);
		
			if (tmp == -1) {
				while (j > 0) went[v[j--]] = false;
				went[v[0]] = true;
				f = false;
				break;
			}
			ans += tmp;
		}
		
		if (f) {
			if (debug) printf("i = %d\n", i);
			printf("%d\n", ans);
			break;
		}
	}
	
	for (int x : v) went[x] = false;
	for (int x : v) cnt[x] = 0;
	v.clear();
 
	return ;
}
int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
}
