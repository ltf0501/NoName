#include <bits/stdc++.h>
using namespace std;

int is_fib[1000010];
vector<pair<int, int>> a;

int main() {
  for (int i = 1, j = 1, k = 1; i <= 1000000; i++, k++) {
    is_fib[i] = k;
    tie(i, j) = make_pair(j, i + j);
  }
  int n;
  cin >> n;
  int last = -1;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (is_fib[x]) a.push_back({x, i});
  }
  sort(a.begin(), a.end());
  for (int i = 1; i < int(a.size()); i++) {
    if (a[i - 1].first == 1 && a[i].first == 1) {
      cout << a[i - 1].second + 1 << ' ' << a[i].second + 1 << '\n';
      return 0;
    }
    if (is_fib[a[i - 1].first] && is_fib[a[i].first] &&
        is_fib[a[i - 1].first] + 1 == is_fib[a[i].first]) {
      cout << a[i - 1].second + 1 << ' ' << a[i].second + 1 << '\n';
      return 0;
    }
  }
  cout << "impossible\n";
}
