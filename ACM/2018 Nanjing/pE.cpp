#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int n, k;
string s1, s2;
int cnt[maxn];
int st[maxn];
string F(string s) {
	if(k == 1) return "";	
	int tp = 0;
	for(int i = 0; i < n; i++) {
		if(tp && st[tp] == s[i] - '0') {
			cnt[tp]++;
			if(cnt[tp] == k) tp--;
		}
		else {
			tp++;
			st[tp] = s[i] - '0';
			cnt[tp] = 1;
		}
	}
	string res = "";
	for(int i = 1; i <= tp; i++) {
		while(cnt[i]--) res += st[i] + '0';
	}
	//cout << "res: " << res << '\n';
	return res;
}
int main() {
	cin.tie(0); ios_base::sync_with_stdio(false);
	cin >> n >> k;
	cin >> s1 >> s2;
	if(F(s1) == F(s2)) cout <<"Yes\n";
	else cout <<"No\n";
	return 0;
}
