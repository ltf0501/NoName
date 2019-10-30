#include <bits/stdc++.h>
using namespace std;
const int maxn =1e6 + 10; 
int cnt[maxn];
vector<int> a, b;
int main() {
#ifdef ONLINE_JUDGE
	freopen("equal.in", "r", stdin);
	freopen("equal.out", "w", stdout); 
#endif
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		cnt[x]++;
	}
	for(int i = 1; i < maxn; i++) {
		if(cnt[i]) {
			a.push_back(cnt[i]);
			for(int j = 2 * i; j < maxn; j += i) {
				if(cnt[j]) {
					b.push_back(cnt[i]);
					break;
				}
			}
		}
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	//printf("a: ");
	//for(int x : a) printf("%d ", x); puts("");
	//printf("b: ");
	//for(int x : b) printf("%d ", x); puts("");
	int ans = (int)a.size();
	int a_iter = 0, b_iter = 0;
	int a_sz = 0, b_sz = 0;
	for(int i = 0; i <= n; i++) {
		while(a_iter < (int)a.size() && a_sz + a[a_iter] <= i) 
			a_sz += a[a_iter++];
		while(b_iter < (int)b.size() && b_sz + b[b_iter] <= i) 
			b_sz += b[b_iter++];
	//	printf("a_iter = %d, b_iter = %d\n", a_iter, b_iter);
			printf("%d ", ans - max(a_iter - 1, b_iter));
	}
	puts("");
	return 0;
}

