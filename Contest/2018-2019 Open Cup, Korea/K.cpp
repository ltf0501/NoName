#include <stdio.h>
#include <utility>
#include <algorithm>
using namespace std;
#define F first
#define S second
typedef long long int ll;
constexpr int kN = int(3E5 + 10);
struct BIT {
	ll val[kN << 1];
	void init() {for (int i = 0; i < kN; i++) val[i] = 0;}
	void add(int pos, ll x) {
		pos++;
		while (pos < kN) {
			val[pos] = max(val[pos], x);
			pos += pos & -pos;
		}
		return ;
	}
	ll ask(int pos) {
		pos++;
		ll ans = 0;
		while (pos) {
			ans = max(ans, val[pos]);
			pos ^= pos & -pos;
		}
		return ans;
	}
};

BIT bit;
int c[kN], d[kN];
pair<int, int> p[kN];

int main() {
	int n, now = 1;
	bool f;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &d[i]);
	bit.init();
	for (int i = 1; i <= n; i++) p[i] = {i - c[i] + 1, -i};	
	sort(p + 1, p + n + 1);
	while (now <= n && p[now].F <= 0) now++;
	while (now <= n && p[now].F <= 1) {
		if (p[now].F != -p[now].S) bit.add(n + p[now].S + 1, bit.ask(n + p[now].S) + d[-p[now].S]);
		now++;
	}
	printf("%lld\n", bit.ask(n - 1) + (c[1] == 1 ? d[1] : 0));
	for (int i = 2; i <= n; i++) {
		if (i - 1 + c[i - 1] - 1 >= i && i - 1 + c[i - 1] - 1 <= n) bit.add((n - (i - 1 + c[i - 1] - 1)), bit.ask(n - (i - 1 + c[i - 1] - 1)) + d[i - 1]);
		while (now <= n && p[now].F <= i) {
			if (-p[now].S != p[now].F) bit.add(n + p[now].S + 1, bit.ask(n + p[now].S) + d[-p[now].S]);
			now++;
		}
		printf("%lld\n", bit.ask(n - i) + (c[i] == 1 ? d[i] : 0));
	} 
} 
