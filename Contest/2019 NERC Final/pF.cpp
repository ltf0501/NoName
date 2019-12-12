#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;
 
typedef pair<int, int> pii;
#define F first
#define S second
int cnt[kN];
int main() {
	vector<int> a, b;
	int n, m, ka, kb;
	scanf("%d%d%d%d", &n, &m, &ka, &kb);
	a.resize(ka), b.resize(kb);
	for(int i = 0; i < ka; i++) scanf("%d", &a[i]);
	for(int i = 0; i < kb; i++) scanf("%d", &b[i]);
	if(ka > m - 1 || kb > n - 1) return puts("No"), 0;
 
	for(int i = 0; i < m - 1 - ka; i++) a.push_back(1);
	for(int i = 0; i < n - 1 - kb; i++) b.push_back(n + 1);
	//for(int x : v) printf("%d ", x); puts("");
 
	for(int i = 0; i < m - 1; i++) cnt[a[i]]++;
	for(int i = 0; i < n - 1; i++) cnt[b[i]]++;
 
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 1; i <= n + m; i++) {
		if(!cnt[i]) pq.push(i);
	}
 
	vector<pii> ans;
	for(int i = 0, j = 0; i < m - 1; i++) {
		int x;
		while((x = pq.top()) <= n && j < n - 1) {
			pq.pop();
			ans.emplace_back(x, b[j]);
			if(--cnt[b[j]] == 0) pq.push(b[j]);
			j++;
		}
		pq.pop();
		ans.emplace_back(x, a[i]);
		if(--cnt[a[i]] == 0) pq.push(a[i]);
	}
	int x = pq.top(); pq.pop();
	int y = pq.top(); pq.pop();
	ans.emplace_back(x, y);
	puts("Yes");
	for(auto p : ans) printf("%d %d\n", p.F, p.S);
}

