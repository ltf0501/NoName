#include <stdio.h>
#include <math.h>
constexpr double pi = acos(-1);

double intersect(double dis, double r, double R) {
	if (dis > r + R) return 0;
	else if (dis < R - r) return 0;
	else {
		double ans, phi, theta, lpart, rpart, lt = (R * R + dis * dis - r * r) / (dis * 2), rt;
		rt = dis - lt;
		theta = acos(lt / R) * 2, phi = acos(rt / r) * 2;
	
		(ans = theta * R - phi * r);
		return -ans;
	}
}

double solve() {
	int m;
	double r, ans, x, y, R;
	scanf("%d%lf", &m, &R);
	ans = 2 * pi * R;
	for (int i = 1; i <= m; i++) {
		scanf("%lf%lf%lf", &x, &y, &r);
		ans += intersect(sqrt(x * x + y * y), r, R);
	}

	return ans;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) printf("%.20lf\n", solve());
} 
