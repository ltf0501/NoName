#include <stdio.h>
#include <stack>
#include <utility>
using namespace std;
#define F first
#define S second
typedef long long int ll;
constexpr int kN = int(1E5 + 10);

int x[kN], y[kN];
double pos[kN];

pair<ll, ll> Merge(pair<ll, ll> a, pair<ll, ll> b) {return {a.F + b.F, a.S + b.S};}

int main() {
	int n, cnt;
	double ans = 0;
	pair<ll, ll> cur;
	stack<pair<ll, ll>> st;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	for (int o = 1; o <= 2; o++) {
		for (int i = 1; i <= n; i++) {
			cur = {x[i], 1};
			while (!st.empty()) {
				if (st.top().F * cur.S >= cur.F * st.top().S) {
					cur = Merge(st.top(), cur);
					st.pop();
				}
				else break;
			}
			//printf("i = %d, cur = (%lld, %lld)\n", i, cur.F, cur.S);
			st.push(cur);
		}
		cur = {0, 0};
		cnt = 0;
		for (int i = n; i >= 1; i--) {
			if (cnt == 0) {
				cur = st.top();
				cnt = cur.S;
				st.pop();
			}
			pos[i] = double(cur.F) / cur.S;
			cnt--;
		}
		for (int i = 1; i <= n; i++) ans += (pos[i] - x[i]) * (pos[i] - x[i]);
		//for (int i = 1; i <= n; i++) //printf("pos[%d] = %.20lf\n", i, pos[i]);
		for (int i = 1; i <= n; i++) swap(x[i], y[i]);
	}
	printf("%.20lf\n", ans);
} 
