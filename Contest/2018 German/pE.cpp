#include <bits/stdc++.h>
using namespace std;

constexpr long double kEps = 1E-7;
constexpr int kC = 1.2E7;

bool not_prime[kC + 1];

bool IsInt(long double x) { return (abs(x - round(x)) < kEps); }

int main() {
  cin.tie(0), ios_base::sync_with_stdio(false);
  not_prime[1] = true;
  for (int i = 2; i <= kC; i++) {
    if (not_prime[i]) continue;
    for (int j = i + i; j <= kC; j += i) not_prime[j] = true;
  }
  int n;
  cin >> n;
  while (n--) {
    long double a, b;
    cin >> a >> b;
    a *= 100000, b *= 100000;
    // while (!IsInt(a) || !IsInt(b)) a *= 10, b *= 10;
    int64_t aa = round(a), bb = round(b), gg = __gcd(aa, bb);
    aa /= gg, bb /= gg;
    if (aa == 1 && bb == 1) aa = bb = 2;
    if (!not_prime[aa] && !not_prime[bb])
      cout << aa << ' ' << bb << '\n';
    else
      cout << "impossible\n";
  }
}
