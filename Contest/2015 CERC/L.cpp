#include <bits/stdc++.h>
using namespace std;
const int kN = 105;
typedef pair<int, int> pii;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int kInf = 1e9;
#define F first
#define S second

int n, m;
char s[kN][kN];
set<pii> vis[kN][kN];
queue<pii> q;
int normal(int x, int n) {
	x %= n;
	if(x < 0) x += n;
	return x;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%s", s[i]);

	q.emplace(0, 0);
	vis[0][0].insert(make_pair(0, 0));
	int cnt = 1000000;
	while(!q.empty()) {
		if(!cnt) break;
		cnt--;
		auto p = q.front(); q.pop(); 

		for(int i = 0; i < 4; i++) {
			int x = p.F + dx[i], y = p.S + dy[i];
			int xx = normal(x, n), yy = normal(y, m);
			if(s[xx][yy] == '#') continue;
			if(vis[xx][yy].find(make_pair(x, y)) != vis[xx][yy].end()) continue;
			vis[xx][yy].insert(make_pair(x, y));
			q.emplace(x, y);
		}
	}

	int type = -1;
	pii delta;
	if(q.empty()) type = 0;
	else {
		set<pii> tmp;
		auto it = vis[0][0].begin();
		for(++it; it != vis[0][0].end(); it++) {
			auto ii = prev(it);
			tmp.insert(make_pair(it->F - ii->F, it->S - ii->S));
		}
		if(tmp.size() == 1) type = 1, delta = *tmp.begin();
		else type = 2;
	}

	//printf("type = %d\n", type);
	//if(type == 1) printf("delta = (%d, %d)\n", delta.F, delta.S);
	int T; scanf("%d", &T);
	while(T--) {
		int x, y; scanf("%d%d", &x, &y);
		int xx = normal(x, n), yy = normal(y, m);
		bool flag = 0;
		if(type == 0) {
			flag = vis[0][0].find(make_pair(x, y)) != vis[0][0].end();
		}
		else if(type == 1) {
			//printf("(%d, %d): ", xx, yy);
			//for(auto p : vis[xx][yy]) {
			//	printf("(%d, %d), ", p.F, p.S);
			//}
			//puts("");

			int l = -kInf, r = kInf;
			while(r - l > 100) {
				int t1 = l + (r - l) / 3;
				int t2 = r - (r - l) / 3;
				long long x1 = x + 1LL * delta.F * t1;
				long long y1 = y + 1LL * delta.S * t1;
				long long x2 = x + 1LL * delta.F * t2;
				long long y2 = y + 1LL * delta.S * t2;
				if(abs(x1) + abs(y1) < abs(x2) + abs(y2)) r = t2;
				else l = t1;
			}
			//printf("(l, r) = (%d, %d)\n", l, r);
			//printf("find: ");
			for(int i = l; i <= r; i++) {
				//printf("(%d, %d), ", x + i * delta.F, y + i * delta.S);
				if(vis[xx][yy].find(make_pair(x + i * delta.F, y + i * delta.S)) != vis[xx][yy].end()) flag = 1;
			}
			//puts("");
		}
		else {
			flag = !vis[xx][yy].empty();
		}
		
		puts(flag ? "yes" : "no");
	}
	return 0;
} 
