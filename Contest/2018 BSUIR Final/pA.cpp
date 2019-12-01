bool debug = false;
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1 << 9, kInf = 0x3f3f3f3f;

string str;
bool vis[kN][kN];
tuple<int, int, int, int, char> dp[kN][kN];

tuple<int, int, int, int, char> Make(int l, int r, int d, int dir, char c);

tuple<int, int, int, int, char> dfs(int l, int r) {
  if (vis[l][r]) return dp[l][r];
  vis[l][r] = true;
  if (l == r) {
    if (str[l] == '*')
      return dp[l][r] = {0, l, r, -1, 0};
    else
      return dp[l][r] = {1, l, r, -1, str[l]};
  }
  if (l + 1 >= r) {
    if (str[l] == '*') return dp[l][r] = Make(l + 1, r, 0, 0, 0);
    if (str[r] == '*') return dp[l][r] = Make(l, r - 1, 0, 0, 0);
    if (str[l] == str[r]) return dp[l][r] = {2, l, r, -3, str[l]};
    if (str[l] == '?') {
      return dp[l][r] = {2, l, r, -3, str[r]};
    }
    if (str[r] == '?') {
      return dp[l][r] = {2, l, r, -3, str[l]};
    }
    return dp[l][r] = {kInf, l, r, -1, 0};
  }
  dp[l][r] = {kInf, l, r, -1, 0};
  bool wild_l = !isalpha(str[l]), wild_r = !isalpha(str[r]);
  if (!wild_l && !wild_r) {
    if (str[l] == str[r])
      return dp[l][r] = Make(l + 1, r - 1, 2, 3, str[l]);
    else
      return dp[l][r] = {kInf, l, r, -1, 0};
  }
  if (wild_l && wild_r) {
    if (str[l] == '?' && str[r] == '?')
      return dp[l][r] = Make(l + 1, r - 1, 2, 3, 'a');
    else if (str[l] == '?')
      dp[l][r] = min(Make(l + 1, r, 2, 3, 'a'), Make(l, r - 1, 0, 0, 0));
    else if (str[r] == '?')
      dp[l][r] = min(Make(l, r - 1, 2, 3, 'a'), Make(l + 1, r, 0, 0, 0));
    else
      return dp[l][r] =
                 min({dp[l][r], Make(l + 1, r, 0, 0, 0),
                      Make(l, r - 1, 0, 0, 0), Make(l + 1, r - 1, 0, 0, 0)});
  } else {
    if (wild_l) {
      if (str[l] == '*')
        return dp[l][r] =
                   min(Make(l, r - 1, 2, 3, str[r]), Make(l + 1, r, 0, 0, 0));
      else
        return dp[l][r] = Make(l + 1, r - 1, 2, 3, str[r]);
    } else {
      if (str[r] == '*')
        return dp[l][r] =
                   min(Make(l + 1, r, 2, 3, str[l]), Make(l, r - 1, 0, 0, 0));
      else
        return dp[l][r] = Make(l + 1, r - 1, 2, 3, str[l]);
    }
  }
  return dp[l][r];
}

tuple<int, int, int, int, char> Make(int l, int r, int d, int dir, char c) {
  if (dir > 0) assert(d == __builtin_popcount(dir));
  return make_tuple(get<0>(dfs(l, r)) + d, l, r, dir, c);
}

int main() {
  cin >> str;
  int n = int(str.size());
  stack<char> l_stack, r_stack;
  auto cur = dfs(0, n - 1);
  if (get<0>(cur) >= kInf) {
    cout << "-1\n";
    return 0;
  }
  int l = 0, r = n - 1;
  while (get<3>(cur) >= 0) {
    if (get<3>(cur) & 1) {
      l_stack.push(get<4>(cur));
    }
    if (get<3>(cur) & 2) {
      r_stack.push(get<4>(cur));
    }
    l = get<1>(cur);
    r = get<2>(cur);
    cur = dfs(l, r);
  }
  if (get<4>(cur)) {
    r_stack.push(get<4>(cur));
  }
  if (get<3>(cur) == -3) {
    r_stack.push(get<4>(cur));
  }
  while (l_stack.size()) {
    r_stack.push(l_stack.top());
    l_stack.pop();
  }
  while (r_stack.size()) {
    cout << (r_stack.top() == '?' ? 'a' : r_stack.top());
    r_stack.pop();
  }
  cout << '\n';
}
