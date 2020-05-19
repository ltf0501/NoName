#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 100010, kS = 200;

int seq[kN], cnt[kS][kS], idx[kS];
bitset<kS> bs[kS], cnt_bs[kS];
queue<int> qs[kS];

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int s, l, n; cin >> s >> l >> n;
	unordered_map<string, int> mp;
	vector<string> strs;
	for (int i = 0; i < s; i++) {
		bs[i][i] = 1;
		string str; cin >> str;
		strs.push_back(str);
	}
	sort(strs.begin(), strs.end());
	for (int i = 0; i < int(strs.size()); i++) {
		mp[strs[i]] = i;
	}
	for (int i = 0; i < l; i++) {
		string s1, s2; cin >> s1 >> s2;
		int id1 = mp[s1], id2 = mp[s2];
		bs[id1][id2] = 1;
		bs[id2][id1] = 1;
	}
	for (int i = 0; i < n; i++) {
		string str; cin >> str;
		seq[i] = mp[str];
	}
	for (int i = 0; i < n; i++) {
		qs[seq[i]].push(i);
	}
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		int cur = -1;
		for (int j = 0; j < s; j++) {
			if (qs[j].size()) {
				while (idx[j] < qs[j].front()) {
					if (++cnt[j][seq[idx[j]]] == 1) {
						cnt_bs[j][seq[idx[j]]] = 1;
					}
					++idx[j];
				}
				if ((cnt_bs[j] & bs[j]) == cnt_bs[j]) {
					cur = j;
					break;
				}
			}
		}
		assert(cur != -1);
		for (int j = 0; j < s; j++) {
			if (--cnt[j][cur] == 0) {
				cnt_bs[j][cur] = 0;
			}
		}
		qs[cur].pop();
		ans.push_back(cur);
	}
	for (int x : ans) {
		cout << strs[x] << ' ';
	}
	cout << '\n';
} 
