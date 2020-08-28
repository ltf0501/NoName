#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 20;
int cur[kN];
string s;
string GetString(int len) {
  string res = "";
  for (int i = 0; i < len; i++)
    res += char('0' + cur[i]);
  return res;
}
// n = length of key, k = number of different
// keys, m = number of characters
void Dfs(int n, int k, int m, int now, int last) {
  if (now && n % now == 0 && last == -1)
    s += GetString(now);
  if (int(s.length()) >= k + n - 1) return;
  if (now == n) return;
  if (now > 0) {
    cur[now] = cur[last + 1];
    Dfs(n, k, m, now + 1, last + 1);
  }
  for (int i = now ? cur[last + 1] + 1 : 0; i < m;
       i++) {
    cur[now] = i;
    Dfs(n, k, m, now + 1, -1);
  }
}
string Debrujin(int n, int k, int m) {
  Dfs(n, k, m, 0, -1);
  while (int(s.length()) < k + n - 1) s += s;
  return s.substr(0, k + n - 1);
}

int main() {
	freopen("infinite.in", "r", stdin);
	freopen("infinite.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	string c = Debrujin(n, (1 << n), 2);
	cout << c << '\n';
	return 0;
} 
