#include <stdio.h>
#include <vector>

#include <string.h>
using namespace std;
#define PB push_back
constexpr int kN = int(8E5 + 10);

struct BIT {
	int a[kN], sz, from;
	void init(int n) {
		sz = n; 
		from = 1;
		while (from <= sz) from <<= 1;
		sz = from;

		for (int i = 1; i <= sz; i++) a[i] = 0;
		return ;
	}
	void add(int pos, int x) {
		while (pos <= sz) {
			a[pos] += x;
			pos += pos & -pos;
		}
		return ;
	}
	int ask(int pos) {
		int ans = 0;
		while (pos) {
			ans += a[pos];
			pos ^= pos & -pos;
		}
		return ans;
	}
	int ask_pos(int x) {
		int now = 0, ans = 0;
		for (int i = from; i >= 1; i >>= 1) if (now + a[ans + i] < x) {
			now += a[ans + i];
			ans += i;
		}
		return ans + 1;
	}
};


BIT bit;
int c[kN], a[kN], seg[kN], st[kN], len[kN], idx[kN], ans[kN];
vector<int> v[kN], sg[kN];

int main() {
	int n, now = 0, l, r, mid, tmp;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &c[i], &a[i]);
	for (int i = 1; i <= n; i++) seg[i] = len[i] = 0;
	bit.init(n);	
	bit.add(1, 1);
	for (int i = 1; i <= n; i++) {
		if (v[c[i]].empty()) {
			seg[i] = ++now;
			idx[i] = 1;
			len[now] = 1;
			v[c[i]].PB(now);
			bit.add(now + 1, 1);
		}
		else if (bit.ask(v[c[i]].back()) + len[v[c[i]].back()] < i - a[i]) {
			seg[i] = ++now;
			idx[i] = 1;
			len[now] = 1;
			v[c[i]].PB(now);
			bit.add(now + 1, 1);
		}
		else {
			tmp = bit.ask(v[c[i]][0]);
			if (tmp + len[v[c[i]][0]] >= i - a[i]) {
				len[v[c[i]][0]]++;
				seg[i] = v[c[i]][0];
				idx[i] = max(tmp, i - a[i]) - tmp + 1;
				bit.add(seg[i] + 1, 1);
			}
			else {
				l = 0, r = int(v[c[i]].size()) - 1;
				while (r - l > 1) {
					mid = (l + r) >> 1;
					if (bit.ask(v[c[i]][mid]) + len[v[c[i]][mid]] >= i - a[i]) r = mid;
					else l = mid;
				}
				tmp = bit.ask(v[c[i]][r]);
				len[v[c[i]][r]]++;
				seg[i] = v[c[i]][r];
				idx[i] = max(tmp, i - a[i]) - tmp + 1;
				bit.add(seg[i] + 1, 1);
			}
		}
	}
	for (int i = 1; i <= now; i++) st[i] = bit.ask(i);
	for (int i = 1; i <= n; i++) sg[seg[i]].PB(i);
	for (int i = 1; i <= now; i++) if (sg[i].size() > 1) {
		bit.init(len[i]);
		for (int j = 1; j <= len[i]; j++) bit.add(j, 1);
		for (int j = len[i] - 1; j >= 0; j--) {
			tmp = bit.ask_pos(idx[sg[i][j]]);
			bit.add(tmp, -1);
			ans[tmp + st[i] - 1] = sg[i][j];
		}
	}
	else ans[st[i]] = sg[i][0];

	printf("%d", ans[1]);
	for (int i = 2; i <= n; i++) printf(" %d", ans[i]);
	printf("\n");
}
