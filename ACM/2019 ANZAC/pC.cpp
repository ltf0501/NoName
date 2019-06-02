//#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int64_t __gcd(int64_t x, int64_t y) {
	if (!y) return x;
	return __gcd(y, x % y);
}

int64_t x1, y1, x2, y2; 

bool inRect(int64_t xx, int64_t yy) {
	return x1 <= xx && xx <= x2 && y1 <= yy && yy <= y2;
}

int main() {
	int64_t x, y; cin >> x >> y;
	cin >> x1 >> y1 >> x2 >> y2;
	int64_t g = __gcd(x, y);
	auto px1 = x / g, py1 = y / g;
	auto px2 = x - px1, py2 = y - py1;
	if (g == 1 || (inRect(px1, py1) && inRect(px2, py2))) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
		if (!inRect(px1, py1)) {
			cout << px1 << ' ' << py1 << '\n';
		} else {
			int64_t l = 1, r = g;
			while (l != r) {
				auto m = (l + r) >> 1;
				auto px = m * x / g, py = m * y / g;
				if (inRect(px, py)) l = m + 1;
				else r = m;
			}
			cout << l * x / g << ' ' << l * y / g << '\n';
		}
	}
}
