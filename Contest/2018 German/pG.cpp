#include <bits/stdc++.h>
using namespace std;

using LD = long double;
using Pos = tuple<LD, LD, LD>;
using Vec = Pos;

constexpr LD kPi = 4 * atan(1), kR = 6371, kC = 299792.458, kEps = 1E-8;

LD Dist(Pos a, Pos b) {
  auto d0 = get<0>(a) - get<0>(b);
  auto d1 = get<1>(a) - get<1>(b);
  auto d2 = get<2>(a) - get<2>(b);
  return sqrt(d0 * d0 + d1 * d1 + d2 * d2);
}

void Print(Pos p) {
  cerr << get<0>(p) << ' ' << get<1>(p) << ' ' << get<2>(p) << '\n';
}

int main() {
  cin.tie(nullptr), ios_base::sync_with_stdio(false);
  int s;
  cin >> s;
  LD lo, la;
  cin >> lo >> la;
  lo = lo / 180 * kPi;
  la = la / 180 * kPi;
  Pos pos = {kR * cos(la) * cos(lo), kR * sin(lo) * cos(la), kR * sin(la)};
  Print(pos);
  Pos oo = {0, 0, 0};
  while (s--) {
    LD phi, psi, r, x;
    cin >> phi >> psi >> r >> x;
    phi = phi / 180 * kPi;
    psi = psi / 180 * kPi;
    LD angle = 2 * kPi * x;
    Pos sat = {r * cos(angle), r * sin(angle) * cos(psi),
               r * sin(angle) * sin(psi)};
    auto tmp = make_pair(get<0>(sat) * cos(phi) - get<1>(sat) * sin(phi),
                         get<0>(sat) * sin(phi) + get<1>(sat) * cos(phi));
    get<0>(sat) = tmp.first, get<1>(sat) = tmp.second;

    Print(sat);
    LD asf = get<0>(pos) * get<0>(sat) + get<1>(pos) * get<1>(sat) +
             get<2>(pos) * get<2>(sat) - get<0>(pos) * get<0>(pos) -
             get<1>(pos) * get<1>(pos) - get<2>(pos) * get<2>(pos);
    if (asf < -kEps) {
      cout << "no signal\n";
    } else {
      cout << fixed << setprecision(20) << Dist(pos, sat) / kC << '\n';
    }
  }
}
