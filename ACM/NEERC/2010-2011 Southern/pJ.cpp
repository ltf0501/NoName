#include <bits/stdc++.h>
using namespace std;
const int maxn = 405;
const double INF = 1e18;
int a[maxn];
int n;
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	double ans = INF;
	int id = -1;
	double d = -1;
	for(int i = 1; i <= n; i++) {
		double l = 0, r = 20000;
		for(int t = 1; t <= 80; t++) {
			double l1 = (l + l + r) / 3;
			double l2 = (l + r + r) / 3;
			double dis1 = 0;
			for(int j = 1; j <= n; j++)
				dis1 += abs(a[j] - (a[i] + (j - i) * l1));
			double dis2 = 0;
			for(int j = 1; j <= n; j++)
				dis2 += abs(a[j] - (a[i] + (j - i) * l2));
			if(dis1 > dis2) l = l1;
			else r = l2;
		}	
		double dis = 0;
		for(int j = 1; j <= n; j++)
			dis += abs(a[j] - (a[i] + (j - i) * l));
		if(ans > dis) 
	       		id = i, d = l, ans = dis;	
	}
	printf("%.9f\n", ans);
	for(int i = 1; i <= n; i++)
		printf("%.9f ", a[id] + (i - id) * d);
	puts("");
	return 0;
}
