#include <string.h>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
const int N = 1e4 + 10;
const long long int INF = 1e16 + 10;
#define PB push_back
#define F first
#define S second
struct edge {
  int a;
  int b;
  long long int cost;
  long long int pres;
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<edge> graph[N];
  vector<int> bg[N];
  int nxt, n, b, t = 0, u, v, w, deg[N];
  long long int ans, pos, x, y, temp, cost[N], pres[N], dp[N];
  map<string, int> m;
  queue<int> q;
  string sa, sb, sc;
  cin >> b >> n;
  memset(deg, 0, sizeof(deg));
  memset(cost, INF, sizeof(cost));
  memset(pres, 0, sizeof(pres));
  memset(dp, 0, sizeof(dp));
  while (n--) {
    cin >> sa >> sb >> sc >> x >> y;
    if (m.find(sa) == m.end())
      m[sa] = u = t++;
    else
      u = m[sa];
    if (m.find(sb) == m.end())
      m[sb] = v = t++;
    else
      v = m[sb];
    if (m.find(sc) == m.end())
      m[sc] = w = t++;
    else
      w = m[sc];
    graph[u].PB({v, w, x, y});
    deg[u] += 2;
    bg[v].PB(u);
    bg[w].PB(u);
  }
  for (int i = 0; i < t; i++)
    if (deg[i] == 0) {
      cost[i] = 0;
      q.push(i);
    }
  while (!q.empty()) {
    nxt = q.front();
    q.pop();
    for (edge i : graph[nxt]) {
      temp = i.cost + cost[i.a] + cost[i.b];
      if (temp < cost[nxt]) {
        cost[nxt] = temp;
        pres[nxt] = i.pres + pres[i.a] + pres[i.b];
      } else if (temp == cost[nxt]) {
        temp = i.pres + pres[i.a] + pres[i.b];
        pres[nxt] = max(pres[nxt], temp);
      }
    }
    for (int i : bg[nxt]) {
      if (deg[i] == 1)
        q.push(i);
      else
        deg[i]--;
    }
  }
  // for(int i=0;i<t;i++)printf("%d %d\n",cost[i],pres[i]);
  for (int i = 0; i < t; i++)
    if (pres[i] > 0) {
      for (int j = b; j >= cost[i]; j--) {
        dp[j] = max(dp[j], dp[j - cost[i]] + pres[i]);
      }
    }
  ans = pos = 0;
  for (int i = 0; i <= b; i++) {
    if (dp[i] > ans) {
      ans = dp[i];
      pos = i;
    }
  }
  cout << ans << endl << pos << endl;
}
