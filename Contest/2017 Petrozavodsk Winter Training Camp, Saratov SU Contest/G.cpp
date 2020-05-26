#include <bits/stdc++.h>
using namespace std;

int n, m, oi[1025], a[2049], b[2049], d[2049];
double dist[1025];

bool Solve(double t) {
	dist[0] = 0;
	for (int i = 1; i <= n; i++) dist[i] = 1e9;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			dist[a[i]] = min(dist[a[i]], dist[b[i]] + t - d[i]);
		}
		for (int i = 1; i <= n; i++) {
			if (oi[i] != INT_MAX) {
				dist[i] = min(dist[i], dist[0] + oi[i]);
				dist[0] = min(dist[0], dist[i] - oi[i]);
			}
			dist[i] = min(dist[i], dist[0] + 1e9);
			dist[0] = min(dist[0], dist[i] + 1e9);
		}
	}
	for (int i = 0; i < m; i++) {
		if (dist[a[i]] > dist[b[i]] + t - d[i]) return false;
	}
	for (int i = 1; i <= n; i++) {
		if (oi[i] != INT_MAX) {
			if (dist[i] > dist[0] + oi[i]) return false;
			if (dist[0] > dist[i] - oi[i]) return false;
		}
		if (dist[i] > dist[0] + 1e9) return false;
		if (dist[0] > dist[i] + 1e9) return false;
	}
	return true;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	while (cin >> n >> m) {
		for (int i = 1; i <= n; i++) {
			string s; cin >> s;
			oi[i] = s == "?" ? INT_MAX : stoi(s);
		}
		for (int i = 0; i < m; i++) {
			cin >> a[i] >> b[i] >> d[i];
		}
		double l = 0, r = 30000000;
		for (int i = 0; i < 64; i++) {
			double mid = (l + r) / 2;
			if (Solve(mid)) r = mid;
			else l = mid;
		}
		cout << fixed << setprecision(20) << r << '\n';
		for (int i = 1; i <= n; i++) {
			double x = oi[i] == INT_MAX ? dist[i] : oi[i];
			cout << fixed << setprecision(20) << x << ' ';
		}
		cout << '\n';
	}
} 
