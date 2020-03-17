#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define F first
#define S second
vector<pll> ans;
set<ll> s;
void solve(ll n) {
	assert(n >= 0);
	if(n <= 2) return;
	if(s.find(n) != s.end()) return;
	ll x = ceil(sqrt(n - 0.5));
	ll y = x * x - n;
	//printf("n = %lld\n", n);
	//printf("x = %lld y = %lld\n", x, y);
	solve(x), solve(y);
	s.insert(n);
	ans.emplace_back(x, y);
	//printf("%lld^2 - %lld = %lld\n", x, y, x * x - y); 
}
int main() {
	ll n; scanf("%lld", &n);
	solve(n);
	for(auto p : ans) printf("%lld %lld\n", p.F, p.S);
	return 0;
} 
