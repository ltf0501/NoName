#include <bits/stdc++.h>
using namespace std;
const int kMod = 1e9 + 7;
const int kN = 1e5 + 10;

string s[kN];
int cnt[26][kN];
int a[26];
bool not0[26];

int r[26];

void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}
int main() {
	int n;
	int cas = 0;
	while(cin >> n) { 
		memset(not0, 0, sizeof(not0));
		memset(cnt, 0, sizeof(cnt));
		
		for(int i = 0; i < n; i++) {
			cin >> s[i];
			int sz = int(s[i].size());
			for(int j = 0; j < sz; j++) {
				cnt[s[i][j] - 'a'][sz - j - 1]++;
			}
			if(sz > 1) not0[s[i][0] - 'a'] = 1;
		} 

		for(int i = 0; i < 26; i++) {
			for(int j = 0; j < kN - 1; j++) {
				cnt[i][j + 1] += cnt[i][j] / 26;
				cnt[i][j] %= 26;
			}
		}

		for(int i = 0; i < 26; i++) r[i] = i;	
		sort(r, r + 26, [&](int x, int y) {
					for(int i = kN - 1; i >= 0; i--) {
						if(cnt[x][i] != cnt[y][i]) return cnt[x][i] > cnt[y][i];	
					}
					return false;
				}); 

		int id;
		for(int i = 25; i >= 0; i--)
			if(!not0[r[i]]) {id = r[i]; break;}

		int now = 25;
		for(int i = 0; i < 26; i++) {
			if(r[i] == id) a[r[i]] = 0;
			else a[r[i]] = now--;
		}

		int ans = 0;
		for(int i = 0; i < 26; i++) {
			int b = 1;
			for(int j = 0; j < kN; j++) {
				add(ans, 1LL * b * cnt[i][j] % kMod * a[i] % kMod);
				b = 1LL * b * 26 % kMod;
			}
		}
		cout << "Case #" << ++cas << ": " << ans << '\n';

	}

	return 0;
} 
