bool debug = false;
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define PB push_back

void make_palin(string &a) {
	string ans = a;
	reverse(a.begin(), a.end());
	a += ans;
	return ;
}
void make_palin1(string &a) {
	string ans = a;
	reverse(a.begin(), a.end());
	a.pop_back();
	a += ans;
	return ;
}

void sub(string &a, string b) {
	if (debug) cout << "sub : " << a << " " << b << '\n';
	int n = int(b.size());
	for (int i = 0; i < n; i++) {
		a[i] -= b[i] - '0';
		if (a[i] < '0') {
			a[i] += 10;
			a[i + 1]--;
		}
	}
	while (n < int(a.size()) && a[n] < '0') {
		a[n] += 10;
		a[++n]--;
	}

	while (!a.empty()) {
		if (a.back() == '0') a.pop_back();
		else break;
	}
	if (debug) {
		string s;
		cin >> s;
	}
	return ;
}

void out(string a) {
	reverse(a.begin(), a.end());
	cout << a << '\n';
	return ;
}

void solve() {
	string s, tmp;
	vector<string> v;
	bool fone, fzero;
	int n;
	cin >> s;
	reverse(s.begin(), s.end());	
	while (s.size() > 1) {
		if (debug) cout << s << '\n';
		if (s.size() == 2 && s[1] == '1') {
			if (s[0] == '0') {
				v.PB("1");
				v.PB("9");
			}
			else if (s[0] == '1') v.PB(s);
			else {
				v.PB("11");
				s.pop_back();
				s[0] -= 1;
				v.PB(s);
			}
			s = "";
			break;
		}
		n = int(s.size());
		tmp = "";
		

		// special case
		if (s[n - 1] == '1') fone = true;
		else fone = false;
		fzero = true;
		for (int i = n / 2; i < n - 1; i++) if (s[i] != '0') {
			fzero = false;
			break;
		}
		if (fone && fzero) for (int i = 0; i < n - 1; i++) tmp += "9";
		else {
			for (int i = n / 2; i < n; i++) tmp += s[i];
			sub(tmp, "1");
			if (n & 1) make_palin1(tmp);
			else make_palin(tmp);
		}
		v.PB(tmp);
		if (debug) cout << tmp << '\n';
		sub(s, tmp);
	}
	if (s.size() == 1) v.PB(s);
	cout << v.size() << '\n';
	for (string i : v) out(i);
	return ;
}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
}

