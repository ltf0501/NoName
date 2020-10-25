#include <iostream>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back

bool lower(char c) {
	return 'a' <= c && c <= 'z';
}

bool capital(char c) {
	return 'A' <= c && c <= 'Z';
}

int main() {
freopen("abbreviation.in", "r", stdin);	
freopen("abbreviation.out", "w", stdout);	
	vector<pair<string, int>> v; // 0 -> nothing, 1 -> word, 2 -> cap, 3 -> symbol
	pair<string, int> tmp;
	int n, sz, nxt;
	string s;
	while (getline(cin, s)) {
		v.clear();
		n = int(s.size());
		tmp = {"", 0};
		for (int i = 0; i < n; i++) {
			if (lower(s[i]) || capital(s[i])) {
				tmp.F += s[i];
				tmp.S = 2;
			}
			else {
				if (tmp.S != 0) {
					if (tmp.F.size() > 1 && capital(tmp.F[0])) {
						sz = int(tmp.F.size());
						for (int j = 1; j < sz; j++) if (capital(tmp.F[j])) tmp.S = 1;
					}
					else tmp.S = 1;
					v.PB(tmp);
				}
				tmp.F = "";
				tmp.F += s[i];
				v.PB({tmp.F, 3});
				tmp.S = 0;
				tmp.F = "";
			}
		}
		if (tmp.S != 0) {
			if (tmp.F.size() > 1 && capital(tmp.F[0])) {
				sz = int(tmp.F.size());
				for (int j = 1; j < sz; j++) if (capital(tmp.F[j])) tmp.S = 1;
			}
			else tmp.S = 1;
			v.PB(tmp);
		}
		sz = int(v.size());
		for (int i = 0; i < sz; i++) {
			if (v[i].S == 2) {
				nxt = i + 1;
				while (nxt + 1 < sz) {
					if (v[nxt].S == 3 && v[nxt].F == " " && v[nxt + 1].S == 2) nxt += 2;
					else break;
				}
				if (nxt - i > 1) {
					for (int j = i; j < nxt; j += 2) cout << v[j].F[0];
					cout << " (";
					for (int j = i; j < nxt; j++) cout << v[j].F;
					cout << ")";
					i = nxt - 1;
				}
				else cout << v[i].F;
			}
			else cout << v[i].F;	
		}
		cout << '\n';
		//for (pair<string, int> i : v) {
		//	cout << i.F << "(" << i.S << '\n';
		//}
		//cout << "---\n";
	}
} 
