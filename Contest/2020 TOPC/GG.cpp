#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define F first
#define S second

constexpr int kN = 2e5, kInf = 1e9;

struct Edge { int ed, next; };
string field[kN];

vector<Edge> edge;
vector<int> graph[kN];
int head[kN], matchx[kN], matchy[kN], disx[kN], disy[kN], vis[kN], que[kN * 2];
int dis;

void AddEdge(int a, int b) {
	edge.push_back({b, head[a]});
	head[a] = int(edge.size() - 1);
	graph[a].PB(b);
	graph[b].PB(a);
	return ;
}

bool Bfs(int v) {
	int x, y;
	int front = 0, tail = 0;
	dis = kInf;
	memset(disx, -1, sizeof(disx));
	memset(disy, -1, sizeof(disy));
	for (int i = 0; i < v; i++) {
		if (matchx[i] < 0) {
			disx[que[tail++] = i] = 0;
		}
	}
	while (front < tail) {
		if (disx[x = que[front++]] > dis) break;
		for (int i = head[x]; ~i; i = edge[i].next) {
			if (disy[y = edge[i].ed] < 0) {
				disy[y] = disx[x] + 1;
				if (matchy[y] < 0) dis = disy[y];
				else {
					disx[que[tail++] = matchy[y]] = disy[y] + 1;
				}
			}
		}
	}
	return dis < kInf;
}

bool Dfs(int x) {
	int y;
	for (int i = head[x]; ~i; i = edge[i].next) {
		if (!vis[y = edge[i].ed] && disy[y] == disx[x] + 1) {
			vis[y] = true;
			if ((~matchy[y]) && disy[y] == dis) {
				continue;
			}
			if (matchy[y] < 0 || Dfs(matchy[y])) {
				matchx[x] = y;
				matchy[y] = x;
				return true;
			}
		}
	}
	return false;
}

int MaxMatch(int v) {
	int ret = 0;
	memset(matchx, -1, sizeof(matchx));
	memset(matchy, -1, sizeof(matchy));
	while (Bfs(v)) {
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < v; i++) {
			if (matchx[i] < 0 && Dfs(i)) ++ret;
		}
	}
	return ret;
}

pair<int, int> posi[kN];
bool went[kN];

void ddfs(int idx) {
	went[idx] = true;
	if (field[posi[idx].F][posi[idx].S] == '*') return ;
	field[posi[idx].F][posi[idx].S] = 'C';
	for (int i : graph[idx]) if (!went[i]) {
		went[i] = true;
		if (i & 1) {
			if (matchy[i] != -1 && !went[matchy[i]]) ddfs(matchy[i]);
		}
		else {
			if (matchx[i] != -1 && !went[matchx[i]]) ddfs(matchx[i]);
		}
	}
	return ;
}


int main() {
	memset(head, -1, sizeof(head));
	int n, m, om, ans = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> field[i];
	om = m;
	if (!(m & 1)) {
		m++;
		for (int i = 0; i < n; i++) field[i] += '*';
	}
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (field[i][j - 1] == '.' && field[i][j] == '.') {
				int u = i * m + (j - 1);
				int v = i * m + (j);
				if ((i + j) % 2 == 0) AddEdge(v, u);
				else AddEdge(u, v);
			}
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (field[i - 1][j] == '.' && field[i][j] == '.') {
				int u = (i - 1) * m + j;
				int v = i * m + (j);
				if ((i + j) % 2 == 0) AddEdge(v, u);
				else AddEdge(u, v);
			}
		}
	}

	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) posi[i * m + j] = {i, j};
	int matchcnt = MaxMatch(n * m);
	// odd -> y, even -> x
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) 
		if (field[i][j] == '.' && !went[i * m + j]) {
			if ((i * m + j) & 1) { // y
				if (matchy[i * m + j] == -1) ddfs(i * m + j);
			}
			else { // x
				if (matchx[i * m + j] == -1) ddfs(i * m + j);
			}
		}
	
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) 
		if (!went[i * m + j]) ddfs(i * m + j);
	

	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (field[i][j] == 'C') ans++;

	//cerr << matchcnt << '\n';

	cout << ans << '\n';
	for (int i = 0; i < n; i++, cout << '\n') for (int j = 0; j < om; j++) cout << field[i][j];
}
