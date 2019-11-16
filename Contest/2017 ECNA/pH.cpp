#include <iostream>
using namespace std;
const int N = 1e2 + 10;
bool went[N][N];
string s[N];
int n, m;
void dfs(int x, int y) {
  if (x < 0 || y < 0 || x >= n || y >= m) return;
  if (s[x][y] == '.') return;
  if (went[x][y]) return;
  went[x][y] = true;
  for (int i = -1; i < 2; i++)
    for (int j = -1; j < 2; j++) dfs(x + i, y + j);
  return;
}
int main() {
  int cnt = 0;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> s[i];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) went[i][j] = false;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (!went[i][j] && s[i][j] == '#') {
        cnt++;
        dfs(i, j);
      }
  cout << cnt << endl;
}
