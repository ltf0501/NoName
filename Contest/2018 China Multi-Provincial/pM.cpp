#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
typedef complex<double> cp;
const int maxn = 131072;
struct FFT {
  int n, rev[maxn];
  cp omega[maxn], iomega[maxn];
  void init(int n) {
    this->n = n;
    for (int i = 0; i < n; i++) {
      omega[i] = cp(cos(2 * pi / n * i), sin(2 * pi / n * i));
      iomega[i] = conj(omega[i]);
    }
    int k = log2(n);
    for (int i = 0; i < n; i++) {
      int t = 0;
      for (int j = 0; j < k; j++)
        if (i & (1 << j)) t |= (1 << (k - j - 1));
      rev[i] = t;
    }
  }
  void transform(vector<cp>& a, cp* omega) {
    for (int i = 0; i < n; i++)
      if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int len = 2; len <= n; len <<= 1) {
      int mid = len >> 1;
      for (int j = 0; j < n; j += len)
        for (int i = 0; i < mid; i++) {
          cp t = omega[n / len * i] * a[j + mid + i];
          a[j + mid + i] = a[j + i] - t;
          a[j + i] += t;
        }
    }
  }
  void fft(vector<cp>& a) { transform(a, omega); }
  void ifft(vector<cp>& a) {
    transform(a, iomega);
    for (int i = 0; i < n; i++) a[i] /= n;
  }
};
vector<int> conv(const vector<int>& a, const vector<int>& b, int p) {
  int sz = 1;
  while (sz < int(a.size()) + int(b.size()) - 1) sz <<= 1;
  vector<cp> fa(sz), fb(sz);
  for (int i = 0; i < int(a.size()); ++i)
    fa[i] = cp(a[i] & ((1 << 15) - 1), a[i] >> 15);
  for (int i = 0; i < int(b.size()); ++i)
    fb[i] = cp(b[i] & ((1 << 15) - 1), b[i] >> 15);

  FFT solver;
  solver.init(sz);
  solver.fft(fa), solver.fft(fb);
  double r = 0.25 / sz;
  cp r2(0, -1), r3(r, 0), r4(0, -r), r5(0, 1);
  for (int i = 0; i <= (sz >> 1); ++i) {
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
  solver.fft(fa), solver.fft(fb);
  vector<int> res(sz);
  for (int i = 0; i < sz; ++i) {
    long long a = round(fa[i].real());
    long long b = round(fb[i].real());
    long long c = round(fa[i].imag());
    res[i] = (a + ((b % p) << 15) + ((c % p) << 30)) % p;
  }
  return res;
}
int pw(int a, int n, int p) {
  int res = 1;
  while (n) {
    if (n & 1) res = 1LL * res * a % p;
    n >>= 1, a = 1LL * a * a % p;
  }
  return res;
}
int n, m, p;
int INV(int a, int p) { return pw(a, p - 2, p); }
int fac[maxn], inv[maxn];
void pre() {
  int sz = max(n, m) + 5;
  fac[0] = 1;
  for (int i = 1; i <= sz; i++) fac[i] = 1LL * fac[i - 1] * i % p;
  inv[sz] = INV(fac[sz], p);
  for (int i = sz - 1; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % p;
}
vector<int> GetStirling(int n) {
  vector<int> a(n + 1), b(n + 1);
  for (int i = 0, c = 1; i <= n; i++, c = p - c) {
    a[i] = 1LL * c * inv[i] % p;
    b[i] = 1LL * pw(i, n, p) * inv[i] % p;
  }
  return conv(a, b, p);
}

int main() {
  int T;
  scanf("%d", &T);
  int cas = 0;
  while (T--) {
    scanf("%d%d%d", &n, &m, &p);
    printf("Case #%d: ", ++cas);
    pre();
    vector<int> s1 = GetStirling(n + 1);
    vector<int> s2 = GetStirling(m + 1);

    int ans = 0;
    for (int i = 1; i <= min(n, m) + 1; i++)
      ans =
          (ans + 1LL * fac[i - 1] * fac[i - 1] % p * s1[i] % p * s2[i] % p) % p;

    printf("%d\n", ans);
  }
  return 0;
}
