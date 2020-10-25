#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;
#define F first
#define S second
#define PB push_back

typedef long long int ll;
constexpr int kN = int(1E5 + 10);

ll ans[kN], t[kN], k[kN], ppl[kN];
bool tp[kN];

int main() {
freopen("expect.in", "r", stdin);	
freopen("expect.out", "w", stdout);	
	int n, q;
	ll now = 0, lst = 0, nans = 0, na = 0;
	string s;
	vector<tuple<ll, ll, ll>> event; // time, type, cnt
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> s >> t[i] >> k[i];
		if (s[0] == '-') tp[i] = false;
		else tp[i] = true;
	}
	for (int i = 1; i <= q; i++) cin >> ppl[i];
	
	for (int i = 1; i <= n; i++) {
		if (now > 0) event.PB({now, 1, t[i] - lst});
		if (tp[i]) now -= k[i];
		else now += k[i];
		lst = t[i];
	}
	for (int i = 1; i <= q; i++) event.PB({ppl[i], 0, i});
	sort(event.begin(), event.end());
	reverse(event.begin(), event.end());
	lst = get<0>(event[0]);
	for (tuple<ll, ll, ll> i : event) {
		if (get<0>(i) < lst) {
			nans += na * (lst - get<0>(i));
			lst = get<0>(i);
		}
		if (get<1>(i) == 0) ans[get<2>(i)] = nans;
		else na += get<2>(i);
	}

	for (int i = 1; i <= q; i++) {
		if (ppl[i] < now) cout << "INFINITY\n";
		else cout << ans[i] << '\n';
	}
} 
