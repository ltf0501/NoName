#include <bits/stdc++.h>
using namespace std;

constexpr int kMod = 998244353;
const int kN = 4e6 + 10;
int64_t Pow(int64_t x, int e) {
	if (!e) return 1;
	auto t = Pow(x * x % kMod, e >> 1);
	return (e & 1) ? (t * x % kMod) : t;
}

int64_t Inv(int x) { return Pow(x, kMod - 2); }

struct NTT {
	int n, invn, rev[kN];
	int g;
	int omega[kN], iomega[kN];
	void init(int n, int g) {
		this->n = n, this->g = g;
		invn = Inv(n);
		int k = log2(n);
		int x = Pow(g, (kMod - 1) / n);
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
				if (i & (1 << j)) t |= (1 << (k - j - 1));
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
					if (a[j + mid + i] < 0) a[j + mid + i] += kMod;
					a[j + i] += t;
					if (a[j + i] >= kMod) a[j + i] -= kMod;
				}
			}
		}
	}
	void dft(vector<int> &a) { transform(a, omega); }
	void idft(vector<int> &a) {
		transform(a, iomega);
		for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * invn % kMod;
	}
};

NTT solver;
vector<int> mul(vector<int> a, vector<int> b) {
	//printf("a: ");
	//for(int x : a) printf("%d ", x); puts("");
	//printf("b: ");
	//for(int x : b) printf("%d ", x); puts("");
	int n = 1;
	int n1 = int(a.size()), n2 = int(b.size());
	while (n < n1 + n2 - 1) n <<= 1;
	a.resize(n), b.resize(n);
	solver.init(n, 3);
	solver.dft(a), solver.dft(b);
	for (int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % kMod;
	solver.idft(a);
	while (!a.empty() && a.back() == 0) a.pop_back();
	return a;
}

int S[kN];
set<int> V, v;
int p;
vector<int> fac;
void pre() {
	int P = p - 1;
	for(int i = 2; 1LL * i * i <= P; i++) if(P % i == 0) {
		fac.push_back(i);
		while(P % i == 0) P /= i;
	}
	if(P != 1) fac.push_back(P);
}
int fpow(int x, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * x % p;
		x = 1LL * x * x % p, n >>= 1;
	}
	return res;
}
int inv(int x) {return fpow(x, p - 2);}
int f(int x) {
	if((3 * x + 1) % p == 0 || (3 * x + 2) % p == 0) return -1;
	int a = (1LL * (2 * x + 3) * (2 * x + 3) % p + 5LL * x * x % p) % p;
	int b = 1LL * (3 * x + 1) * (3 * x + 1) % p; 
	int c = (1LL * (2 * x + 5) * (2 * x + 5) % p + 3) % p;
	int d = 1LL * (3 * x + 2) * (3 * x + 2) % p;
	return (1LL * a * inv(b) % p + 1LL * c * inv(d) % p) % p;
}

bool test(int g) {
	//printf("test: %d\n", g);
	for(auto pp : fac)
		if(fpow(g, (p - 1) / pp) == 1) return 0;
	return 1;
}
int PrimitiveRoot(int p) {
	for(int g = 2;; g++)
		if(test(g)) return g;
}
int main() { 
	scanf("%d", &p);
	pre();
	int n, m;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		S[x]++;
	}
	scanf("%d", &m);
	for(int i = 0; i < m; i++) {
		int x; scanf("%d", &x);
		V.insert(x);
	}
	for(int i = 1; i < p; i++) 
		if(V.find(f(i)) != V.end()) v.insert(i);

	//printf("v: ");
	//for(int x : v) printf("%d ", x); puts("");

	int g = PrimitiveRoot(p);
	//printf("g = %d\n", g);
	vector<int> vv(p - 1), ss(p - 1);
	for(int i = 0, cur = 1; i < p - 1; i++, cur = 1LL * cur * g % p) {
		if(v.find(cur) != v.end()) vv[i] = 1;
		else vv[i] = 0;

		ss[i] = S[cur];	
	}
	//printf("ss: ");
	//for(int x : ss) printf("%d ", x); puts("");
	//printf("vv: ");
	//for(int x : vv) printf("%d ", x); puts("");

	vector<int> res = mul(ss, vv);

	//printf("res: ");
	//for(int x : res) printf("%d ", x); puts("");
	int64_t ans = 0;
	for(int i = 0; i < int(res.size()); i++) {
		ans += 1LL * res[i] * ss[i % (p - 1)];
	}
	//printf("V: ");
	//for(int x : V) printf("%d ", x); puts("");

	if(S[0]) {
		if(p != 2 && V.find(16 % p) != V.end()) { //a = 0
			//printf("a can be 0\n");
			for(int i = 0; i < p; i++)
				if(i % p != 0) ans += S[i];
		}
		if(p != 3 && V.find(13LL * inv(9) % p) != V.end()) { // b = 0
			//printf("b can be 0\n");
			for(int i = 0; i < p; i++)
				if(i % p != 0) ans += S[i];
		}
	}
	printf("%lld\n", ans);
	return 0;
} 
