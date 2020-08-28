#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kMod = 1e7 + 7;
const int kN = 1e6 + 10;

vector<int> pr;
bool notp[kN];

void pre() {
	for(int i = 2; i < kN; i++) {
		if(!notp[i]) pr.push_back(i);
		for(int j = 0; j < int(pr.size()) && 1LL * i * pr[j] < kN; j++) {
			notp[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
ll Cal(int p, int n) {
	ll res = 0;
	while(n) {
		res += n / p;
		n /= p;
	}
	return res;
}
int main() {
	pre();
	int n;
	while(~scanf("%d", &n) && n) {
		int ans = 1;
		for(int i = 0; i < int(pr.size()) && pr[i] <= n; i++) {
			int p = pr[i];
			ll tmp = Cal(p, n);
			tmp = 1LL * (tmp + 1) * (tmp + 2) / 2;
			tmp %= kMod;
			ans = 1LL * ans * tmp % kMod; 
		}
		printf("%d\n", ans);
	}
	return 0;
}

