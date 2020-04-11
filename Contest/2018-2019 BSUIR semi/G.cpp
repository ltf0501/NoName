#include <bits/stdc++.h>
using namespace std;

string gao(string s) {
	string res = "";
	for(int i = 0, j = 0; i < int(s.size()); ) {
		while(j < int(s.size()) && s[i] == s[j]) j++;
		res += j - i + '0';	
		res += s[i];
		i = j;
	}
	return res;
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	long long n, m; cin >> n >> m;
	n--;

	if(n >= 34) n = 30 + (n - 30) % 4;
	
	string s = "1";
	for(int i = 0; i < 50; i++) {
		if(i == n) {
			if(int(s.size()) > m) s = s.substr(int(s.size()) - m, m);
			cout << s << '\n';
			return 0;
		}
		s = gao(s);
		if(int(s.size()) > 1000) s = s.substr(int(s.size()) - 1000, 1000);
	}
	return 0;
}
