#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	string s; cin >> s;
	deque<char> left, right;
	for (char c: s) {
		if (c == 'L') {
			if (left.size()) {
				right.push_back(left.back());
				left.pop_back();
			}
		} else if (c == 'R') {
			if (right.size()) {
				left.push_back(right.back());
				right.pop_back();
			}
		} else {
			left.push_back(c);
		}
	}
	for (char c: left) cout << c;
	while (right.size()) {
		cout << right.back();
		right.pop_back();
	}
}
