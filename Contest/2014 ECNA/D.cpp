#include <bits/stdc++.h>
using namespace std;

#define PB push_back
constexpr int kN = int(5E3 + 10);

int8_t vis[55][55][kN], timer;
vector<int> dp[55][55];
int cnt[kN];

vector<int> merge(vector<int>& a, vector<int> &b, int l, int r) {
	vector<int> ans;
	for (int i : a) for (int j : b) {
		
		if (i >= j) {
			if(vis[l][r][i + j] != timer) vis[l][r][i + j] = timer, ans.push_back(i + j);
		}
		else {
			if(vis[l][r][j - i] != timer) vis[l][r][j - i] = timer, ans.push_back(j - i);
		}
	}
	
	return ans;
}

void solve(string s) {
	timer++;
	int n = int(s.size());
	vector<vector<int>> v;
	for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++) dp[i][j].clear();
	for (int i = 1; i <= n; i++) {
		if (s[i - 1] == 'I') dp[i][i].PB(1);
		else if (s[i - 1] == 'V') dp[i][i].PB(5);
		else if (s[i - 1] == 'X') dp[i][i].PB(10);
		else if (s[i - 1] == 'L') dp[i][i].PB(50);
		else dp[i][i].PB(100);
	}
	for (int k = 2; k <= n; k++) for (int i = 1; i <= n; i++) {
		int j = i + k - 1;
		if (j > n) break;
		v.clear();
		for (int x = 1; x < k; x++) {
			auto tmp = merge(dp[i][i + x - 1], dp[i + x][j], i, j); 
			for(auto xx : tmp) dp[i][j].push_back(xx);
		}
	}
	sort(dp[1][n].begin(), dp[1][n].end());
	for (int i : dp[1][n]) cout << " " << i;
	cout << '\n';
	return ;
}

int main() {
	string s;
	int idx = 1;
	while (true) {
		cin >> s;
		if (s[0] == '0') break;
		else {
			cout << "Case " << idx++ << ":";
			solve(s);
		}
	}
} 
