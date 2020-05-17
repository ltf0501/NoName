#include <stdio.h>
#include <algorithm>
using namespace std;

constexpr int kN = int(2E3 + 10);
int a[kN][kN], n;

int ask(int x, int y) {
	if (a[x][y] > 0) return a[x][y];
	int ans;
	printf("? %d %d\n", x, y);
	fflush(stdout);
	scanf("%d", &ans);
	return a[x][y] = ans;
}

void answer(int x, int y) {
	printf("! %d %d\n", x, y);
	fflush(stdout);
	return ;
}
void dfs(int x1, int y1, int x2, int y2, int lst, int lstx, int lsty) { 
	if (x2 - x1 <= 3 && y2 - y1 <= 3) {
	       	int x = x1, y = y1;
		for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) if (ask(x, y) < ask(i, j)) x = i, y = j;
		answer(x, y);
	}
	else if (x2 - x1 >= y2 - y1) {
		int mid = (x1 + x2) >> 1, pos = y1, mxl = 0, mxr = 0;
		for (int i = y1; i <= y2; i++) if (ask(mid, pos) < ask(mid, i)) pos = i;


		for (int i = -1; i <= 1; i++) if (y1 <= i + pos && i + pos <= y2) {
			if (x1 <= mid - 1 && mid - 1 <= x2) mxl = max(mxl, ask(mid - 1, i + pos));
			if (x1 <= mid + 1 && mid + 1 <= x2) mxr = max(mxr, ask(mid + 1, i + pos));
		}

		if (lst > ask(mid, pos)) {
			if (lstx < mid) dfs(x1, y1, mid, y2, lst, lstx, lsty);
			else dfs(mid, y1, x2, y2, lst, lstx, lsty);
		}
		else if (mxl < mxr) dfs(mid, y1, x2, y2, ask(mid, pos), mid, pos);
		else dfs(x1, y1, mid, y2, ask(mid, pos), mid, pos);
	}
	else {
		int mid = (y1 + y2) >> 1, pos = x1, mxl = 0, mxr = 0;
		for (int i = x1; i <= x2; i++) if (ask(pos, mid) < ask(i, mid)) pos = i;
		for (int i = -1; i <= 1; i++) if (x1 <= i + pos && i + pos <= x2) {
			if (y1 <= mid - 1 && mid - 1 <= y2) mxl = max(mxl, ask(pos + i, mid - 1));
			if (y1 <= mid + 1 && mid + 1 <= y2) mxr = max(mxr, ask(pos + i, mid + 1));
		}
		if (lst > ask(pos, mid)) {
			if (lsty < mid) dfs(x1, y1, x2, mid, lst, lstx, lsty);
			else dfs(x1, mid, x2, y2, lst, lstx, lsty);
		}
		else if (mxl < mxr) dfs(x1, mid, x2, y2, ask(pos, mid), pos, mid);
		else dfs(x1, y1, x2, mid, ask(pos, mid), pos, mid);
	}

	return ;
}

int main() {
	scanf("%d", &n);
	dfs(1, 1, n, n, 0, 1, 1);
} 
