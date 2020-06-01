#include <stdio.h>
#include <stack>
#include <set>
#include <utility>
using namespace std;
#define F first
#define S second

constexpr int kN = int(2E5 + 10);

int a[kN], b[kN], ans[kN];
int ABS(int n) {return n >= 0 ? n : -n;}

int main() {
	stack<int> st;
	set<pair<int, int>> s;
	set<pair<int, int>>::iterator u;	
	int n, now = 0, p;
	long long int tot = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) s.insert({b[i], i});
	auto nearest = [&](int pos) {
		set<pair<int, int>>::iterator tl, tr;
		tr = s.lower_bound({pos, 0});
//		printf("pos = %d\n", pos);
		if (tr == s.begin()) return tr;
		else if (tr == s.end()) return prev(tr);
		else {
			tl = prev(tr);
//			printf("tl = (%d, %d), tr = (%d, %d)\n", tl->F, tl->S, tr->F, tr->S);
			if (ABS(pos - tl->F) > ABS(pos - tr->F)) return tr;
			else return tl;
		}
	};
	for (int i = 1; i <= n; i++) tot += ABS(a[i] - b[i]);
	for (int i = 1; i <= n; i++) {
		st.push(i);
		while (!st.empty()) {
			p = st.top();
			u = nearest(a[p]);
//			printf("i = %d, p = %d, u = %d\n", i, p, u->S);
			if (p == u->S) {
				ans[++now] = p;
				st.pop();
				s.erase(u);
			}
			else break;
		}
	}

	printf("%lld\n%d", tot, ans[1]);
	for (int i = 2; i <= n; i++) printf(" %d", ans[i]);
	printf("\n");
}
