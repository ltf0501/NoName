#include <stdio.h>
#include <math.h>
#include <tuple>
#include <queue>
using namespace std;

constexpr int kN = int(2E3 + 10);


bool went[kN];
double dis[kN][kN], sz[kN], x[kN], y[kN];
int lst[kN][kN];

double meet1(int l, int r) {
	double X = x[l] - x[r], Y = y[l] - y[r];
	return sqrt(X * X + Y * Y) - sz[r];

}

double meet2(int l, int r) {
	double X = x[l] - x[r], Y = y[l] - y[r];
	return sqrt(X * X + Y * Y) / 2;
}

int main() {
	int n, t = 0;
	double ans = 0;
	tuple<double, int, int, int> cur;
	priority_queue<tuple<double, int, int, int>, vector<tuple<double, int, int, int>>, greater<tuple<double, int, int, int>>> pq;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lf%lf", &x[i], &y[i]);
	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
		dis[i][j] = dis[j][i] = meet2(i, j);
		lst[i][j] = lst[j][i] = t;
		pq.push({dis[i][j], lst[i][j], i, j});
	}
	while (!pq.empty()) {
		cur = pq.top();
		pq.pop();
		if (lst[get<2>(cur)][get<3>(cur)] > get<1>(cur)) continue;
		t++;
		if (!went[get<2>(cur)]) {
			sz[get<2>(cur)] = get<0>(cur);
			went[get<2>(cur)] = true;
			for (int i = 1; i <= n; i++) if (i != get<2>(cur) && i != get<3>(cur)) {
				if (!went[i]) {
					dis[i][get<2>(cur)] = dis[get<2>(cur)][i] = meet1(i, get<2>(cur));
					lst[i][get<2>(cur)] = lst[get<2>(cur)][i]= t;
					pq.push({dis[i][get<2>(cur)], lst[i][get<2>(cur)], i, get<2>(cur)});
				}
			}
		}	
		if (!went[get<3>(cur)]) {
			sz[get<3>(cur)] = get<0>(cur);
			went[get<3>(cur)] = true;
			for (int i = 1; i <= n; i++) if (i != get<2>(cur) && i != get<3>(cur)) {
				if (!went[i]) {
					dis[i][get<3>(cur)] = dis[get<3>(cur)][i] = meet1(i, get<3>(cur));
					lst[i][get<3>(cur)] = lst[get<3>(cur)][i] = t;
					pq.push({dis[i][get<3>(cur)], lst[i][get<3>(cur)], i, get<3>(cur)});
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) ans += sz[i] * sz[i];
	ans *= acos(-1);
	printf("%.20lf\n", ans);
}
