bool debug = false;
#include <stdio.h>
#include <bitset>
#include <vector>
using namespace std;
const int N = 1e2 + 10;
const int NN = 1e4 + 10;
#define PB push_back
struct triple {
  int a, b, c;
  void in() {
    scanf("%d%d%d", &a, &b, &c);
    return;
  }
  void out() {
    printf("%d %d %d\n", a, b, c);
    return;
  }
};
int main() {
  vector<triple> ans;
  vector<vector<int>> rings;
  vector<int> temp, trings[N];
  bitset<N> went;
  bitset<NN> done;
  int n, now, pos, tot, cnt;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    went.reset();
    for (int j = 1; j <= n; j++)
      if (!went[j]) {
        temp.clear();
        now = j;
        went[j] = true;
        temp.PB(now);
        now += i;
        while (now != j) {
          temp.PB(now);
          went[now] = true;
          now += i;
          now = (now - 1) % n + 1;
        }
        rings.PB(temp);
      }
  }
  if (debug)
    for (vector<int> i : rings) {
      for (int j : i) printf("%d ", j);
      printf("\n");
    }
  done.reset();
  tot = (int)rings.size();
  for (int i = 0; i < tot; i++)
    for (int j = 0; j < rings[i].size(); j++) trings[rings[i][j]].PB(i);
  ans.PB({1, 1, 0});
  now = 1;
  cnt = 1;
  done[0] = true;
  while (cnt < tot) {
    for (int i = 0; i < trings[now].size(); i++)
      if (!done[trings[now][i]]) {
        for (pos = 0; rings[trings[now][i]][pos] != now; pos++)
          ;
        for (int j = pos + 1; j < rings[trings[now][i]].size(); j++)
          ans.PB({rings[trings[now][i]][j], rings[trings[now][i]][j],
                  rings[trings[now][i]][j - 1]});
        ans.PB({rings[trings[now][i]][0], rings[trings[now][i]][0],
                rings[trings[now][i]].back()});
        for (int j = 1; j <= pos; j++) {
          ans.PB({rings[trings[now][i]][j], rings[trings[now][i]][j],
                  rings[trings[now][i]][j - 1]});
        }
        done[trings[now][i]] = true;
        cnt++;
      }
    ans.PB({now + 1, now + 1, now});
    now++;
  }
  while (now < n) {
    ans.PB({now + 1, now + 1, now});
    now++;
  }
  if (now == n) ans.PB({0, 1, n});
  for (triple i : ans) i.out();
}
