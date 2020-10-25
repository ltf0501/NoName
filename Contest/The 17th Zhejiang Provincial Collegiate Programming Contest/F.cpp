#include <bits/stdc++.h>
#include <fenv.h>
using namespace std;
const int kN = 205;
const double kEps = 1e-9;
#define F first
#define S second

int w[2][kN], b[2];
int n; 

int sign(double x) {
	if(fabs(x) < kEps) return 0;
	return x > 0 ? 1 : -1;
}
bool gao() {
	bool res = 1;
	for(int i = 1; i <= n; i++) {
		if((w[0][i] == 0) ^ (w[1][i] == 0)) return 0;
	}
	if((b[0] == 0) ^ (b[1] == 0)) return 0;
	pair<int, int> p;
	for(int i = 1; i <= n; i++) if(w[0][i]) {
		p = make_pair(w[0][i], w[1][i]);
		break;
	}
	for(int i = 1; i <= n; i++) if(w[0][i]) {
		if(p.F * w[1][i] != p.S * w[0][i]) return 0;
	}
	if(b[0]) {
		if(p.F * b[1] != p.S * b[0]) return 0;
	}

	if((p.F > 0) ^ (p.S > 0)) return 0;
	return 1;
}
int main() {
	//feenableexcept(FE_DIVBYZERO);
	int T; scanf("%d", &T);
	mt19937 rng;
	while(T--) {
		//printf("T = %d\n", T);
		//for(int i = 1; i <= n; i++) w[0][i] = uniform_int_distribution<int>(-100, 100)(rng);
		//b[0] = uniform_int_distribution<int>(-100, 100)(rng);
		//for(int i = 1; i <= n; i++) w[1][i] = uniform_int_distribution<int>(-100, 100)(rng);
		//b[1] = uniform_int_distribution<int>(-100, 100)(rng);
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &w[0][i]);
		scanf("%d", &b[0]);
		for(int i = 1; i <= n; i++) scanf("%d", &w[1][i]);
		scanf("%d", &b[1]);

		bool flag0 = 0;
		for(int i = 1; i <= n; i++) flag0 |= (w[0][i] != 0);
		if(!flag0 && !b[0]) {
			puts("No"); continue;
		}
		bool flag1 = 0;
		for(int i = 1; i <= n; i++) flag1 |= (w[1][i] != 0);
		if(!flag1 && !b[1]) {
			puts("No"); continue;
		}

		if(!flag0 && !flag1) {
			if(b[0] * b[1] > 0) {
				puts("No");
			}
			else {
				for(int i = 0; i < n; i++) printf("%d ", 0); puts("");
			} 
			continue;
		}

		if(gao()) {
			puts("No");
			continue;
		}

		if(!flag0) {
			for(int i = 1; i <= n; i++) swap(w[0][i], w[1][i]);
			swap(b[0], b[1]);
		}
		//if(!flag0) swap(w[0], w[1]), swap(b[0], b[1]);
		//for(int i = 1; i <= n; i++) printf("%d ", w[0][i]); printf("%d ", b[0]); puts("");
		//for(int i = 1; i <= n; i++) printf("%d ", w[1][i]); printf("%d ", b[1]); puts("");
		vector<int> non_zero;
		vector<double> x(n + 1);
		for(int i = 1; i <= n; i++) if(w[0][i]) non_zero.push_back(i);

		auto Check = [&](vector<double> &x) {
			double tmp0 = b[0];
			for(int i = 1; i <= n; i++) tmp0 += x[i] * w[0][i];
			double tmp1 = b[1];
			for(int i = 1; i <= n; i++) tmp1 += x[i] * w[1][i];
			return sign(tmp0) * sign(tmp1) == -1;
		};
		int tt = 2000;
		while(true) {
			int id = uniform_int_distribution<int>(0, int(non_zero.size()) - 1)(rng);
			vector<double> v(int(non_zero.size()) - 1);
			for(int i = 0; i < int(non_zero.size()) - 1; i++) v[i] = uniform_real_distribution<double>(-50.0, 50.0)(rng);

			double sum = 0;
			for(int i = 0, j = 0; i < int(non_zero.size()); i++) if(i != id) {
				x[non_zero[i]] = v[j++];
				sum += x[non_zero[i]] * w[0][non_zero[i]];
			}
			x[non_zero[id]] = (-sum - b[0]) / w[0][non_zero[id]];
			//cerr << "non_zero[id] = " << non_zero[id] << '\n';
			//for(int i = 1; i <= n; i++) cerr << x[i] << ' '; cerr << '\n';

			vector<double> mv(n + 1);
			int num = 10;
			while(num--) {
				double len = 0;
				for(int i = 1; i <= n; i++) mv[i] = uniform_real_distribution<double>(0, 1)(rng), len += mv[i] * mv[i];

				len = sqrt(len);
				for(int i = 1; i <= n; i++) mv[i] = mv[i] / len * 1e-6;
				vector<double> xx(n + 1);

				int flag = 1;
				for(int o = 0; o < 2; o++) {
					for(int i = 1; i <= n; i++) xx[i] = x[i] + flag * mv[i];
					if(Check(xx)) {
						for(int i = 1; i <= n; i++) printf("%.10f ", xx[i]); puts("");
						goto End;
					}
					flag *= -1;
				} 
			} 
		}
End: ;
	}
	return 0;
} 
