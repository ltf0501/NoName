#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

long double val[N];
int a[N], l[N];
bool f[N];

int main() {
  int n, last, cnt = 0;
  long double temp = 0;
  string s;
  cin >> n;
  n <<= 1;
  last = n;
  l[0] = 0;
  for (int i = 1; i <= n; i++) {
    cin >> s >> a[i];
    if (s[0] == '+')
      f[i] = true;
    else
      f[i] = false;
  }
  for (int i = 1; i <= n; i++)
    if (f[i])
      l[i] = l[i - 1] + 1;
    else
      l[i] = l[i - 1] - 1;
  for (int i = n; i >= 2; i--)
    if (f[i] != f[i - 1]) {
      if (f[i]) {
        last = i;
        cnt = 0;
      } else {
        cnt++;
        temp += a[i];
        if (last == n) {
          val[i - 1] = temp / l[i - 1];
          temp = 0;
        } else {
          val[i - 1] = (val[last] * (l[i - 1] - cnt)) / l[i - 1];
          val[i - 1] += temp / l[i - 1];
          temp = 0;
        }
        cnt = 0;
      }
    } else {
      if (!f[i]) {
        cnt++;
        temp += a[i];
      } else
        val[i - 1] = val[i];
    }

  for (int i = 1; i <= n; i++)
    if (f[i]) cout << fixed << setprecision(20) << val[i] - a[i] << endl;
}
