#include <bits/stdc++.h>
using namespace std;
const int kN = 2e3 + 10;
vector<pair<int, int>> mp[kN], tmp;

pair<int, int> p[kN];
int n, q;

pair<int, int> normal(pair<int, int> r) {
	int x = r.first, y = r.second;
	int g = __gcd(x, y);
	//printf("x = %d, y = %d, g = %d\n", x, y, g);
	x /= g, y /= g;
	if(x < 0) x = -x, y = -y;
	else if(x == 0) y = abs(y);
	return make_pair(x, y);
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; i++) scanf("%d%d", &p[i].first, &p[i].second);
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) if(i != j) {
			mp[i].push_back(normal(make_pair(p[i].first - p[j].first, p[i].second - p[j].second)));
		}
		sort(mp[i].begin(), mp[i].end());
	}

	//for(int i = 0; i < n; i++) {
	//	printf("%d: ", i);
	//	for(auto p : mp[i]) printf("(%d, %d), ", p.first, p.second);
	//	puts("");
	//}
	while(q--) {
		int x, y; scanf("%d%d", &x, &y);
		tmp.clear();
		int ans = 0;
		for(int i = 0; i < n; i++) {
			//printf("i = %d:\n", i);
			int xx = x - p[i].first, yy = y - p[i].second;
			//printf("xx = %d, yy = %d\n", xx, yy);
			pair<int, int> t = normal(make_pair(yy, -xx));
			//printf("t = (%d, %d) ", t.first, t.second);
			int k1 = lower_bound(mp[i].begin(), mp[i].end(), t) - mp[i].begin();
			int k2 = upper_bound(mp[i].begin(), mp[i].end(), t) - mp[i].begin();
			ans += k2 - k1;
			//printf("tot = %d\n", k2 - k1);
			
			tmp.push_back(normal(make_pair(xx, yy)));
		}
		sort(tmp.begin(), tmp.end());
		//printf("tmp: ");
		//for(auto p : tmp) printf("(%d, %d), ", p.first, p.second);
		//puts("");
		
		int sum = 0;
		for(auto p : tmp) {
			p = normal(make_pair(p.second, -p.first));
			int k1 = lower_bound(tmp.begin(), tmp.end(), p) - tmp.begin();
			int k2 = upper_bound(tmp.begin(), tmp.end(), p) - tmp.begin();
			sum += k2 - k1;
		}
		//printf("sum = %d\n", sum);
		sum >>= 1;
		ans += sum;

		printf("%d\n", ans);
	}
	return 0;
} 
