#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1010, kM = 5010;

string line[kN * 2];
vector<int> exit_ldr[kN];
int n, m, sum[kN][kM], dp[kN][11][11], ldr_l[kN][11], ldr_r[kN][11],
    ldr_ul[kN][11], ldr_ur[kN][11];

int range(int lvl, int l, int r) {
  // cerr << lvl << ' ' << l << ' ' << r << '\n';
  if (l > r) swap(l, r);
  return sum[lvl][r + 1] - sum[lvl][l];
}

int cal(int lvl, vector<pair<int, int>> &v) {
  sort(v.begin(), v.end());
  pair<int, int> last = {-100, -100};
  int ans = 0;
  // cerr << "---";
  // for (auto p : v) cerr << p.first << '/' << p.second << ' ';
  // cerr << "---\n";
  for (auto p : v) {
    if (p.first > last.second + 1) {
      if (last.first >= 0) ans += range(lvl, last.first, last.second);
      last = {p.first, p.second};
    } else {
      last.second = max(last.second, p.second);
    }
  }
  if (last.first >= 0) ans += range(lvl, last.first, last.second);
  // cerr << "------: " << ans << '\n';
  return ans;
}

int dfs(int lvl, int l, int r) {
  if (lvl == n) return 0;
  if (dp[lvl][l][r] != -1) return dp[lvl][l][r];
  auto insert = [](int x, vector<pair<int, int>> &v) {
    if (x != -1) v.emplace_back(x, x);
  };
  {
    // cerr << lvl << '-' << l << '-' << r << '\n';
    vector<pair<int, int>> v = {
        minmax(exit_ldr[lvl - 1][l], exit_ldr[lvl - 1][r])};
    insert(ldr_ul[lvl][l], v), insert(ldr_ur[lvl][r], v);
    dp[lvl][l][r] = cal(lvl, v);
  }
  for (int nl = 0; nl < int(exit_ldr[lvl].size()); nl++) {
    for (int nr = nl; nr < int(exit_ldr[lvl].size()); nr++) {
      if (nl == nr && line[lvl << 1][exit_ldr[lvl][nl]] != '-') continue;
      auto nl_i = exit_ldr[lvl][nl], nr_i = exit_ldr[lvl][nr],
           l_i = exit_ldr[lvl - 1][l], r_i = exit_ldr[lvl - 1][r];
      vector<pair<int, int>> v = {minmax(nl_i, l_i), minmax(nr_i, r_i)};
      int check_l = max(v[0].first, v[1].first),
          check_r = min(v[0].second, v[1].second);
      if (check_l <= check_r && range(lvl, check_l, check_r) > 0) continue;
      if (nl_i > l_i)
        insert(ldr_ul[lvl][l], v), insert(ldr_r[lvl][nl], v);
      else
        insert(ldr_ur[lvl][l], v), insert(ldr_l[lvl][nl], v);
      if (nr_i > r_i)
        insert(ldr_ul[lvl][r], v), insert(ldr_r[lvl][nr], v);
      else
        insert(ldr_ur[lvl][r], v), insert(ldr_l[lvl][nr], v);
      // cerr << nl << '-' << nr << '\n';
      dp[lvl][l][r] = max(dp[lvl][l][r], cal(lvl, v) + dfs(lvl + 1, nl, nr));
    }
  }
  return dp[lvl][l][r];
}

int main() {
  cin.tie(nullptr), ios_base::sync_with_stdio(false);
  memset(dp, -1, sizeof(dp));
  cin >> n >> m >> ws;
  for (int i = 0; i < (n << 1); i++) getline(cin, line[i]);
  for (int i = 0; i < n; i++) {
    int cur_line = i << 1, last_candy = -1;
    for (int j = 0, k = 0; j < m; j++) {
      if (line[cur_line][j] != '-') last_candy = j;
      if (line[cur_line + 1][j] == '|') {
        ldr_l[i][exit_ldr[i].size()] = last_candy;
        exit_ldr[i].push_back(j);
      }
      if (i && line[cur_line - 1][j] == '|') ldr_ul[i][k++] = last_candy;
    }
    last_candy = -1;
    int ldr_idx = int(exit_ldr[i].size()),
        ldru_idx = i ? int(exit_ldr[i - 1].size()) : 0;
    for (int j = m - 1; j >= 0; j--) {
      if (line[cur_line][j] != '-') last_candy = j;
      if (line[cur_line + 1][j] == '|') ldr_r[i][--ldr_idx] = last_candy;
      if (i && line[cur_line - 1][j] == '|') ldr_ur[i][--ldru_idx] = last_candy;
    }
    for (int j = 1; j <= m; j++) {
      sum[i][j] = sum[i][j - 1];
      if (line[cur_line][j - 1] != '-')
        sum[i][j] += line[cur_line][j - 1] - '0';
    }
  }
  int cnt = int(exit_ldr[0].size()), ans = 0;
  for (int i = 0; i < cnt; i++) {
    for (int j = i; j < cnt; j++) ans = max(ans, dfs(1, i, j));
  }
  cout << ans << '\n';
}
