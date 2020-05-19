#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n; cin >> n;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		if (s[0] == '-') continue;
		if (s.size() > 6 && s != "1000000") continue;
		v.push_back(stoi(s));
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 0; i < int(v.size()); i++) {
		if (v[i] != i) {
			cout << i << '\n';
			return 0;
		}
	}
	cout << v.size() << '\n';
} 
