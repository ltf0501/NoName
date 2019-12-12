#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int mp[100];
ll f[100];
int main() { 
	f[0] = 1;
	for(int i = 1; i <= 70; i++) f[i] = f[i - 1] * i;
	int T;
	scanf("%d", &T);
	while(T--) {
		ll n;
		scanf("%lld", &n);
		vector<int> v, vv;
		for(int i = 2; ; i++) {
			v.push_back(n % i);
			vv.push_back(n % i);
			mp[n % i]++;
			n /= i;
			if(n == 0) break;
		}
		sort(v.begin(), v.end());
		sort(vv.begin(), vv.end());
		vv.resize(unique(vv.begin(), vv.end()) - vv.begin());	
		ll ans = 1;
		int m = int(v.size());
		//for(int x : v) printf("%d ", x);
		for(int i = m - 1; i >= 0; i--) {
			ans *= (i + 2 - max(v[i], 1));
			//printf("%d ", i + 2 - max(v[i], 1)); 
		}
 
		for(int x : vv) ans /= f[mp[x]];
		if(mp[0]) { 
			mp[0]--;
			ll tmp = 1;
			for(int i = m - 1; i >= 1; i--) {
				tmp *= (i + 1 - max(v[i], 1));
				//printf("%d ", i + 1 - max(v[i], 1)); 
			}
			for(int x : vv) tmp /= f[mp[x]];
			ans -= tmp;
			//printf("tmp = %lld\n", tmp);
		}
		printf("%lld\n", ans - 1);
		for(int x : v) mp[x] = 0;
		v.clear();
	}
	return 0;
}
