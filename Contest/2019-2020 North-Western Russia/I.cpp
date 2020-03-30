#include <bits/stdc++.h>
using namespace std;

int x[1024], y[1024], h[1024];

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n; cin >> n;
	int max_h = 0;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> h[i];
		max_h = max(max_h, h[i]);
	}
	int64_t l = max_h, r = INT64_MAX / 2;
	while (l != r) {
		auto m = (l + r) >> 1;
		int64_t mn_x = INT64_MIN, mx_x = INT64_MAX, mn_y = INT64_MIN, mx_y = INT64_MAX;
		for (int i = 0; i < n; i++) {
			mn_x = max(mn_x, x[i] - (m - h[i]));
			mx_x = min(mx_x, x[i] + (m - h[i]));
			mn_y = max(mn_y, y[i] - (m - h[i]));
			mx_y = min(mx_y, y[i] + (m - h[i]));
		}
		if (mn_x <= mx_x && mn_y <= mx_y) r = m;
		else l = m + 1;
	}
	{
		auto m = l;
		int64_t mn_x = INT64_MIN, mx_x = INT64_MAX, mn_y = INT64_MIN, mx_y = INT64_MAX;
		for (int i = 0; i < n; i++) {
			mn_x = max(mn_x, x[i] - (m - h[i]));
			mx_x = min(mx_x, x[i] + (m - h[i]));
			mn_y = max(mn_y, y[i] - (m - h[i]));
			mx_y = min(mx_y, y[i] + (m - h[i]));
		}
		cout << mn_x << ' ' << mn_y << ' ' << m << '\n';
	}
} 
