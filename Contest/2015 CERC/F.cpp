#include <bits/stdc++.h>
using namespace std;

constexpr double kPi = acos(-1);
typedef complex<double> cp;

constexpr int kN = (1 << 22);
constexpr int kMod = 1e6 + 3;

struct FFT {
	int n, rev[kN];
	cp omega[kN], iomega[kN];
	void Init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) {
			omega[i] = cp(cos(2 * kPi / n * i), sin(2 * kPi / n * i));
			iomega[i] = conj(omega[i]);
		}
		int k = log2(n);
		for (int i = 0; i < n; i++) {
			int t = 0;
			for (int j = 0; j < k; j++) {
				if (i & (1 << j)) t |= (1 << (k - j - 1));
			}
			rev[i] = t;
		}
	}
	void Transform(vector<cp> &a, cp *omega) {
		for (int i = 0; i < n; i++) {
			if (i < rev[i]) swap(a[i], a[rev[i]]);
		}
		for (int len = 2; len <= n; len <<= 1) {
			int mid = len >> 1;
			int r =  n / len;
			for (int j = 0; j < n; j += len) {
				for (int i = 0; i < mid; i++) {
					cp t = omega[r * i] * a[j + mid + i];
					a[j + mid + i] = a[j + i] - t;
					a[j + i] += t;
				}
			}
		}
	}
	void Fft(vector<cp> &a) {
		Transform(a, omega);
	}
	void Ifft(vector<cp> &a) {
		Transform(a, iomega);
		for (int i = 0; i < n; i++) a[i] /= n;
	}
};
vector<int> Conv(const vector<int> &a, const vector<int> &b, int p) {
	int sz = 1;
	while (sz < int(a.size() + b.size() - 1)) sz <<= 1;
	vector<cp> fa(sz), fb(sz);
	for (int i = 0; i < int(a.size()); i++) {
		fa[i] = cp(a[i] & ((1 << 15) - 1), a[i] >> 15);
	}
	for (int i = 0; i < int(b.size()); i++) {
		fb[i] = cp(b[i] & ((1 << 15) - 1), b[i] >> 15);
	}
	FFT solver;
	solver.Init(sz);
	solver.Fft(fa);
	solver.Fft(fb);
	double r = 0.25 / sz;
	cp r2(0, -1), r3(r, 0), r4(0, -r), r5(0, 1);
	for (int i = 0; i <= (sz >> 1); i++) {
		int j = (sz - i) & (sz - 1);
		cp a1 = (fa[i] + conj(fa[j]));
		cp a2 = (fa[i] - conj(fa[j])) * r2;
		cp b1 = (fb[i] + conj(fb[j])) * r3;
		cp b2 = (fb[i] - conj(fb[j])) * r4;
		if (i != j) {
			cp c1 = (fa[j] + conj(fa[i]));
			cp c2 = (fa[j] - conj(fa[i])) * r2;
			cp d1 = (fb[j] + conj(fb[i])) * r3;
			cp d2 = (fb[j] - conj(fb[i])) * r4;
			fa[i] = c1 * d1 + c2 * d2 * r5;
			fb[i] = c1 * d2 + c2 * d1;
		}
		fa[j] = a1 * b1 + a2 * b2 * r5;
		fb[j] = a1 * b2 + a2 * b1;
	}
	solver.Fft(fa);
	solver.Fft(fb);
	vector<int> res(sz);
	for (int i = 0; i < sz; i++) {
		int64_t a = round(fa[i].real());
		int64_t b = round(fb[i].real());
		int64_t c = round(fa[i].imag());
		res[i] = (a + ((b % p) << 15) + ((c % p) << 30)) % p;
	}
	return res;
}

int n, a, b, c;
int a_pow[kN], b_pow[kN];
int x[kN], y[kN];
int fac[kN], invf[kN];
int fpow(int x, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * x % kMod;
		x = 1LL * x * x % kMod, n >>= 1;
	}
	return res;
}
int Inv(int x) {return fpow(x, kMod - 2);}
void pre() {
	const int N = 1e6;
	fac[0] = 1;
	for(int i = 1; i < N; i++) fac[i] = 1LL * fac[i - 1] * i % kMod;
	invf[N - 1] = Inv(fac[N - 1]);
	for(int i = N - 2; i >= 0; i--) invf[i] = 1LL * invf[i + 1] * (i + 1) % kMod;

	a_pow[0] = b_pow[0] = 1;
	for(int i = 1; i < N; i++) {
		a_pow[i] = 1LL * a_pow[i - 1] * a % kMod;
		b_pow[i] = 1LL * b_pow[i - 1] * b % kMod;
	}
}

int C(int n, int m) {
	if(n < m) return 0;
	return 1LL * fac[n] * invf[m] % kMod * invf[n - m] % kMod;
}

void add(int &a, int b) {
	a += b;
	if(a >= kMod) a -= kMod;
}

int main() {
	scanf("%d%d%d%d", &n, &a, &b, &c);
	for(int i = 1; i <= n; i++) scanf("%d", &x[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &y[i]);

	pre();
	int ans = 0;
	vector<int> A(n - 1), B(n - 1);
	for(int i = 0; i <= n - 2; i++) {
		A[i] = 1LL * a_pow[i] * invf[i] % kMod;
		B[i] = 1LL * b_pow[i] * invf[i] % kMod;
	}

	//int tmp = 0;
	//for(int i = 0; i < n - 1; i++) {
	//	for(int j = 0; j < n - 1; j++) {
	//		add(tmp, 1LL * a_pow[i] * b_pow[j] % kMod * C(i + j, j) % kMod);
	//		printf("i = %d, j = %d\n", i, j);
	//		printf("a^i * b^j * C(i + j, j) = %d\n", 1LL * a_pow[i] * b_pow[j] % kMod * C(i + j, j) % kMod);
	//	}
	//}
	//printf("tmp = %d\n", tmp);

	//printf("A: ");
	//for(int x : A) printf("%d ", x); puts("");
	//printf("B: ");
	//for(int x : B) printf("%d ", x); puts("");

	vector<int> res = Conv(A, B, kMod);
	//printf("res: ");
	//for(int x : res) printf("%d ", x); puts("");

	for(int i = 0; i <= 2 * n - 4; i++) {
		add(ans, 1LL * fac[i] * res[i] % kMod);
	}
	//printf("%d\n", ans);
	ans = 1LL * ans * c % kMod;

	for(int i = 2; i <= n; i++) {
		add(ans, 1LL * C(2 * n - i - 2, n - i) * a_pow[n - 1] % kMod * b_pow[n - i] % kMod * x[i] % kMod);
	}
	for(int i = 2; i <= n; i++) {
		add(ans, 1LL * C(2 * n - i - 2, n - i) * a_pow[n - i] % kMod * b_pow[n - 1] % kMod * y[i] % kMod);
	}
	printf("%d\n", ans);
	return 0;
} 
