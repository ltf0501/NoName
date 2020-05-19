#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back

map<vector<pair<int, int>>, int> m;
int t;

int mex(vector<int> &x) {
	int sz;
	sort(x.begin(), x.end());
	x.resize(unique(x.begin(), x.end()) - x.begin());
	sz = int(x.size());
	for (int i = 0; i < sz; i++) if (x[i] != i) return i;
	return sz;
}

int ABS(int n) {return n >= 0 ? n : -n;}

bool have_edge(pair<int, int> a, pair<int, int> b) {
	int x = a.F - b.F, y = a.S - b.S;
	return ABS(x) + ABS(y) <= 1;
}

void make_good(vector<pair<int, int>> & v) {
	int lx = 100, ly = 100;
	for (pair<int, int> i : v) lx = min(lx, i.F), ly = min(ly, i.S);
	for (pair<int, int> &i : v) i.F -= lx, i.S -= ly;
	sort(v.begin(), v.end());
	return ;
}

int went[30][30], need[30][30], dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

bool can(int x, int y, int t) {
	if (x < 0 || y < 0) return false;
	if (need[x][y] != t) return false;
	if (went[x][y] == t) return false;
	return true;
}

void dfs(int x, int y, vector<pair<int, int>> &v) {
	went[x][y] = need[x][y];
	v.PB({x, y});
	for (int i = 0; i < 4; i++) if (can(x + dx[i], y + dy[i], need[x][y])) dfs(x + dx[i], y + dy[i], v);
	return ;
}

int sg_val(vector<pair<int, int>> v) {
	make_good(v);
	if (m.find(v) != m.end()) return m[v];
	int tmp;
	vector<int> x;
	vector<pair<int, int>> nxt;
	vector<vector<pair<int, int>>> vv;
	for (pair<int, int> i : v) {
		++t;
		tmp = 0;
		vv.clear();
		for (pair<int, int> j : v) if (!have_edge(i, j)) need[j.F][j.S] = t;
		for (pair<int, int> j : v) if (can(j.F, j.S, t)) {
			nxt.clear();
			dfs(j.F, j.S, nxt);
			vv.PB(nxt);
		}
		for (vector<pair<int, int>> j : vv) tmp ^= sg_val(j);
		x.PB(tmp);
	}	
	return m[v] = mex(x);
}

string s[30];
int went1[30][30], n, went3[30][30];

bool can1(int x, int y) {
	if (x < 0 || y < 0) return false;
	if (x >= n || y >= n) return false;
	if (went1[x][y]) return false;
	if (s[x][y] != '*') return false;
	return true;
}

void dfs1(int x, int y, int tm) {
	went1[x][y] = tm;
	for (int i = 0; i < 4; i++) if (can1(x + dx[i], y + dy[i])) dfs1(x + dx[i], y + dy[i], tm);
	return ;
}

bool can_val(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= n) return false;
	if (s[x][y] != '*') return false;
	return true;
}

int get_val(int x, int y) {
	for (int i = 0; i < 4; i++) if (can_val(x + dx[i], y + dy[i])) return went1[x + dx[i]][y + dy[i]];
	return 0;
}

bool can3(int x, int y, int tm) {
	if (x < 0 || y < 0 || x >= n || y >= n) return false;
	if (s[x][y] != '.') return false;
	if (went3[x][y]) return false;
	if (get_val(x, y) != tm) return false;
	return true;
}

void dfs3(int x, int y, int tm, vector<pair<int, int>> &v) {
	v.PB({x, y});
	went3[x][y] = true;
	for (int i = 0; i < 4; i++) if (can3(x + dx[i], y + dy[i], tm)) dfs3(x + dx[i], y + dy[i], tm, v);
	return ;
}

int main() {
	int tmp, ans = 0, tm = 0;
	vector<pair<int, int>> v;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> s[i];
	m[v] = 0;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (can1(i, j)) dfs1(i, j, ++tm);
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (s[i][j] == '.' && !went3[i][j]) {
		tmp = get_val(i, j);
		if (tmp) {
			v.clear();
			dfs3(i, j, tmp, v);
			ans ^= sg_val(v);
		}
	}
	if (ans) cout << "First player will win\n";
	else cout << "Second player will win\n";
} 
