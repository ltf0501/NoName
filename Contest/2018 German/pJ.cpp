#include <stdio.h>
const int N = 12e5 + 10;
void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
  return;
}
struct piece {
  int a[4];
  void in() {
    for (int i = 0; i < 4; i++) scanf("%d", &a[i]);
    return;
  }
  bool zero() {
    for (int i = 0; i < 3; i++)
      if (a[i] == a[i + 1] && a[i] == 0) return true;
    if (a[0] == a[3] && a[0] == 0) return true;
    return false;
  }
  int right() { return a[3]; }
  int bot() { return a[2]; }
  int left() { return a[1]; }
  int top() { return a[0]; }
  void spin() {
    for (int i = 1; i < 4; i++) swap(a[i], a[i - 1]);
    return;
  }
  void spinto(int left) {
    while (true) {
      if (a[1] == left)
        return;
      else
        spin();
    }
  }
  void spintotop(int top) {
    while (true) {
      if (a[0] == top)
        return;
      else
        spin();
    }
  }
  void tozero() {
    while (true) {
      if (a[0] == a[1] && a[0] == 0)
        return;
      else
        spin();
    }
  }
};
int ans[N], n, con[N][2], ft[N], now, w = 1, h = 0, cnt = 0;
piece a[N];
bool used[N];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) a[i].in();
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 4; j++)
      if (a[i].a[j] != 0) {
        if (con[a[i].a[j]][0] == 0)
          con[a[i].a[j]][0] = i;
        else
          con[a[i].a[j]][1] = i;
      }
  }
  for (int i = 1; i <= n; i++)
    if (a[i].zero()) {
      a[i].tozero();
      ans[0] = i;
      ft[0] = a[i].bot();
      now = a[i].right();
      cnt++;
      used[i] = true;
      while (now != 0) {
        w++;
        cnt++;
        if (!used[con[now][0]]) {
          ans[w - 1] = con[now][0];
          a[con[now][0]].spinto(now);
          if (a[con[now][0]].top() != 0) {
            printf("impossible\n");
            return 0;
          }
          ft[w - 1] = a[con[now][0]].bot();
          used[con[now][0]] = true;
          now = a[con[now][0]].right();
        } else if (!used[con[now][1]]) {
          if (!used[con[now][1]]) {
            ans[w - 1] = con[now][1];
            a[con[now][1]].spinto(now);
            if (a[con[now][1]].top() != 0) {
              printf("impossible\n");
              return 0;
            }
            ft[w - 1] = a[con[now][1]].bot();
            used[con[now][1]] = true;
            now = a[con[now][1]].right();
          }
        } else {
          printf("impossible\n");
          return 0;
        }
      }
      if (cnt != n)
        for (int j = 0; j < w; j++)
          if (ft[j] == 0) {
            printf("impossible\n");
            return 0;
          }
      while (cnt < n) {
        now = 0;
        h++;
        cnt++;
        if (!used[con[ft[0]][0]]) {
          ans[h * w] = con[ft[0]][0];
          a[con[ft[0]][0]].spintotop(ft[0]);
          if (a[con[ft[0]][0]].left() != 0) {
            printf("impossible\n");
            return 0;
          }
          used[con[ft[0]][0]] = true;
          now = a[con[ft[0]][0]].right();
          ft[0] = a[con[ft[0]][0]].bot();
        } else if (!used[con[ft[0]][1]]) {
          ans[h * w] = con[ft[0]][1];
          a[con[ft[0]][1]].spintotop(ft[0]);
          if (a[con[ft[0]][1]].left() != 0) {
            printf("impossible\n");
            return 0;
          }
          used[con[ft[0]][1]] = true;
          now = a[con[ft[0]][1]].right();
          ft[0] = a[con[ft[0]][1]].bot();
        } else {
          printf("impossible\n");
          return 0;
        }
        for (int j = 1; j < w; j++) {
          if (now == 0) {
            printf("impossible\n");
            return 0;
          }
          cnt++;
          if (!used[con[now][0]]) {
            ans[h * w + j] = con[now][0];
            a[con[now][0]].spinto(now);
            if (a[con[now][0]].top() != ft[j]) {
              printf("impossible\n");
              return 0;
            }
            ft[j] = a[con[now][0]].bot();
            used[con[now][0]] = true;
            now = a[con[now][0]].right();
          } else if (!used[con[now][1]]) {
            if (!used[con[now][1]]) {
              ans[h * w + j] = con[now][1];
              a[con[now][1]].spinto(now);
              if (a[con[now][1]].top() != ft[j]) {
                printf("impossible\n");
                return 0;
              }
              ft[j] = a[con[now][1]].bot();
              used[con[now][1]] = true;
              now = a[con[now][1]].right();
            }
          } else {
            printf("impossible\n");
            return 0;
          }
        }
        if (now != 0) {
          printf("impossible\n");
          return 0;
        }
        if (cnt != n)
          for (int j = 0; j < w; j++)
            if (ft[j] == 0) {
              printf("impossible\n");
              return 0;
            }
      }
      for (int i = 0; i < w; i++)
        if (ft[i] != 0) {
          printf("impossible\n");
          return 0;
        }
      printf("%d %d\n", h + 1, w);
      for (int i = 0; i <= h; i++) {
        printf("%d", ans[i * w]);
        for (int j = 1; j < w; j++) printf(" %d", ans[i * w + j]);
        printf("\n");
      }
      return 0;
    }
  printf("impossible\n");
  return 0;
}
