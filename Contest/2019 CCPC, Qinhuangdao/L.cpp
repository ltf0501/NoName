#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const ll kInf = 1e16;
#define F first
#define S second

vector<ll> vl, vr;
vector<pii> v;

bool Check(ll T) {
	ll cur = 1;
	int i = 0, j = 0;
	priority_queue<ll> pq;
	while(cur <= T) {
		while(j < int(v.size()) && v[j].F <= cur) pq.push(v[j++].S);
		if(i < int(vl.size()) && vl[i] <= cur) {
			i++, cur++;
		}
		else {
			if(pq.empty()) {
				cur = kInf;
				if(i < int(vl.size())) cur = min(cur, vl[i]);
				if(j < int(v.size())) cur = min(cur, v[j].F);
			}
			else {
				pq.pop();
				cur++;
			}
		}
	}

	if(i != int(vl.size())) return 0;
	
	vector<ll> vv;
	while(!pq.empty()) vv.push_back(pq.top()), pq.pop();
	while(j < int(v.size())) vv.push_back(v[j++].S);
	for(ll x : vr) vv.push_back(x);
	sort(vv.begin(), vv.end(), greater<ll>());

	ll mx = 0;
	for(int i = 0; i < int(vv.size()); i++) mx = max(mx, vv[i] + i);
	return mx <= T;
}
int main() {
	int n, k;
	ll l1, l2, l3;
	scanf("%d%lld%lld%lld%d", &n, &l1, &l2, &l3, &k);

	for(int i = 0; i < k; i++) {
		int type;
		ll x, y;
		scanf("%d%lld%lld", &type, &y, &x); x--;
		if(type == 1) vl.push_back(y + l1 - x); 
		else if(type == 3) vr.push_back(y + x - 1 - l1 - l2);
		else v.emplace_back(y + x - l1, y + l1 + l2 + 1 - x);
	}

	sort(vl.begin(), vl.end());
	sort(v.begin(), v.end());
	sort(vr.begin(), vr.end());

	ll l = 0, r = kInf;
	while(l < r) {
		ll m = (l + r) >> 1;
		if(Check(m)) r = m;
		else l = m + 1;
	}
	printf("%lld\n", l);
} 
