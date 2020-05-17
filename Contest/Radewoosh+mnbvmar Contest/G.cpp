#include <bits/stdc++.h>
using namespace std;
#define PB push_back
constexpr int kN = int(4E6 + 10);

int dp[kN];

string s;
int Hash(int l, int r) {
	int ans = 1;
	for(int i = l; i <= r; i++) {
		ans <<= 1;
		if(s[i] == 'B') ans |= 1;
	}
	return ans;
} 

void pre() {
	for (int i = 0; i < kN; i++) dp[i] = -1;
	return ;
}

int dfs(int l, int r) {
	if(l > r) return 0;
	//cerr << "now = " << s.substr(l, r - l + 1) << '\n';
	if(l == r) {
		if(s[l] == 'A') return 0;
		if(s[l] == 'B' || s[l] == 'C') return 1;
		return 2;
	}
	vector<int> v;
	int sz;
	string nxt, left, right;
	for (int i = l; i <= r; i++) if (s[i] == 'A') {
		int a = 0, b = 0;
		if(i != l) {
			if(s[i - 1] == 'D') a = 1;
		}
		if(i != r) {
			if(s[i + 1] == 'D') b = 1;
		}
		return a ^ b ^ dfs(l, i - 2) ^ dfs(i + 2, r);
	}
	int x = Hash(l, r);
	if (dp[x] >= 0) return dp[x]; 

	for (int i = l; i <= r; i++) if (s[i] == 'B') {
		s[i] = 'A';
		v.PB(dfs(l, r));
		s[i] = 'B';
	}

	for (int i = l; i <= r; i++) if (s[i] == 'D') {
		v.PB(dfs(l, i - 1) ^ dfs(i + 1, r));
		s[i] = 'B';
		v.PB(dfs(l, r));
		s[i] = 'D';
	}

	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	sz = int(v.size());
	int val = -1;
	for(int i = 0; i < sz; i++) 
		if(v[i] != i) {val = i; break;}
	if(val == -1) val = sz;
	//cerr << s.substr(l, r - l + 1) << ": " << "x = " << x << " val = " << val << '\n';
	return dp[x] = val;
}

char make(string s) {
	if (s == "III") return 'D';
	else if (s == ".I.") return 'A';
	else if (s == "I.I") return 'C';
	else return 'B';
}

string x[30];

void solve() {
	int n, ans = 0, lst = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> x[i];
	s.clear();

	for (int i = 1; i <= n; i++) s += make(x[i]);

	for (int i = 0; i < n; i++) if (s[i] == 'C') {
		ans ^= dfs(lst, i - 1);
		lst = i + 1;
	}
	ans ^= dfs(lst, n - 1);
	//cerr << ans << '\n';
	if (ans != 0) cout << "First" << '\n';
	else cout << "Second" << '\n';

	return ;
}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(0);
	pre();
	int t;
	cin >> t;
	while (t--) solve();
} 
