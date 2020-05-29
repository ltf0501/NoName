#include <stdio.h>


int a[5][5], n = 4;
bool used[20];

void out() {
	for (int i = 2; i <= n; i++) for (int j = 2; j <= n; j++) if (a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1] <= 16 && a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1] >= 1 && !used[a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1]]) {
		a[i][j] = a[i][j - 1] + a[i - 1][j] - a[i - 1][j - 1];
		used[a[i][j]] = true;
	} else {
		for (int i = 2; i <= n; i++) for (int j = 2; j <= n; j++) if (a[i][j] != 0) {
			used[a[i][j]] = false;
			a[i][j] = 0;
		}
		return ;
	}
	for (int i = 1; i <= n; i++, printf("\n")) for (int j = 1; j <= n; j++) printf("%d ", a[i][j]);
	return ;
}


void dfs(int x, int y, int v) {
	if (x == 5) {
		out();
		return ;
	}
	for (int i = 1; i <= 16; i++) if (!used[i]) {
		used[a[x][y] = i] = true;
		if (x == 1 && y == 4) dfs(2, 1, i);
		else if (x == 1) dfs(x, y + 1, i);
		else dfs(x + 1, y, i);
		used[a[x][y]] = false;
	}
	return ;
}


int main() {
	int n = 4;
	for (int i = 1; i <= 9; i++) {
		used[a[1][1] = i] = true;
		dfs(1, 2, i);
		used[i] = false;
	}
}
