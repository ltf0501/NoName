#include <bits/stdc++.h>
using namespace std;

map<char, bool> has;

string solve(string str, int mask) {
  has.clear();
  for (char c : str) has[c] = true;
  if (has['0'] && (mask & (1 << 0))) {
    for (int i = 33; i <= 47; i++) str.push_back(char(i));
  }
  if (has['A'] && (mask & (1 << 1))) {
    for (int i = 58; i <= 64; i++) str.push_back(char(i));
  }
  if (has['a'] && (mask & (1 << 2))) {
    for (int i = 91; i <= 96; i++) str.push_back(char(i));
  }
  sort(str.begin(), str.end());
  str.erase(unique(str.begin(), str.end()), str.end());
  deque<pair<char, char>> vec;
  pair<char, char> last = {1, 0};
  for (char c : str) {
    if (last.second != c - 1) {
      vec.push_back(last);
      last = {c, c};
    } else {
      last.second = c;
    }
  }
  vec.push_back(last);
  vec.pop_front();
  stringstream ss;
  ss << "%[";
  if (vec.empty()) return "%[!]";
  for (auto p : vec) {
    if (p.first == p.second) {
      ss << p.first;
    } else if (p.first + 1 == p.second) {
      ss << p.first << p.second;
    } else {
      ss << p.first << '-' << p.second;
    }
  }
  ss << "]\n";
  string ans;
  getline(ss, ans);
  return ans;
}

int main() {
  string str1;
  getline(cin, str1);
  pair<int, string> ans = {INT_MAX, ""};
  for (int i = 0; i < (1 << 3); i++) {
    auto ans_str = solve(str1, i);
    ans = min(ans, {ans_str.size(), ans_str});
  }
  string str2;
  if (!has[' ']) str2.push_back(' ');
  for (char c = '0'; c <= '9'; c++) {
    if (!has[c]) str2.push_back(c);
  }
  for (char c = 'A'; c <= 'Z'; c++) {
    if (!has[c]) str2.push_back(c);
  }
  for (char c = 'a'; c <= 'z'; c++) {
    if (!has[c]) str2.push_back(c);
  }
  for (int i = 0; i < (1 << 3); i++) {
    auto ans_str = solve(str2, i);
    ans_str.insert(2, "^");
    ans = min(ans, {ans_str.size(), ans_str});
  }
  // cerr << ans1 << ' ' << ans2 << '\n';
  cout << ans.second << '\n';
  ;
}
