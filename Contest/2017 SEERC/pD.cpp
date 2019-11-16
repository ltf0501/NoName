#include <bits/stdc++.h>
using namespace std;

int cc, par[100010];
vector<int> g[100010];

int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

void join(int a, int b) {
  int pa = find(a), pb = find(b);
  if (pa != pb) {
    par[pa] = pb;
    cc--;
  }
}

int main() {
  cin.tie(nullptr), ios_base::sync_with_stdio(false);
  int n, m;
  cin >> m >> n;
  cc = m;
  for (int i = 0; i <= max(n, m); i++) par[i] = i;
  for (int i = 0; i < m; i++) {
    int c;
    cin >> c;
    for (int j = 0; j < c; j++) {
      int x;
      cin >> x;
      g[x].push_back(i);
    }
  }
  for (int i = 0; i < max(n, m); i++) {
    for (auto x : g[i]) {
      for (auto y : g[i]) {
        if (x != y) join(x, y);
      }
    }
  }
  cout << m - cc << '\n';
}
