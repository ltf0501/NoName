#include <bits/stdc++.h>
using namespace std;
const int kN = 6e5 + 10;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
typedef pair<int, int> pii;
#define F first
#define S second

int m, n;
char c[kN];

int p[kN];
int x[kN], y[kN];
int Find(int x) {return p[x] == x ? x : p[x] = Find(p[x]);}
int main() {
	map<char, int> mv;
	mv['L'] = 0, mv['R'] = 1, mv['D'] = 2, mv['U'] = 3;
	scanf("%d", &m);
	scanf("%s", c);
	scanf("%d", &n);

	map<pii, int> mp;
	for(int i = 0; i < n; i++) p[i] = i;
	for(int i = 0; i < n; i++) {
		scanf("%d%d", &x[i], &y[i]);
		if(mp.find(make_pair(x[i], y[i])) == mp.end()) {
			mp[make_pair(x[i], y[i])] = i;
		}
		else {
			int v = mp[make_pair(x[i], y[i])];
			p[i] = v;
		}
	}

	int nx = 0, ny = 0;
	for(int i = 0; i < m; i++) {
		int dir = mv[c[i]];
		nx += dx[dir], ny += dy[dir];
		//printf("mv: (%d, %d)\n", dx[dir], dy[dir]);
		if(mp.find(make_pair(nx, ny)) == mp.end()) continue;

		int v = mp[make_pair(nx, ny)];
		//printf("v = %d\n", v);
		int tx = nx + dx[dir], ty = ny + dy[dir];
		if(mp.find(make_pair(tx, ty)) == mp.end()) {
			x[v] = tx, y[v] = ty;
			mp[make_pair(tx, ty)] = v;
			//printf("change %d to (%d, %d)\n", v, x[v], y[v]);
		}
		else {
			int u = mp[make_pair(tx, ty)];
			p[v] = u;
			//printf("merge %d to %d\n", v, u);
		}
		mp.erase(make_pair(nx, ny));
	}

	//printf("nx = %d, ny = %d\n", nx, ny);
	for(int i = 0; i < n; i++) {
		int id = Find(i);
		//printf("i = %d: id = %d\n", i, id);
		printf("%d %d\n", x[id] - nx, y[id] - ny);
	}
	return 0;
} 
