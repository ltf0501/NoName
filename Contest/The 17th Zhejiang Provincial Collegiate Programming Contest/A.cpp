#include <bits/stdc++.h>
using namespace std;

constexpr int kStart = 20000101, kEnd = 99991231;

unsigned short cnt[kEnd - kStart + 10];

bool IsLeap(int y) {
	if (y % 400 == 0) return true;
	if (y % 100 == 0) return false;
	if (y % 4 == 0) return true;
	return false;
}

int Days(int y, int m) {
	switch (m) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 2:
			return IsLeap(y) + 28;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		default:
			assert(false);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	for (int i = kStart; i <= kEnd; i++) {
		int y = i / 10000;
		int m = i / 100 % 100;
		int d = i % 100;
		bool skip = false;
		if (m < 1 || 12 < m) skip = true;
		else if (d < 1 || Days(y, m) < d) skip = true;
		if (skip) {
			cnt[i - kStart + 1] = cnt[i - kStart];
		} else {
			string s = to_string(i);
			cnt[i - kStart + 1] = cnt[i - kStart] + (strstr(s.c_str(), "202") != nullptr);
		}
	}
	int t; cin >> t;
	while (t--) {
		int y1, m1, d1, y2, m2, d2; cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
		int c1 = y1 * 10000 + m1 * 100 + d1;
		int c2 = y2 * 10000 + m2 * 100 + d2;
		cout << cnt[c2 - kStart + 1] - cnt[c1 - kStart] << '\n';
	}
} 
