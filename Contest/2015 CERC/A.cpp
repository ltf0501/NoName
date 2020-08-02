#include <bits/stdc++.h>
using namespace std;

const string kDigit[7][11] = {
	{ "xxxxx", "    x", "xxxxx", "xxxxx", "x   x", "xxxxx", "xxxxx", "xxxxx", "xxxxx", "xxxxx", "     " },
	{ "x   x", "    x", "    x", "    x", "x   x", "x    ", "x    ", "    x", "x   x", "x   x", "  x  " },
	{ "x   x", "    x", "    x", "    x", "x   x", "x    ", "x    ", "    x", "x   x", "x   x", "  x  " },
	{ "x   x", "    x", "xxxxx", "xxxxx", "xxxxx", "xxxxx", "xxxxx", "    x", "xxxxx", "xxxxx", "xxxxx" },
	{ "x   x", "    x", "x    ", "    x", "    x", "    x", "x   x", "    x", "x   x", "    x", "  x  " },
	{ "x   x", "    x", "x    ", "    x", "    x", "    x", "x   x", "    x", "x   x", "    x", "  x  " },
	{ "xxxxx", "    x", "xxxxx", "xxxxx", "    x", "xxxxx", "xxxxx", "    x", "xxxxx", "xxxxx", "     " }
};

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	string s;
	int n = 0;
	vector<vector<string>> v;
	while (cin >> s) {
		if (n == 0) {
			n = (int(s.size() + 1) / 6);
			v.resize(n);
		} else {
			assert(n == (int(s.size() + 1) / 6));
		}
		for (int i = 0; i < n; i++) {
			v[i].push_back(s.substr(i * 6, 5));
		}
	}
	for (int i = 0; i < n; i++) {
		for (string &ss : v[i]) {
			for (char &c : ss) {
				if (c == '.') c = ' ';
			}
			cerr << ss << '\n';
		}
		cerr << '\n';
	}
	int64_t a = -1, b = -1;
	string parse;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 11; j++) {
			bool ok = [&]() {
				for (int k = 0; k < 7; k++) {
					if (v[i][k] != kDigit[k][j]) return false;
				}
				return true;
			}();
			if (ok) {
				if (j == 10) {
					cerr << parse << '\n';
					a = stoll(parse);
					parse = "";
				} else {
					parse.push_back(char('0' + j));
				}
				break;
			}
			assert(j != 10);
		}
	}
	cerr << parse << '\n';
	b = stoll(parse);
	assert(a >= 0 && b >= 0);
	cerr << a << '+' << b << '\n';
	auto ans = to_string(a + b);
  for (int k = 0; k < 7; k++) {
		bool first = true;
		for (char c : ans) {
      if (!first) cout << '.';
			first = false;
			for (char cc : kDigit[k][c - '0']) {
				cout << (cc == ' ' ? '.' : cc);
			}
		}
		cout << '\n';
	}
} 
