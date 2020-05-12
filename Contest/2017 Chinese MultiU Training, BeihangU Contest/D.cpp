#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1 << 19, kMod = 985661441;

int Pw(int a, int n) {
	if(!n) return 1;
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}
int Inv(int a) {return Pw(a, kMod - 2);}
struct NTT {
	int n, invn, rev[kN];
	int g;
	int omega[kN], iomega[kN];
	void init(int n, int g) {
		this->n = n, this->g = g;
		invn = Inv(n);
		int k = __lg(n);
		int x = Pw(g, (kMod - 1) / n);
		omega[0] = 1;
		for (int i = 1; i < n; i++) {
			omega[i] = 1LL * omega[i - 1] * x % kMod;
		}
		iomega[n - 1] = Inv(omega[n - 1]);
		for (int i = n - 2; i >= 0; i--) {
			iomega[i] = 1LL * iomega[i + 1] * x % kMod;
		}
		for (int i = 0; i < n; i++) {
			int t = 0;
			for (int j = 0; j < k; j++) {
				if (i & (1 << j)) t |= 1 << (k - j - 1);
			}
			rev[i] = t;
		}
	}
	void transform(vector<int> &a, int *omega) {
		for (int i = 0; i < n; i++) {
			if (i < rev[i]) swap(a[i], a[rev[i]]);
		}
		for (int len = 2; len <= n; len <<= 1) {
			int mid = len >> 1;
			int r = n / len;
			for (int j = 0; j < n; j += len) {
				for (int i = 0; i < mid; i++) {
					int t = 1LL * omega[r * i] * a[j + mid + i] % kMod;
					a[j + mid + i] = a[j + i] - t;
					if (a[j + mid + i] < 0) {
						a[j + mid + i] += kMod;
					}
					a[j + i] += t;
					if (a[j + i] >= kMod) a[j + i] -= kMod;
				}
			}
		}
	}
	void dft(vector<int> &a) { transform(a, omega); }
	void idft(vector<int> &a) {
		transform(a, iomega);
		for (int i = 0; i < n; i++) {
			a[i] = 1LL * a[i] * invn % kMod;
		}
	}
};

//int find_primitive() {
//	int a[3] = {2, 5, 47};
//	for(int i = 2;; i++) {
//		if(Pw(i, (kMod - 1) / 2) != 1 && Pw(i, (kMod - 1) / 5) != 1 && Pw(i, (kMod - 1) / 47) != 1) return i;
//	}
//}

vector<int> mul(vector<int> a, vector<int> b) {
	int n = 1;
	int n1 = int(a.size()), n2 = int(b.size());
	while (n < n1 + n2 - 1)  n <<= 1;
	a.resize(n);
	b.resize(n);
	NTT solver;
	solver.init(n, 3);
	solver.dft(a);
	solver.dft(b);
	for (int i = 0; i < n; i++) {
		a[i] = 1LL * a[i] * b[i] % kMod;
	}
	solver.idft(a);
	while (!a.empty() && a.back() == 0) a.pop_back();
	return a;
}

int fac[kN], invf[kN];
void pre() {
	fac[0] = 1;
	for(int i = 1; i < kN; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;
	invf[kN - 1] = Inv(fac[kN - 1]);
	for(int i = kN - 2; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % kMod;
}
int C(int n, int m) {
	if(n < m) return 0;
	return 1LL * fac[n] * invf[m] % kMod * invf[n - m] % kMod;
}

int e[15];
void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}
int main() {
	pre();
	int m, k;
	int cas = 0;
	while(~scanf("%d%d", &m, &k)) {
		int tot = 0;
		for(int i = 1; i <= m; i++) {
			int p;
			scanf("%d%d", &p, &e[i]);
			tot += e[i];
		} 

		vector<int> g;
		g.push_back(0);

		for(int x = 1; x <= tot; x++) {
			int tmp = 1;
			for(int i = 1; i <= m; i++) tmp = 1LL * tmp * C(e[i] + x - 1, e[i]) % kMod;
			g.push_back(tmp);	
		}
		vector<int> a, b;
		int flag = 1;
		for(int x = 0; x <= tot; x++) {
			a.push_back(1LL * g[x] * invf[x] % kMod);	
			int tmp = flag * invf[x]; 
			if(tmp < 0) tmp += kMod;
			b.push_back(tmp);
			flag = -flag;
		}

		vector<int> f = mul(a, b);
		for(int i = 0; i <= tot; i++) f[i] = 1LL * f[i] * fac[i] % kMod;
		f[tot + 1] = 0;

		printf("Case #%d: ", ++cas);
		for(int i = 1; i <= k; i++) {
			int ans = 0;
			for(int x = 1; x <= tot; x++) {
				add(ans, 1LL * Pw(f[x], k - i + 1) * Pw(f[x + 1], i - 1) % kMod);
			}
			printf("%d ", ans);
		}
		puts("");
	}

	return 0;
} 
