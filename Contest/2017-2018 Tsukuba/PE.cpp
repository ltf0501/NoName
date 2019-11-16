By ltf0501, contest : 2017 - 2018 ACM - ICPC, Asia Tsukuba Regional Contest,
    problem : (E)Black or White, Accepted,
    #
#include <algorithm>
#include <cstdio>
#include <deque>
    using namespace std;
#define maxn 500010
char s[maxn], t[maxn];
int n, k;
int num[maxn];
int dp[maxn];
deque<int> dq;
int cal(int i, int j) { return dp[j] + (num[i] - num[j + 1] + 1) / 2 + 1; }
int main() {
  scanf("%d%d", &n, &k);
  scanf("%s", s + 1);
  scanf("%s", t + 1);
  num[1] = 1;
  for (int i = 2; i <= n; i++) num[i] = num[i - 1] + (t[i] != t[i - 1]);
  for (int i = 1; i <= n; i++) {
    while (!dq.empty()) {
      if (cal(i, dq.back()) > cal(i, i - 1))
        dq.pop_back();
      else
        break;
    }
    dq.push_back(i - 1);
    while (!dq.empty() && i - dq.front() > k) dq.pop_front();
    while (dq.size() >= 2) {
      int j = dq[0], l = dq[1];
      if (cal(i, j) > cal(i, l))
        dq.pop_front();
      else
        break;
    }
    if (s[i] == t[i])
      dp[i] = dp[i - 1];
    else {
      int j = dq[0];
      //			printf("%d: %d\n",i,j);
      dp[i] = cal(i, j);
    }
  }
  //	for(int i=1;i<=n;i++)printf("%d ",dp[i]);
  printf("%d\n", dp[n]);
  return 0;
}
