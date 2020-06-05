#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
typedef long long int ll;
constexpr int kN = int(5E5 + 10);

int ABS(int n) {return n >= 0 ? n : -n;}

int s[kN], nxt[kN], p[kN];
bool used[kN];

int Find(int n) {return n == p[n] ? n : p[n] = Find(p[n]);}

void Merge(int l, int r) {
	l = Find(l), r = Find(r);
	p[r] = l;
	nxt[l] = nxt[r];
	return ;
}

int main() {
	int n, discard = 0, lst = 0;
	vector<pair<int, int>> v;
	ll c, r, ans;
	scanf("%d%lld%lld", &n, &c, &r);
	for (int i = 1; i <= n; i++) scanf("%d", &s[i]);
	if (n == 1) {
		if (s[1] == 0) printf("%lld\n", min(c, r));
		else printf("0\n");
		return 0;
	}
	for (int i = 1; i <= n; i++) p[i] = i, nxt[i] = i + 1;
	for (int i = 1; i <= n; i++) if (s[i] != 0) {
		if (lst == 0) lst = s[i];
		else if ((lst > 0) != (s[i] > 0)) lst = s[i];
		else discard++;
	}
	else discard++;

	ans = discard * r;
	
	for (int i = 1; i <= n; i++) if (s[i] < 0) s[i]--;
	else s[i]++;

	discard = lst = 0;
	for (int i = 1; i <= n; i++) {
		if (lst == 0) lst = s[i];
		else if ((lst > 0) != (s[i] > 0)) lst = s[i];
		else discard++;
	}
	function<void(int)> remove = [&](int x) {
		function<int(int, int, bool)> cal = [&](int l, int r, bool target) {
			if (l == 1 && r == n) return n - 1;
			else if (l == 1) {
				if (target != (s[r + 1] > 0)) return r - l;
				else return r - l + 1;
			}
			else if (r == n) {
				if ((s[l - 1] > 0) != target) return r - l;
				else return r - l + 1;
			}
			else {
				if ((s[l - 1] > 0) != target && target != (s[r + 1] > 0)) {
					if ((r - l + 1) & 1) return r - l;
					else return r - l - 1;
				}
				else if ((s[l - 1] > 0) == target && target == (s[r + 1] > 0)) {
					if ((r - l + 1) & 1) return r - l + 2;
					else return r - l + 1;
				}
				else {
					if ((r - l + 1) & 1) return r - l;
					else return r - l + 1;
				}
			}
		};
		
		int l, r;
		if (x == 1) l = 0;
		else if (used[x - 1]) l = Find(x - 1) - 1;
		else l = x - 1;
		if (x == n) r = n + 1;
		else if (used[x + 1]) r = nxt[Find(x + 1)];
		else r = x + 1;

		if (x - l > 1) discard += cal(l + 1, x - 1, s[x] > 0);
		if (r - x > 1) discard += cal(x + 1, r - 1, s[x] > 0);
		discard -= cal(l + 1, r - 1, s[x] > 0);

		if (x > 1 && used[x - 1]) Merge(x - 1, x);
		if (x < n && used[x + 1]) Merge(x, x + 1);
		used[x] = true;
		return ;
	};
	for (int i = 1; i <= n; i++) v.PB({ABS(s[i]), i});
	sort(v.begin(), v.end());
	for (pair<int, int> i : v) {
		remove(i.S);
		ans = min(ans, r * discard + i.F * c);
	}
	printf("%lld\n", ans);
} 
