#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 4e6;

//int trie[kPool][kSigma], scores[kPool], poolHead;
//
//void Insert(const string &s, int score) {
//	int p = 0;
//	for (char c : s) {
//		int b = c - 'a';
//		if (!trie[p][b]) trie[p][b] = poolHead++;
//		p = trie[p][b];
//	}
//	scores[p] += score;
//}
//
//int Query(const string &s) {
//	int p = 0;
//	for (char c : s) {
//		int b = c - 'a';
//		if (!trie[p][b]) return -kInf;
//		p = trie[p][b];
//	}
//	return scores[p];
//}

constexpr uint64_t kModMP = (1ULL << 61) - 1;
uint64_t ModMulMP(uint64_t a, uint64_t b) {
	uint64_t l1 = uint32_t(a), h1 = a >> 32, l2 = uint32_t(b), h2 = b >> 32;
	uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
	uint64_t ret = (l & kModMP) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & kModMP) + (ret >> 61);
	ret = (ret & kModMP) + (ret >> 61);
	return ret - 1;
}

string s[1023];

void Solve() {
	int n, m;
	cin >> n >> m;
	vector<pair<uint64_t, int>> scores;
	scores.reserve(m);
	for (int i = 0; i < n; i++) cin >> s[i];
	for (int i = 0; i < m; i++) {
		string ss; cin >> ss;
		int score; cin >> score;
		uint64_t h = 0;
		for (char c : ss) {
			h = ModMulMP(h, 32ULL) + uint64_t(c);
			if (h >= kModMP) h -= kModMP;
		}
		scores.emplace_back(h, score);
	}
	sort(scores.begin(), scores.end());
	int64_t ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s[i][j] == '#') continue;
			if (!i || s[i - 1][j] == '#') {
				uint64_t h = 0;
				for (int k = i; k < n && s[k][j] != '#'; k++) {
					h = ModMulMP(h, 32ULL) + uint64_t(s[k][j]);
					if (h >= kModMP) h -= kModMP;
					//cerr << s[k][j];
				}
				//cerr << '\n';
				auto it = lower_bound(scores.begin(), scores.end(), make_pair(h, 0));
				if (it == scores.end() || it->first != h) {
					ans = -1;
					goto End;
				}
				ans += it->second;
			}
			if (!j || s[i][j - 1] == '#') {
				uint64_t h = 0;
				for (int k = j; k < n && s[i][k] != '#'; k++) {
					h = ModMulMP(h, 32ULL) + uint64_t(s[i][k]);
					if (h >= kModMP) h -= kModMP;
					//cerr << s[i][k];
				}
				//cerr << '\n';
				auto it = lower_bound(scores.begin(), scores.end(), make_pair(h, 0));
				if (it == scores.end() || it->first != h) {
					ans = -1;
					goto End;
				}
				ans += it->second;
			}
		}
	}
End:
	cout << ans << '\n';
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) Solve();
} 
