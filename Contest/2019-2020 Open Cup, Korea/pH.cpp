#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;
 
constexpr int kN = int(3E5 + 10);
struct BIT {
	int val[kN];
	void init() {memset(val, 0, sizeof(val));}
	void add(int pos, int x) {
		while (pos < kN) {
			val[pos] += x;
			pos += pos & -pos;
		}
		return ;
	}
	int ask(int pos) {
		int ans = 0;
		while (pos) {
			ans += val[pos];
			pos ^= pos & -pos;
		}
		return ans;
	}
};
int a[kN], b[kN], pa[kN], pb[kN], pos[kN];
BIT bit;
long long int solve(int n) {
	//printf("pa : \n");
	//for (int i = 1; i <= n; i++) printf("%d ", pa[i]);
	//printf("\n");
	//printf("pb : \n");
	//for (int i = 1; i <= n; i++) printf("%d ", pb[i]);
	//printf("\n");
	long long int ans = 0;
	priority_queue<int, vector<int>, greater<int>> pq0, pq1;
	for (int i = 1; i <= n; i++) if (pa[i] == 1) pq1.push(i);
	else pq0.push(i);
	bit.init();
	for (int i = 1; i <= n; i++) bit.add(i, 1);
	for (int i = 1; i <= n; i++) if (pb[i] == 1) {
		ans += bit.ask(pq0.top()) - i;
		bit.add(1, 1);
		bit.add(pq0.top(), -1);
		pq0.pop();
	}
	else {
		ans += bit.ask(pq1.top()) - i;
		bit.add(1, 1);
		bit.add(pq1.top(), -1);
		pq1.pop();
	}
	return ans;
}
 
int main() {
	int n, amid, bmid;
	long long int ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	if (n & 1) {
		for (int i = 1; i <= n; i++) pa[i] = a[i] > (n >> 1) ? 1 : 0;
		for (int i = 1; i <= n; i++) pb[i] = b[i] > (n >> 1) ? 1 : 0;
		for (int i = 1; i <= n; i++) if (a[i] == (n >> 1) + 1) amid = i;
		for (int i = 1; i <= n; i++) if (b[i] == (n >> 1) + 1) bmid = i;
		pa[amid] = 1, pb[bmid] = 0;
		ans = solve(n);
		pa[amid] = 0, pb[bmid] = 1;
		ans = min(ans, solve(n));
		printf("%lld\n", ans);
	}
	else {
		for (int i = 1; i <= n; i++) pa[i] = a[i] > (n >> 1) ? 1 : 0;
		for (int i = 1; i <= n; i++) pb[i] = b[i] > (n >> 1) ? 1 : 0;
		printf("%lld\n", solve(n));
	}
}
