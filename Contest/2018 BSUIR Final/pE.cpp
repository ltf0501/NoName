#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
typedef long long int ll;
constexpr int kMod = 998244353, kN = int(1E5 + 10), kNN = 512, kNNN = 1024,
              kNNNN = 2048;

ll Pow(ll a, ll b) {
  ll ans = 1;
  while (b) {
    if (b & 1) ans = (ans * a) % kMod;
    a = (a * a) % kMod;
    b >>= 1;
  }
  return ans;
}
ll Rev(ll n) { return Pow(n, kMod - 2); }
void Ntt(vector<ll> &v, bool on, int size) {
  ll wn, u, t, w, inv;
  for (int i = 1, j = size >> 1, k; i < (size - 1); i++) {
    if (i < j) swap(v[i], v[j]);
    k = size >> 1;
    while (j & k) {
      j ^= k;
      k >>= 1;
    }
    j |= k;
  }
  for (int i = 2; i <= size; i <<= 1) {
    wn = on ? Pow(3, (kMod - 1) / i) : Pow(3, kMod - 1 - (kMod - 1) / i);
    for (int j = 0; j < size; j += i) {
      w = 1;
      for (int k = j; k < j + (i >> 1); k++) {
        u = v[k];
        t = (w * v[k + (i >> 1)]) % kMod;
        v[k] = (u + t) % kMod;
        v[k + (i >> 1)] = (u - t + kMod) % kMod;
        w = (w * wn) % kMod;
      }
    }
  }
  if (on) {
    inv = Rev(size);
    for (int i = 0; i < size; i++) v[i] = (v[i] * inv) % kMod;
  }
  return;
}

int main() {
  int n, a[kN], b[kN], tmp, nsz = kNNN;
  vector<ll> v[kNN];
  ll ans = 0, inv = Pow(kNN, kMod - 2), now = 1;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
  for (int i = 0; i < kNN; i++) v[i].resize(kNNNN);
  for (int i = 1; i <= n; i++) v[b[i]][a[i]]++;
  auto fix = [](ll &x, ll &y) {
    x += y;
    y = x - (y << 1);
  };
  auto work = [&](int l, int r) {
    for (int i = 0; i < nsz; i++) fix(v[l][i], v[r][i]);
  };
  auto FWT = [&](bool inverse) {
    for (int i = 2; i <= kNN; i <<= 1)
      for (int j = 0; j < kNN; j += i)
        for (int k = j; k < j + (i >> 1); k++) work(k, k + (i >> 1));
    for (int i = 0; i < kNN; i++)
      for (int j = 0; j < nsz; j++)
        v[i][j] = (inverse ? (v[i][j] % kMod * inv) : v[i][j]) % kMod;
  };
  FWT(false);
  for (int i = 0; i < kNN; i++) Ntt(v[i], false, kNNNN);
  for (int i = 0; i < kNN; i++)
    for (int j = 0; j < kNNNN; j++) {
      v[i][j] = (v[i][j] * v[i][j]) % kMod;
      v[i][j] = (v[i][j] * v[i][j]) % kMod;
    }
  for (int i = 0; i < kNN; i++) Ntt(v[i], true, kNNNN);
  nsz <<= 1;
  FWT(true);
  for (int i = 0; i < kNNNN; i++) {
    now = 1;
    for (int j = 0; j < kNN; j++) {
      ans += v[j][i] * now % kMod;
      now = (now * i) % kMod;
    }
  }
  ans %= kMod;
  if (ans < 0) ans += kMod;
  printf("%lld", ans % kMod);
}
