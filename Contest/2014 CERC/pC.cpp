#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
constexpr int kN = int(1E3 + 10);
typedef long long int ll;
int gcd(int a, int b) {return b == 0 ? a :gcd(b, a % b);}
int x[kN], y[kN], rad[kN];
bool went[kN], flip[kN];
vector<int> graph[kN];
 
bool connect(int l, int r) {
	ll X = x[l] - x[r], Y = y[l] - y[r], R = rad[l] + rad[r];
	return R * R >= (X * X + Y * Y);
}
 
void dfs(int pos, int from) {
	went[pos] = true;
	flip[pos] = !flip[from];
	for (int i : graph[pos]) if (!went[i]) dfs(i, pos);
	return ;
}
 
void solve() {
	int n, l, r, tmp;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &x[i], &y[i], &rad[i]);
	flip[0] = true;
	flip[1] = false;
	went[1] = true;
	for (int i = 2; i <= n; i++) went[i] = false;
	for (int i = 2; i <= n; i++) flip[i] = false;
	for (int i = 1; i <= n; i++) graph[i].clear();
	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) 
		if (connect(i, j)) {
			graph[i].PB(j);
			graph[j].PB(i);
		}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) if (!went[i]) printf("not moving\n");
		else {
			l = rad[1];
			r = rad[i];
			tmp = gcd(l, r);
			l /= tmp;
			r /= tmp;
			if (r == 1) printf("%d ", l);
			else printf("%d/%d ", l, r);
			if (flip[i]) printf("counter");
			printf("clockwise\n");
		}
	return ;
}
 
int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
}
