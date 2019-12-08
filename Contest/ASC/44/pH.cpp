#include <bits/stdc++.h>
using namespace std;
const int kN = 1e2 + 10;
struct P {
	int x, y, id;
	bool operator < (const P& b) const {
		if(x + y != b.x + b.y) return x + y < b.x + b.y;
		if(x != b.x) return x < b.x;
		return y < b.y;
	}
	bool operator == (const P& b) const {
		return x == b.x && y == b.y;
	}
};
string ans[kN];
vector<int> com[kN];
int p[kN], sz[kN];
void init(int n) {
	for(int i = 0; i < n; i++) ans[i] = "";
	for(int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
	for(int i = 0; i < n; i++) {
		com[i].clear();
		com[i].push_back(i);
	}
}
int find(int x) {return p[x] == x ? x : p[x] = find(p[x]);}
int Union(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return -1;
	if(sz[x] < sz[y]) swap(x, y);
	p[y] = x, sz[x] += sz[y];
	for(int i : com[y]) com[x].push_back(i);
	return x;
}
int main() {
#ifdef ONLINE_JUDGE
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);
#endif
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n;
	while(cin >> n && n) {
		init(n);
		priority_queue<P> pq;
		for(int i = 0; i < n; i++) {
			int x, y;
			cin >> x >> y;
			pq.push({x, y, i});
		} 
 
		bool flag = 1;
		while(pq.size() > 1) {
			vector<int> id1, id2;
			P t1 = pq.top(); pq.pop();
			id1.push_back(t1.id);
 
			P t2; 
			int cnt = 1;
			while(!pq.empty() && (t2 = pq.top()) == t1) {
				pq.pop(); cnt++;
				id1.push_back(t2.id);
			}
			//printf("cnt = %d\n", cnt);
 
			if(pq.empty()) {flag = 0; break;}
 
			if(t1.x + t1.y != t2.x + t2.y || abs(t1.x - t2.x) != 1) {
				flag = 0; break;
			}
 
			for(int i = 0; i < cnt; i++) {
				if(pq.empty()) {flag = 0; break;}
				P t3 = pq.top();
				if(!(t3 == t2)) {flag = 0; break;}
				id2.push_back(t3.id);
				pq.pop();
			}
 
			if(!flag) break;
			//printf("t1: %d %d %d\n", t1.x, t1.y, t1.id);
			//printf("t2: %d %d %d\n", t2.x, t2.y, t2.id);
			for(int j = 0; j < cnt; j++) {
				int i1 = id1[j], i2 = id2[j];
				for(int i : com[i1]) ans[i] += '0';
				for(int i : com[i2]) ans[i] += '1';
				int id = Union(i1, i2);
				assert(id != -1);
				pq.push({t1.x - 1, t1.y, id});
			}
		}
		P t = pq.top(); pq.pop();
		if(t.x + t.y != 0) flag = 0;
		if(!flag) {
			cout << "No\n";
			continue;
		}
		cout << "Yes\n";
		for(int i = 0; i < n; i++) reverse(ans[i].begin(), ans[i].end());
		for(int i = 0; i < n; i++) cout << ans[i] << '\n';
	}
	return 0;
}
