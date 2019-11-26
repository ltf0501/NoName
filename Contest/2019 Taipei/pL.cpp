#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
const int N=5e3+10;

constexpr long double kEps = 1E-10;

struct P {
	int64_t x, y;
	P(int64_t xx = 0, int64_t yy = 0) : x(xx), y(yy) {}
	P operator -(P b) const { return P(x - b.x, y - b.y); }
	inline int64_t operator^(P b) const { return x * b.y - y * b.x; }
	long double abs() const { return hypot<long double>(x, y); }	
	bool operator<(P b) const {
		return x == b.x ? y < b.y : x < b.x;
	}
	bool operator==(P b) const { return x == b.x && y == b.y; }
};

inline int dcmp(int64_t x){return x>0?1:x==0?0:-1;}
pair<vector<P>, vector<int>> ConvexHull(vector<P> ps){
	vector<P> p;
	vector<int> id;
	for(int i=0;i<int(ps.size());i++){
		while(p.size()>=2&&((ps[i]-p[p.size()-2])^(p[p.size()-1]-p[p.size()-2]))>=0) {
			p.pop_back();
			id.pop_back();
		}
		p.push_back(ps[i]);
		id.push_back(i);
	}
	int t=int(p.size());
	for(int i=int(ps.size())-2;i>=0;i--){
		while(int(p.size())>t&&((ps[i]-p[p.size()-2])^(p[p.size()-1]-p[p.size()-2]))>=0) {
			p.pop_back();
			id.pop_back();
		}
		p.push_back(ps[i]);
		id.push_back(i);
	}
	p.pop_back();
	id.pop_back();
	return {p, id};
}
void solve(){
	int n; cin >> n;
	vector<P> p_ori(n);
	for (int i = 0; i < n; i++) cin >> p_ori[i].x >> p_ori[i].y;
	sort(p_ori.begin(), p_ori.end());
	auto [p, id] = ConvexHull(p_ori);
	n = int(p.size());
	int64_t ans = 0;
	if (n < 4) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				for (int k = 0; k < int(p_ori.size()); k++) {
					if (k == id[i] || k == id[j]) continue;
					for (int l = 0; l < int(p_ori.size()); l++) {
						if (l == id[i] || l == id[j]) continue;
						if(l==k)continue;
						int64_t res = ((p[j] - p[i]) ^ (p_ori[k] - p[i])) + ((p_ori[k] - p[i]) ^ (p_ori[l] - p[i]));
						ans = max(ans, abs(res));
					}
				}
			}
		}
		cout << ans / 2;
		if (ans & 1) cout << ".5";
		cout << '\n';
		return;
	}
	for (int i = 0; i < n; i++) {
		int ii=i+n-1;
		for (int j = i + 2, k1 = i+1, k2 = j + 1, rj = j; j < ii; j++,rj++) {
			if(rj>=n)rj-=n;
			P temp=p[rj]-p[i];
			while (k1 < j-1 && dcmp((p[k1%n]-p[i])^temp)==dcmp((p[(k1+1)%n]-p[k1%n])^temp)) {
				++k1;
			}
			while (k2 <= j) ++k2;
			while (k2 < ii && dcmp((p[k2%n]-p[i])^temp)==dcmp((p[(k2+1)%n]-p[k2%n])^temp)) {
				++k2;
			}
			//cerr << i << ' ' << j << ' ' << k1 << ' ' << k2 << ' ' << n << endl;
			ans = max(ans, abs(((p[rj] - p[i]) ^ (p[k1 % n] - p[i])) + ((p[k2 % n] - p[i]) ^ (p[rj] - p[i]))));
		}
	}
	cout << ans / 2;
	if (ans & 1) cout << ".5";
	cout << '\n';
}
int main(){
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--)solve();
}
