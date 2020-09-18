#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define F first
#define S second
const int kN = 105;

ll pos[kN], speed[kN];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int cas = 0;
	ll l, s, d, n;
	while(cin >> l >> s >> d >> n && l + s + d + n) {
		d *= 4, l *= 4;
		for(int i = 0; i < n; i++) {
			cin >> pos[i] >> speed[i];
			pos[i] *= 4;
		}

		ll now = 0;
		double ans = 0;
		int first = 0;
		while(true) {
			vector<pii> events;
			int cnt = 0;
			for(int i = 0; i < n; i++) {
				if(pos[i] >= d) continue;

				if(speed[i] == s) {
					if(pos[i] >= l - 4 && pos[i] <= l) cnt++;
				}
				else if(speed[i] > s) {
					if(pos[i] <= l) {
						ll diff = speed[i] - s;
						ll tt = max<ll>(first, ((l - pos[i] - 4) + diff - 1) / diff);
						if(pos[i] + tt * speed[i] <= l + tt * s) events.emplace_back(tt, i);
					}
				}
				else {
					if(pos[i] >= l - 4) {
						ll diff = s - speed[i];
						ll tt = max<ll>(first, ((pos[i] - l) + diff - 1) / diff);
						if(pos[i] + tt * speed[i] >= (l - 4) + tt * s) events.emplace_back(tt, i);
					}
				}
			}

			if(events.empty()) {
				ans = ((double)now + (double)(d - l) / (double)s) / 4.0;
				break;
			}
			sort(events.begin(), events.end());

			int t = events[0].F;
			if(l + s * t >= d) {
				ans = ((double)now + (double)(d - l) / (double)s) / 4.0;
				break;
			}

			now += t;
			l += s * t;
			for(int i = 0; i < n; i++) pos[i] += speed[i] * t;

			cnt++;
			ll tot = cnt * s;
			for(auto &e : events) {
				if(e.F == t) {
					tot += speed[e.S], cnt++;
				}
				else break;
			}
			s = tot / cnt;
			first = 1;
		}
		cout << fixed << setprecision(4) << "Case " << ++cas << ": " << "Anna reaches her destination at time " << ans << " at a speed of " << s << '\n';
	}
	
	return 0;
} 
