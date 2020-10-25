#include <bits/stdc++.h>
using namespace std;
constexpr int kN = int(1E5 + 10);
typedef long long int ll;
#define PB push_back

static inline char GetRawChar() {
	static char buf[1 << 16], *p = buf, *end = buf;
	if (p == end) {
		if ((end = buf + fread(buf, 1, 1 << 16, stdin)) == buf) return '\0';
		p = buf;
	}
	return *p++;
}

static inline int GetInt() {
	int n = 0;
	char c;
	while ((c = GetRawChar()) && (unsigned)(c - '0') <= 10U) n = n * 10 + (c - '0');
	return n;
}

struct BIT {
	ll val[kN], sz;
	void init(int n) {
		sz = n + 5;
		memset(val, 0, sizeof(ll) * (sz + 1));
		//for (int i = 0; i <= sz; i++) val[i] = 0;
		return ;
	}
	void add(int pos, ll x) {
		while (pos < sz) {
			val[pos] += x;
			pos += pos & -pos;
		}
		return ;
	}
	ll ask(int pos) {
		ll ans = 0;
		while (pos) {
			ans += val[pos];
			pos ^= pos & -pos;
		}
		return ans;
	}
};

int a[kN], l[kN], r[kN], k[kN], lim[kN];
ll ans[kN], s[kN], val[kN];
using TIII = tuple<int, int>;
vector<TIII> event, eventtmp1, eventtmp2, eventlim, eventa;
BIT bit;

void solve() {
	int n = GetInt();
	for (int i = 1; i <= n; i++) a[i] = GetInt();
	int q = GetInt();
	for (int i = 1; i <= q; i++) {
		l[i] = GetInt();
		r[i] = GetInt();
		k[i] = GetInt();
	}

	for (int i = 1; i <= q; i++) lim[i] = 0;

	eventlim.clear();
	eventa.clear();
	for (int j = 1; j <= q; j++) eventlim.PB({lim[j], -j});
	for (int j = 1; j <= n; j++) eventa.PB({a[j], +j});
	sort(eventlim.begin(), eventlim.end(), greater<TIII>());
	sort(eventa.begin(), eventa.end(), greater<TIII>());
	for (int i = 1 << 20; i >= 1; i >>= 1) {
		for (int j = 1; j <= q; j++) lim[j] += i;
		for (auto &j : eventlim) get<0>(j) += i;
		bit.init(n);
		event.resize(eventlim.size() + eventa.size());
		merge(eventlim.begin(), eventlim.end(), eventa.begin(), eventa.end(), event.begin(), greater<TIII>());
		for (auto j : event) {
			if (get<1>(j) > 0) {
				bit.add(get<1>(j), 1);
			}
			else {
				val[-get<1>(j)] = bit.ask(r[-get<1>(j)]) - bit.ask(l[-get<1>(j)] - 1);
			}
		}
		eventtmp1.clear();
		eventtmp2.clear();
		for (auto j : eventlim) {
			if (get<1>(j) < 0 && val[-get<1>(j)] < k[-get<1>(j)]) {
				lim[-get<1>(j)] -= i;
				eventtmp2.emplace_back(get<0>(j) - i, get<1>(j));
				//assert(get<0>(j) - i == lim[-get<1>(j)]);
			} else {
				eventtmp1.emplace_back(j);
			}
		}
		merge(eventtmp1.begin(), eventtmp1.end(), eventtmp2.begin(), eventtmp2.end(), eventlim.begin(), greater<TIII>());
	}

		bit.init(n);
		for (auto j : event) {
			if (get<1>(j) > 0) {
				bit.add(get<1>(j), 1);
			}
			else {
				val[-get<1>(j)] = bit.ask(r[-get<1>(j)]) - bit.ask(l[-get<1>(j)] - 1);
			}
		}
	
	bit.init(n);
	for (auto j : event) {
		if (get<1>(j) > 0) {
			bit.add(get<1>(j), get<0>(j));
		}
		else {
			ans[-get<1>(j)] = bit.ask(r[-get<1>(j)]) - bit.ask(l[-get<1>(j)] - 1);
		}
	}

	for (int i = 1; i <= q; i++) {
		cout << ans[i] + s[r[i] - l[i] + 1] + (k[i] - val[i]) * (lim[i] - 0) << '\n';
	}
	return ;
}

void pre() {
	for (ll i = 1; i < kN; i++) s[i] = s[i - 1] + i * i;
	return ;
}

int main() {
	pre();
	int t = GetInt();
	while (t--) solve();
} 
