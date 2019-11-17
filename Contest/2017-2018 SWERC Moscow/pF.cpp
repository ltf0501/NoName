#include <bits/stdc++.h>
using namespace std;

int main() {
  int ll;
  cin >> ll;
  int n;
  cin >> n;
  int64_t area = 0;
  for (int i = 0; i < n; i++) {
    int64_t w, l;
    cin >> w >> l;
    area += w * l;
  }
  cout << area / ll << '\n';
}
