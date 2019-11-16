bool debug = true;
#include <iostream>
using namespace std;
struct node {
  node* nxt[26];
  int sg;
  node() {
    sg = 1;
    for (int i = 0; i < 26; i++) nxt[i] = nullptr;
  }
  void pull() {
    sg = 0;
    for (int i = 0; i < 26; i++)
      if (nxt[i]) sg ^= nxt[i]->sg;
    sg++;
    return;
  }
};
void insert(string& s, int pos, node* n) {
  if (pos >= s.size()) return;
  if (!n->nxt[s[pos] - 'a']) n->nxt[s[pos] - 'a'] = new node();
  insert(s, pos + 1, n->nxt[s[pos] - 'a']);
  n->pull();
  return;
}
void out(node* n) {}
void solve() {
  int n, q;
  string s;
  node* root = new node();
  cin >> n;
  while (n--) {
    cin >> s;
    insert(s, 0, root);
  }
  cin >> q;
  while (q--) {
    cin >> s;
    insert(s, 0, root);
    if ((root->sg - 1) == 0)
      cout << 2 << endl;
    else
      cout << 1 << endl;
  }
  return;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case " << i << ":" << endl;
    solve();
  }
}
