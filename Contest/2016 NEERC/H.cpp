#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define F first
#define S second
#define PB push_back


constexpr int kN = int(1E5 + 10);
bool val[kN];

void out(pair<int, int> p) {
	if (p.F == 0) cout << "x <= " << p.S - 32768;
	else if (p.S == 65535) cout << "x >= " << p.F - 32768;
	else cout << "x >= " << p.F - 32768 << " && x <= " << p.S - 32768;
	return ;
}

int main() {
freopen("hard.in", "r", stdin);	
freopen("hard.out", "w", stdout);	
	int n, lst, l, r, cnt, idx, sz;
	vector<pair<int, int>> v;
	bool b, lm, rm, t, f;
	string s;
	while (getline(cin, s)) {
		cnt = 0;
		for (char i : s) if (i == 'x') cnt++;
		if (cnt == 1) {
			b = false;
			for (char i : s) if (i == '>') b = true;
			l = 0;
			for (char i : s) if ('0' <= i && i <= '9') l = l * 10 + i - '0';
			for (char i : s) if (i == '-') l = -l;
			//cout << l << '\n';
			l += 32768;
			if (b) {
				for (int i = l; i < 65536; i++) val[i] = true;
			}
			else {
				for (int i = 0; i <= l; i++) val[i] = true;
			}
		}
		else {
			n = int(s.size());
			l = r = 0;
			if (s[5] == '-') {
				lm = true;
				idx = 6;
			}
			else {
				lm = false;
				idx = 5;
			}
			while (s[idx] != ' ') {
				l = l * 10 + s[idx] - '0';
				idx++;
			}
			idx += 9;
			if (s[idx] == '-') {
				rm = true;
				idx++;
			}
			else rm = false;
			while (s[idx] != ' ' && idx < n) {
				r = r * 10 + s[idx] - '0';
				idx++;
			}
			
			if (lm) l = -l;
			if (rm) r = -r;
			//cout << l << " " << r << '\n';
			l += 32768;
			r += 32768;
			for (int i = l; i <= r; i++) val[i] = true;
		}
	}
	t = f = true;
	for (int i = 0; i < 65536; i++) {
		t &= val[i];
		f &= !val[i];
	}
	if (t) cout << "true\n";
	else if (f) cout << "false\n";
	else {
		lst = 0;
		for (int j = 1; j < 65536; j++) if (val[j] != val[lst]) {
			if (val[lst]) v.PB({lst, j - 1});
			lst = j;
		}
		if (val[lst]) v.PB({lst, 65535});
		sz = int(v.size());
		out(v[0]);
		for (int i = 1; i < sz; i++) {
			cout << " ||\n";
			out(v[i]);
		}
		cout << "\n";
	}
} 
