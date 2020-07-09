#include <bits/stdc++.h>
using namespace std;
const int kN = 3e3 + 10;
const int kP[2] = {890501, 880301};
const int kMod = 1e9 + 7;

void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}

int n, m;
char s[kN][kN];

int fac[kN], pw[2][kN];
void init() {
	fac[0] = 1;
	for(int i = 1; i < kN; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;
	pw[0][0] = pw[1][0] = 1;
	for(int i = 1; i < kN; i++) 
		for(int j = 0; j < 2; j++) pw[j][i] = 1LL * pw[j][i - 1] * kP[j] % kMod;
}

int h[2][kN][kN];
vector<int> pos[kN];
void preprocess() {
	for(int o = 0; o < 2; o++) {
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				h[o][i][j + 1] = 1LL * h[o][i][j] * kP[o] % kMod;
				if(s[j][i] == '?') {
					if(o == 0) pos[i].push_back(j);
				}
				else h[o][i][j + 1] = (h[o][i][j + 1] + s[j][i]) % kMod;
			}
		}
	}
}

int Solve(int x) {
	unordered_map<int64_t, int> cnt[2];
	set<int64_t> hsh;

	for(int i = 0; i < m; i++) {
		int64_t tot_pre = 0, tot_suf = 0;
		for(int o = 0; o < 2; o++) {
			int pre = h[o][i][n - 1];
			int suf = (h[o][i][n] - 1LL * h[o][i][1] * pw[o][n - 1] % kMod) % kMod;
			if(suf < 0) suf += kMod;

			for(int id : pos[i]) {
				if(id < n - 1) add(pre, 1LL * x * pw[o][n - 2 - id] % kMod);
				if(id > 0) add(suf, 1LL * x * pw[o][n - 1 - id] % kMod); 
			}

			tot_pre = tot_pre * kMod + pre, tot_suf = tot_suf * kMod + suf;
		}
		cnt[0][tot_pre]++, cnt[1][tot_suf]++;
		hsh.insert(tot_pre);
	}

	int ans = 1;
	for(int64_t x : hsh) {
		if(cnt[1].find(x) == cnt[1].end() || cnt[0][x] != cnt[1][x]) return 0;
		ans = 1LL * ans * fac[cnt[0][x]] % kMod;
	}
	return ans;
}
int main() {
	scanf("%d%d", &n, &m);
	init();
	vector<int> cnt(130);
	for(int i = 0; i < n; i++) {
		scanf("%s", s[i]);
		vector<int> tmp(130);
		for(int j = 0; j < m; j++) tmp[s[i][j]]++;
		for(int i = 33; i <= 126; i++) cnt[i] = max(cnt[i], tmp[i]);
	}

	int tot = 0;
	for(int i = 33; i <= 126; i++) 
		if(i != 63) tot += cnt[i];
	cnt[63] = 0;

	//printf("tot = %d\n", tot);
	if(tot == m) {
		for(int i = 0; i < n; i++) {
			auto tmp = cnt;
			for(int j = 0; j < m; j++)
				if(s[i][j] != '?') tmp[s[i][j]]--;

			for(int j = 0; j < m; j++) if(s[i][j] == '?') {
				for(int k = 33; k <= 126; k++)
					if(tmp[k] != 0) s[i][j] = k;
			}
		}
	}

	//for(int i = 0; i < n; i++) printf("%s\n", s[i]);
	preprocess();

	int good = Solve(63);
	//printf("good = %d\n", good);
	int ans = good;
	for(int i = 33; i <= 126; i++) {
		if(i != '?') {
			int tmp = Solve(i) - good;
			tmp %= kMod;
			if(tmp < 0) tmp += kMod;
			add(ans, tmp);
		}
	}
	printf("%d\n", ans);
} 
