#include <stdio.h>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

#define F first
#define S second
#define PB push_back

constexpr int kN = int(3E3 + 10);

pair<int, int> p[kN];
int a[kN], val[kN];

int main() {
	vector<int> ans;
	set<int> s;
	int n, apos = 1, m , sz;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].F, &p[i].S);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) s.insert(a[i]);
	sort(p + 1, p + n + 1);
	sort(a + 1, a + m + 1);
	for (int i = 1; i <= n; i++) {
		val[i] = 0;
		if (apos > 1 && a[apos - 1] == p[i].F) val[i]++;
		while (apos <= m) {
			if (a[apos] <= p[i].S) {
				if (a[apos] >= p[i].F) val[i]++;
				apos++;
			}
			else break;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (val[i] == 0) {
			ans.PB(p[i].F + 1);
			if (i < n && p[i + 1].F == p[i].S && val[i + 1] < 2) {
				ans.PB(p[i].S);
				val[i + 1]++;
			}
			else ans.PB(p[i].S - 1);
		}
		else if (val[i] == 1) {
			if (s.find(p[i].S) != s.end()) ans.PB(p[i].S - 1);
			else if (i < n && p[i + 1].F == p[i].S && val[i + 1] < 2) {
				ans.PB(p[i].S);
				val[i + 1]++;
			}
			else {
				if (s.find(p[i].S - 1) != s.end()) ans.PB(p[i].S - 2);
				else ans.PB(p[i].S - 1);
			}
		}
		else if (val[i] > 2) {
			printf("impossible\n");
			return 0;
		}
	}


	sort(ans.begin(), ans.end());
	sz = int(ans.size());
	printf("%d\n", sz);
	if (sz) printf("%d", ans[0]);
	for (int i = 1; i < sz; i++) printf(" %d", ans[i]);
	printf("\n");
}
