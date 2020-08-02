#include <bits/stdc++.h>
using namespace std;
const double Eps = 1e-8;
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	pair<double, double> p[4];
	for(int i = 0; i < 4; i++) cin >> p[i].first >> p[i].second;
	
	double ans = 0.0;
	vector<int> dots = {3, 6, 4, 1};
	for(int i = 0; i < 4; i++) {
		vector<pair<double, double>> tmp;	

		for(int j = 0; j < 4; j++) {
			if(p[j].first >= 0.5) tmp.push_back(p[j]);
			int jj = (j + 1) % 4;
			if((p[j].first - 0.5) * (p[jj].first - 0.5) < -Eps) {
				double y = p[j].second + (0.5 - p[j].first) * (p[jj].second - p[j].second) / (p[jj].first - p[j].first);
				tmp.emplace_back(0.5, y);
			}
		}

		double area = 0.0;
		for(int j = 0; j < int(tmp.size()); j++) {
			int jj = (j + 1) % int(tmp.size());
			area += tmp[j].first * tmp[jj].second - tmp[jj].first * tmp[j].second;
		}

		area = fabs(area) / 2.0;
		ans += area * dots[i] * 5.0;

		for(int j = 0; j < 4; j++) {
			swap(p[j].first, p[j].second);
			p[j].second *= -1.0;
		}
	}

	ans += 100.0 * 5.0;
	ans /= 124.0;
	cout << fixed << setprecision(12) << ans << '\n';
} 
