#include <bits/stdc++.h>
using namespace std;

string n;
int k;
int vis[11];
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T; cin >> T;
	while(T--) {
		cin >> n >> k;
		if(n == "1000000000") {
			cout << n << ' ' << n << '\n';
			continue;
		}
		auto mn = n, mx = n;
		int sz = int(n.size());
		int now = 0;
		vector<int> p(sz);
		for(int i = 0; i < sz; i++) p[i] = i;
		do {
			now++;
			int cnt = 0;
			for(int i = 0; i < sz; i++) {
				if(vis[i] == now) continue;
				int cur = i;
				cnt++;
				while(vis[cur] != now) {
					vis[cur] = now;
					cur = p[cur];
				}
			}
			//cerr << "cnt = " << cnt << '\n';
			if(sz - cnt <= k && n[p[0]] != '0') {
				string tmp;
				for(int i = 0; i < sz; i++) tmp += n[p[i]];
				//cerr << "tmp = " << tmp << '\n';
				mn = min(mn, tmp), mx = max(mx, tmp);
			}
		} while(next_permutation(p.begin(), p.end()));
		cout << mn << ' ' << mx << '\n';
	}
	return 0;
} 
