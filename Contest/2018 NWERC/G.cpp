#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back

int tp[26];

int main() {
	vector<pair<int, int>> ans;
	vector<int> v;
	int n, lst = 0, sz, x = 0, y = 0;
	string s;
	cin >> s;
	n = int(s.size());
	for (int i = 1; i < n; i++) if (s[i] == s[i - 1]) {
		cout << "impossible\n";
		return 0;
	}
	tp['L' - 'A'] = 4;
	tp['R' - 'A'] = 5;
	tp['U' - 'A'] = 6;
	tp['D' - 'A'] = 7;
	for (int i = 0; i < n; i++) s[i] = tp[s[i] - 'A'];
	
	if (n >= 3) {
		if (s[n - 1] == s[n - 3] && (s[n - 2] ^ s[n - 1]) <= 1) {
			cout << "impossible\n";
			return 0;
		}
	}

	for (int i = 1; i < n; i++) {
		if ((s[i] ^ s[i - 1]) & 2) {
			v.PB(s[i - 1]);
			lst = i;
		}
	}
	v.PB(s[n - 1]);



	sz = int(v.size());	
	for (int i = 0; i < sz; i++) {
		if (v[i] & 2) {
			ans.PB({x, y + (1 << i) + 1});
			ans.PB({x, y - (1 << i) - 1});
			if (v[i] == 6) y += (1 << i);
			else y -= (1 << i);
		}
		else {
			ans.PB({x + (1 << i) + 1, y});
			ans.PB({x - (1 << i) - 1, y});
			if (v[i] == 4) x -= (1 << i);
			else x += (1 << i);
		}
	}

	cout << -x << " " << -y << '\n';
	cout << int(ans.size()) << '\n';
	for (pair<int, int> i : ans) cout << i.F - x << " " << i.S - y << '\n';
} 
