#include <iostream>
#include <vector>
using namespace std;

constexpr int kN = int(1E5 + 10);

int mx[kN], my[kN];

vector<int> idx[kN];
string field[kN];

bool Dfs(int x) {
	if (vis[x]) return false;
	vis[x] = true;
	for (int y : g[x]) {
		if (!my[y] || Dfs(y)) {
			my[y] = x;
			mx[x] = y;
			return true;
		}
	}
	return false;
}

int main() {
	int n, m;
	bool f = false;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> field[i];
	for (int i = 0; i < n; i++) for (int j = 0
	for (int i = 0; i < n; i++) for (int j = 1; j < m; j++) 
		if (field[i][j] == '.' && field[i][j - 1] == '.') {
			g[
		}
}
