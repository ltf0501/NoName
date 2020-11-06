#include <bits/stdc++.h>
using namespace std;
constexpr int kN = int(1E2 + 10), kInf = int(1E9 + 10);
#define PB push_back
#define F first
#define S second
constexpr int dx[6] = {1, -1, 0, 0, 0, 0};
constexpr int dy[6] = {0, 0, 1, -1, 0, 0};
constexpr int dz[6] = {0, 0, 0, 0, 1, -1};
constexpr int ddx[8] = {1, 1, 1, -1, 1, -1, -1, -1};
constexpr int ddy[8] = {1, 1, -1, 1, -1, 1, -1, -1};
constexpr int ddz[8] = {1, -1, 1, 1, -1, -1, 1, -1};
string board[kN][kN];
bool b[kN][kN][kN];
int dis[kN][kN][kN], cnt[kN][kN][kN];
vector<tuple<int, int, int>> ppl, station;
int ABS(int n) {return n >= 0 ? n : -n;}
tuple<int, int, int> better(tuple<int, int, int> a, tuple<int, int, int> b, int idx) {
	int vala = get<0>(a) * ddz[idx] + get<1>(a) * ddx[idx] + get<2>(a) * ddy[idx];
	int valb = get<0>(b) * ddz[idx] + get<1>(b) * ddx[idx] + get<2>(b) * ddy[idx];
	if (vala < valb) return a;
	else return b;
}
bool ok(int len, int z, int x, int y) {
	vector<tuple<int, int, int>> v;
	tuple<int, int, int> now;
	for (tuple<int, int, int> i : ppl) if (dis[get<0>(i)][get<1>(i)][get<2>(i)] > len) v.PB(i);
	if (v.empty()) return true;
	for (int i = 0; i < z; i++) for (int j = 0; j < x; j++) for (int k = 0; k < y; k++) cnt[i][j][k] = 0;
	for (int j = 0; j < 8; j++) {
		now = v[0];
		for (tuple<int, int, int> i : v) now = better(now, i, j);
		for (int nz = 0; nz < z; nz++) for (int nx = 0; nx < x; nx++) for (int ny = 0; ny < y; ny++) 
			if (ABS(nz - get<0>(now)) + ABS(nx - get<1>(now)) + ABS(ny - get<2>(now)) <= len) cnt[nz][nx][ny]++;
	}
	for (int i = 0; i < z; i++) for (int j = 0; j < x; j++) for (int k = 0; k < y; k++) 
		if (cnt[i][j][k] == 8 && b[i][j][k]) return true;
	return false;
}
void solve(int z, int x, int y) {
	int l, r, mid, ndis;
	tuple<int, int, int> cur, nxt;
	queue<pair<tuple<int, int, int>, int>> q;
	for (int i = 0; i < z; i++) for (int j = 0; j < x; j++) cin >> board[i][j];
	ppl.clear();
	station.clear();
	for (int i = 0; i < z; i++) for (int j = 0; j < x; j++) for (int k = 0; k < y; k++) {
		if (board[i][j][k] == '*') ppl.PB(make_tuple(i, j, k));
		else if (board[i][j][k] == '@') station.PB(make_tuple(i, j, k));
		b[i][j][k] = (board[i][j][k] == '.');
	}
	for (tuple<int, int, int> i : station) q.push(make_pair(i, 0));
	for (int i = 0; i < z; i++) for (int j = 0; j < x; j++) for (int k = 0; k < y; k++) dis[i][j][k] = kInf;
	while (!q.empty()) {
		cur = q.front().F;
		ndis = q.front().S;
		q.pop();
		for (int i = 0; i < 6; i++) {
			nxt = {get<0>(cur) + dz[i], get<1>(cur) + dx[i], get<2>(cur) + dy[i]};
			if (0 <= get<0>(nxt) && get<0>(nxt) < z &&
					0 <= get<1>(nxt) && get<1>(nxt) < x &&
					0 <= get<2>(nxt) && get<2>(nxt) < y && 
					dis[get<0>(nxt)][get<1>(nxt)][get<2>(nxt)] == kInf) {
				dis[get<0>(nxt)][get<1>(nxt)][get<2>(nxt)] = ndis + 1;
				q.push(make_pair(nxt, ndis + 1));
			}
		}
	}
	l = 0, r = x + y + z;
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (ok(mid, z, x, y)) r = mid;
		else l = mid;
	}
	cout << r << '\n';
	return ;
}

int main() {
	int z, x, y;
	while (cin >> z >> x >> y) solve(z, x, y);
} 
