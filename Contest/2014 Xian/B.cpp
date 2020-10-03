#include <iostream>
#include <queue>
#include <utility>
using namespace std;
#define F first
#define S second

constexpr int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
constexpr char dir[4] = {'D', 'U', 'R', 'L'};

bool ok(int x, int y) {
	return 0 <= x && x < 5 && 0 <= y && y < 6;
}

int p[40];
int Find(int n) {return p[n] == n ? n : p[n] = Find(p[n]);}

struct Board {
	string s[5];
	char ns[5][6][2];
	bool used[5][6], went[5][6];
	void in() {
		for (int i = 0; i < 5; i++) cin >> s[i];
		return ;
	}
	inline void move(int x, int y, int px, int py) {
		swap(s[x][y], s[px][py]);
		return ;
	}
	pair<int, int> run() {
		//cout << "run\n";
		//for (int i = 0; i < 5; i++) cout << s[i] << "\n";
		bool move = true, f = false;
		int combo = 0, drop = 0, idx;
		pair<int, int> nxt;
		queue<pair<int, int>> q;
		for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) ns[i][j][f] = s[i][j];
		while (move) {
			move = false;
			for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) used[i][j] = false;
			for (int j = 0; j < 4; j++) for (int i = 4; i >= 0; i--) if (ns[i][j][f] == '\0') break;
			else {
				if (ns[i][j][f] == ns[i][j + 1][f] && ns[i][j + 1][f] == ns[i][j + 2][f]) {
					used[i][j] = true;
					used[i][j + 1] = true;
					used[i][j + 2] = true;
				}
			}
			for (int j = 0; j < 6; j++) for (int i = 2; i >= 0; i--) if (ns[i][j][f] == '\0') break;
			else {
				if (ns[i][j][f] == ns[i + 1][j][f] && ns[i + 1][j][f] == ns[i + 2][j][f] && ns[i][j][f] != '\0') {
					used[i][j] = true;
					used[i + 1][j] = true;
					used[i + 2][j] = true;
				}
			}
			//for (int i = 0; i < 5; i++, cout << '\n') for (int j = 0; j < 6; j++) cout << ns[i][j][f];
			//for (int i = 0; i < 5; i++, cout << '\n') for (int j = 0; j < 6; j++) cout << (used[i][j] ? 1 : 0);

			for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) went[i][j] = false;
			for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) if (used[i][j] && !went[i][j]) {
				q.push({i, j});
				while (!q.empty()) {
					nxt = q.front();
					q.pop();
					went[nxt.F][nxt.S] = true;
					for (int k = 0; k < 4; k++) if (ok(nxt.F + dx[k], nxt.S + dy[k]) && !went[nxt.F + dx[k]][nxt.S + dy[k]]) {
						if (ns[nxt.F + dx[k]][nxt.S + dy[k]][f] == ns[i][j][f]) q.push({nxt.F + dx[k], nxt.S + dy[k]});
					}
				}
				move = true;
				combo++;
			}
			for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) if (used[i][j]) drop++;
			for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) ns[i][j][!f] = '\0';
			for (int j = 0; j < 6; j++) {
				idx = 4;
				for (int i = 4; i >= 0; i--) if (!used[i][j]) ns[idx--][j][!f] = ns[i][j][f];
			}
			f = !f;
		}
		//cout << combo << ' ' << drop << '\n';
		return {combo, drop};
	}
};

struct Solution {
	int s[10], combo, drop, len, x, y;
	Solution() {}
	Solution (int a, int b, int c, int d, int e, int f[]) {
		combo = a;
		drop = b;
		x = c;
		y = d;
		len = e;
		for (int i = 0; i < len; i++) s[i] = f[i];
	}
	void set(int a, int b, int c, int d, int e, int f[]) {
		combo = a;
		drop = b;
		x = c;
		y = d;
		len = e;
		for (int i = 0; i < len; i++) s[i] = f[i];
		return ;
	}
	void out() {
		cout << "Combo:" << combo << " Length:" << len << "\n";
		cout << x << " " << y << "\n";
		for (int i = 0; i < len; i++) cout << dir[s[i]];
		cout << "\n";
		return ;
	}
};

Board board;
Solution ans;
int s[10];
int stx, sty;

void better_solution(Solution &a, Solution b) {
	if (a.combo < b.combo) a = b;
	else if (a.combo == b.combo && a.drop < b.drop) a = b;
	else if (a.combo == b.combo && a.drop == b.drop && a.len > b.len) a = b;
	return ;
}


void check(int step) {
	pair<int, int> tmp = board.run();
	int combo = tmp.F, drop = tmp.S;
	better_solution(ans, Solution(combo, drop, stx, sty, step, s));
}

void dfs(int px, int py, int step) {
	//cout << px << " " << py << " " << step << "\n";
	for (int i = 0; i < 4; i++) if (ok(px + dx[i], py + dy[i])) {
		if (step > 0 && s[step - 1] == (i ^ 1)) continue;
		board.move(px, py, px + dx[i], py + dy[i]);
		s[step] = i;
		check(step + 1);
		if (step < 8) dfs(px + dx[i], py + dy[i], step + 1);
		board.move(px, py, px + dx[i], py + dy[i]);
	}
	return ;
}

void solve() {
	board.in();
	ans.set(0, 0, 1, 1, 0, s);
	stx = sty = 1;
	//check(0);
	for (int i = 0; i < 5; i++) for (int j = 0; j < 6; j++) {
		stx = i + 1, sty = j + 1;
		//cout << i << " " << j << "\n";
		dfs(i, j, 0);
	}
	ans.out();
}

int main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ":\n";
		solve();
	}
} 
