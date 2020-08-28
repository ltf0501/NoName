#include <bits/stdc++.h>
using namespace std;
const int kN = 3e5 + 10;

int n, k;
int main() {
	freopen("kaleidoscope.in", "r", stdin);
	freopen("kaleidoscope.out", "w", stdout);
	
	//ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	vector<pair<int, string>> v;
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int tot = 0;
		for(auto c : s)
			if(c != '.') tot += c - '0';
		v.emplace_back(tot, s);
	}

	// even, odd
	
	while(k > 2) {
		cout << v.back().second << '\n';
		v.pop_back();
		k--;
	}

	int num = 0;
	for(auto p : v) num += (p.first & 1); 
	if(num == 0 || num == int(v.size())) { // all odd, even
		cout << v.back().second << '\n';
		v.pop_back();
		for(auto p : v) cout << p.second << ' ';
		cout << '\n';
	}
	else {
		vector<string> ans[2];
		for(auto p : v) ans[p.first & 1].push_back(p.second);
		for(int i = 0; i < 2; i++) {
			for(auto s : ans[i]) cout << s << ' ';
			cout << '\n';
		}
	}
	return 0;
} 
