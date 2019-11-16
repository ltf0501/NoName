#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

static inline char getRawChar() {
  static char buf[1 << 16], *p = buf, *end = buf;
  if (p == end) {
    if ((end = buf + fread(buf, 1, 1 << 16, stdin)) == buf) return '\0';
    p = buf;
  }
  return *p++;
}
char getChar() {
  char c;
  while (!isdigit(c = getRawChar()))
    ;
  return c;
}
int readInt() {
  char c;
  int n = 0;
  while (!isdigit(c = getRawChar()))
    ;
  do {
    n = n * 10 + (c - '0');
  } while ((c = getRawChar()) && isdigit(c));
  return n;
}

template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  int t = readInt();
  for (int cases = 1; cases <= t; cases++) {
    cout << "Case " << cases << ":\n";
    int e = readInt();
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>>
        pq;
    Tree<tuple<int, int>> st;
    for (int ev = 0; ev < e; ev++) {
      int op = readInt(), cur = readInt();
      while (pq.size() && get<0>(pq.top()) < cur) {
        auto pr = pq.top();
        st.erase(make_tuple(get<2>(pr), get<1>(pr)));
        pq.pop();
      }
      if (op == 1) {
        int val = readInt(), e_ts = readInt();
        pq.emplace(e_ts, cur, val);
        st.insert(make_tuple(val, cur));
        // cerr << "INSERT\n";
      } else {
        int k = readInt();
        cout << (int(st.size()) >= k ? get<0>(*st.find_by_order(k - 1)) : -1)
             << '\n';
      }
      // cerr << "SZ: " << st.size() << ' ' << pq.size() << '\n';
    }
  }
}
