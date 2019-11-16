bool debug = false;
#include <stdio.h>
#include <string.h>
#include <stack>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N = 2e3 + 10;
struct twoBIT {
  int a[N][N];
  void init() {
    memset(a, 0, sizeof(a));
    return;
  }
  void add(int x, int y, int val) {
    if (x == 0 || y == 0) return;
    int temp;
    while (x < N) {
      temp = y;
      while (temp < N) {
        a[x][temp] += val;
        temp += temp & -temp;
      }
      x += x & -x;
    }
    return;
  }
  int ask(int x, int y) {
    if (x == 0 || y == 0) return 0;
    int temp, ans = 0;
    while (x) {
      temp = y;
      while (temp) {
        ans += a[x][temp];
        temp ^= temp & -temp;
      }
      x ^= x & -x;
    }
    return ans;
  }
  void add(int l, int r, int x, int y, int val) {
    r++;
    y++;
    add(l, x, val);
    add(r, y, val);
    add(l, y, -val);
    add(r, x, -val);
    return;
  }
  int ask(int l, int r, int x, int y) {
    l--;
    x--;
    return ask(l, x) + ask(r, y) - ask(l, y) - ask(r, x);
  }
};
twoBIT BOARD, answer;
bool board[N][N];
int to[N][N], ans[N][N];
bool have(int l, int r, int x, int y) { return BOARD.ask(x, y, l, r) > 0; }
int right(int R, int x, int y) {
  if (R <= 1) return R;
  int l, r, mid;
  if (have(R - 1, R - 1, x, y)) return R;
  if (!have(1, R - 1, x, y)) return 1;
  l = 1;
  r = R - 1;
  while (r - l > 1) {
    mid = (l + r) >> 1;
    if (have(mid, R - 1, x, y))
      l = mid;
    else
      r = mid;
  }
  return r;
}
int main() {
  int d, n, x, y, x1, x2, y1, y2, tt;
  stack<pair<int, int>> s;
  pair<int, int> nxt;
  scanf("%d%d%d%d", &y, &x, &n, &d);
  memset(board, true, sizeof(board));
  while (n--) {
    scanf("%d%d%d%d", &y1, &y2, &x1, &x2);
    x1++;
    y1++;
    for (int i = x1; i <= x2; i++)
      for (int j = y1; j <= y2; j++) board[i][j] = false;
  }
  if (debug)
    for (int i = 1; i <= x; i++, printf("\n"))
      for (int j = 1; j <= y; j++) printf("%d", board[i][j] ? 1 : 0);
  for (int j = 1; j <= y; j++) {
    to[x][j] = board[x][j] ? 1 : 0;
    for (int i = x - 1; i >= 1; i--)
      to[i][j] = board[i][j] ? to[i + 1][j] + 1 : 0;
  }
  BOARD.init();
  for (int i = 1; i <= x; i++)
    for (int j = 1; j <= y; j++)
      if (!board[i][j]) BOARD.add(i, j, 1);
  answer.init();
  for (int i = 1; i <= x; i++) {
    while (!s.empty()) s.pop();
    for (int j = y; j >= 1; j--) {
      if (s.empty()) {
        if (to[i][j] > 0) {
          s.push({j, to[i][j]});
          answer.add(1, j - right(j, i, i + to[i][j] - 1) + 1, 1, to[i][j], 1);
          if (debug)
            printf("answer.add(%d,%d,%d,%d)\n", 1,
                   j - right(j, i, i + to[i][j] - 1) + 1, 1, to[i][j]);
        }
      } else if (to[i][j] == 0)
        while (!s.empty()) s.pop();
      else
        while (true) {
          if (s.top().S == to[i][j])
            break;
          else if (s.top().S > to[i][j]) {
            nxt = s.top();
            s.pop();
            if (!s.empty() && s.top().S >= to[i][j])
              ;
            else {
              if (s.empty())
                tt = 1;
              else
                tt = s.top().S + 1;
              s.push({nxt.F, to[i][j]});
              answer.add(1, nxt.F - right(j, i, i + to[i][j] - 1) + 1, tt,
                         to[i][j], 1);
              if (debug)
                printf("answer.add(%d,%d,%d,%d)\n", 1,
                       nxt.F + 1 - right(j, i, i + to[i][j] - 1), tt, to[i][j],
                       1);
              answer.add(1, nxt.F - j, tt, to[i][j], -1);
            }
          } else {
            if (s.empty())
              tt = 1;
            else
              tt = s.top().S + 1;
            s.push({j, to[i][j]});
            answer.add(1, j - right(j, i, i + to[i][j] - 1) + 1, tt, to[i][j],
                       1);
            if (debug)
              printf("answer.add(%d,%d,%d,%d)\n", 1,
                     j + 1 - right(j, i, i + to[i][j] - 1), tt, to[i][j], 1);
          }
        }
    }
  }
  memset(ans, 0, sizeof(ans));
  for (int i = 1; i <= x; i++)
    for (int j = 1; j <= y; j++) ans[i][j] = answer.ask(1, j, 1, i);
  if (debug)
    for (int i = 1; i <= x; i++, printf("\n"))
      for (int j = 1; j <= y; j++) printf("%d", ans[i][j]);
  for (int i = x; i >= 1; i--)
    for (int j = y; j >= 1; j--) ans[i][j] += ans[i][j + 1];
  if (debug)
    for (int i = 1; i <= x; i++, printf("\n"))
      for (int j = 1; j <= y; j++) printf("%3d", ans[i][j]);
  while (d--) {
    scanf("%d%d", &y1, &x1);
    printf("%d\n", ans[x1][y1]);
  }
}
