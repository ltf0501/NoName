#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define PB push_back
int cnt[26];
int main() {
	string s, ans;
	int n;
	vector<int> v;
	cin >> s;
	n = int(s.size());
	sort(s.begin(), s.end());
	for (char i : s) cnt[i - 'a']++;

	for (int i = 0; i < 26; i++) if (cnt[i] > (n >> 1)) {

		for (int j = 0; j < 26; j++) if (cnt[j]) v.PB(j);	

		if (v.size() >= 3) {
			for (int k = 0; k < (n >> 1); k++) ans += 'a' + i;
			cnt[i] -= n >> 1;
			for (int k = 0; k < int(v.size()); k++) if (v[k] != i) {
				ans += 'a' + v[k];
				cnt[v[k]]--;
				while (cnt[i]--) ans += 'a' + i;
				while (cnt[v[k]]--) ans += 'a' + v[k];
				for (int x = k + 1; x < int(v.size()); x++) if (v[x] != i) while (cnt[v[x]]--) ans += 'a' + v[x];
				break;
			}
			cout << "YES" << endl << ans << endl;

		}
		else if (v.size() == 2) {
			if (cnt[i] >= n - 2) cout << "NO" << endl;
			else {
				for (int k = 0; k < (n >> 1); k++) ans += 'a' + i;
				cnt[i] -= n >> 1;
				for (int k = 0; k < int(v.size()); k++) if (v[k] != i) {
					ans += 'a' + v[k];
					cnt[v[k]]--;
					while (cnt[i]--) ans += 'a' + i;
					while (cnt[v[k]]--) ans += 'a' + v[k];
					for (int x = k + 1; x < int(v.size()); x++) if (v[x] != i) while (cnt[v[x]]--) ans += 'a' + v[x];
					break;
				}
				cout << "YES" << endl << ans << endl;

			}
		}
		else cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl << s << endl;
} 
