#include <bits/stdc++.h>
using namespace std;
const int kN = 205;

int n;
string s[kN];
int cnt[26], now[26];
vector<int> g[26];

int main() {
	freopen("agnatic.in", "r", stdin);
	freopen("agnatic.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> s[i];
		vector<int> ccnt(26);
		for(auto c : s[i]) ccnt[c - 'A']++;
		for(int j = 0; j < 26; j++) if(ccnt[j]) {
			if(cnt[j] && cnt[j] != ccnt[j]) {
				return cout << "NO" << '\n', 0;	
			}
			cnt[j] = ccnt[j];
			g[j].push_back(i);
		}
	}

	for(int i = 0; i < n; i++) reverse(s[i].begin(), s[i].end()); 
	for(int i = 0; i < n; i++) now[s[i].back() - 'A']++;
	int sum = 0;
	for(int i = 0; i < 26; i++) sum += cnt[i];

	string ans;
	for(int i = 0; i < sum; i++) {
		bool flag = 0;
		for(int j = 0; j < 26; j++) if(cnt[j] && now[j] == int(g[j].size())) {
			ans += char(j + 'A');
			now[j] = 0;
			for(int id : g[j]) {
				s[id].pop_back();
				if(!s[id].empty()) now[s[id].back() - 'A']++;
			}
			cnt[j]--, flag = 1;
			break;
		}
		if(!flag) {
			return cout << "NO" << '\n', 0;
		}
	}
	cout << "YES" << '\n' << ans << '\n';
	return 0;
}

