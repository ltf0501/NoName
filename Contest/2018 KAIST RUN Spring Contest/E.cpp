#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 3e5 + 10;
typedef pair<ll, int> pii;
#define F first
#define S second

int n;
pii a[kN];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%lld%d", &a[i].F, &a[i].S), a[i].F += a[i].S;
	sort(a + 1, a + n + 1);
	priority_queue<int> pq;
	ll now = 0;
	for(int i = 1; i <= n; i++) {
		now += a[i].S;
		pq.push(a[i].S);
		if(now > a[i].F) {
			now -= pq.top(); pq.pop();
		}
	}
	printf("%d\n", int(pq.size()));
} 
