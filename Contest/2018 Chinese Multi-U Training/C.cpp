#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;

int mu[kN], phi[kN];
vector<int> fac[kN];
void pre() {
	mu[1] = 1;
	for(int i = 1; i < kN; i++) phi[i] = i;
	for(int i = 1; i < kN; i++) {
		for(int j = i; j < kN; j += i) {
			if(j != i) mu[j] -= mu[i], phi[j] -= phi[i];
			fac[j].push_back(i);
		}
	}
	//for(int i = 1; i <= 50; i++) printf("%d: mu = %d, phi = %d\n", i, mu[i], phi[i]);
}

vector<int> Psi(int n) {
	if(n == 1) return {-1, 1};
	vector<int> res(phi[n] + 1, 0);
	res[0] = 1;
	for(int d : fac[n]) {
		if(mu[n / d] > 0) {
			for(int i = phi[n]; i >= d; i--) res[i] -= res[i - d];
		}
		else if(mu[n / d] < 0) {
			for(int i = d; i <= phi[n]; i++) res[i] += res[i - d];
		}
	}
	//for(int x : res) printf("%d ", x); puts("");
	return res;
}

void print(const vector<int> &p) {
	putchar('(');
	for(int i = int(p.size()) - 1; i >= 0; i--) {
		if(p[i] == 0) continue;
		if(abs(p[i]) > 1) {
			if(p[i] > 0 && i != int(p.size()) - 1) putchar('+');
			else if(p[i] < 0) putchar('-');
			printf("%d", abs(p[i]));
		}
		else {
			if(p[i] > 0 && i != int(p.size()) - 1) putchar('+');
			else if(p[i] < 0) putchar('-'); 
			if(i == 0) putchar('1');
		} 
		if(i > 1) printf("x^%d", i);
		else if(i == 1) printf("x");
	}
	putchar(')');
}
int main() {
	pre();
	int T; scanf("%d", &T);
	while(T--) {
		int n; scanf("%d", &n);
		vector<vector<int>> ans;
		for(int d : fac[n]) ans.push_back(Psi(d));
		sort(ans.begin(), ans.end(), [&](const vector<int> &a, const vector<int> &b) {
				if(a.size() != b.size()) return a.size() < b.size();
				for(int i = int(a.size()) - 1; i >= 0; i--)
					if(a[i] != b[i]) return a[i] < b[i];
					return false;
				});

		for(auto p : ans) print(p); puts("");
	}
	return 0;
} 
