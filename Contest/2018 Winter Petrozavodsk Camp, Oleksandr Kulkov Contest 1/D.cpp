#include <bits/stdc++.h>
using namespace std;
const int kMod = 1e9 + 7;

int a[130], b[130];
int k; 

int pw(int x, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * x % kMod;
		n >>= 1, x = 1LL * x * x % kMod;
	}
	return res;
}
int Inv(int x) {return pw(x, kMod - 2);}

vector<vector<int>> Gauss(vector<vector<int>> &v) {
	if (v.empty()) return {};
	int n = int(v.size()), m = int(v[0].size());
	vector<vector<int>> vv(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		vv[i][i] = 1;
	}
	for (int i = 0; i < m; i++) {
		int p = -1;
		for (int j = i; j < n; j++) {
			if (!v[j][i]) continue;
			p = j;
			break;
		}
		if (p == -1) continue;
		for (int j = 0; j < m; j++) {
			swap(v[p][j], v[i][j]);
			swap(vv[p][j], vv[i][j]);
		}
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			int x = (1LL * v[j][i] * Inv(v[i][i])) % kMod;
			for (int k = 0; k < m; k++) {
				v[j][k] -= (1LL * x * v[i][k]) % kMod; 
				vv[j][k] -= (1LL * x * vv[i][k]) % kMod; 
				v[j][k] %= kMod;
				if (v[j][k] < 0) v[j][k] += kMod;
				vv[j][k] %= kMod;
				if (vv[j][k] < 0) vv[j][k] += kMod;
			}
		}
	}
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			int x = (1LL * v[j][i] * Inv(v[i][i])) % kMod;
			for (int k = 0; k < m; k++) {
				v[j][k] -= (1LL * x * v[i][k]) % kMod; 
				vv[j][k] -= (1LL * x * vv[i][k]) % kMod; 
				v[j][k] %= kMod;
				if (v[j][k] < 0) v[j][k] += kMod;
				vv[j][k] %= kMod;
				if (vv[j][k] < 0) vv[j][k] += kMod;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		int x = Inv(v[i][i]);
		for (int j = 0; j < n; j++) {
			vv[i][j] = (1LL * vv[i][j] * x) % kMod;
		}
	}

	return vv;
}

void add(int &x, int y) {
	x += y;
	if(x >= kMod) x -= kMod;
}

vector<int> Mul(const vector<int> &p, const vector<int> &q) {
	vector<int> res(p.size() + q.size() - 1, 0);
	//printf("p: "); for(int x : p) printf("%d ", x); puts("");
	//printf("q: "); for(int x : q) printf("%d ", x); puts("");
	for(int i = 0; i < p.size(); i++) {
		for(int j = 0; j < q.size(); j++) {
			add(res[i + j], 1LL * p[i] * q[j] % kMod);
		}
	}

	//printf("res1: "); for(int x : res) printf("%d ", x); puts("");

	for(int i = int(res.size()) - 1; i >= k; i--) {
		for(int j = 1; j <= k; j++) add(res[i - j], 1LL * res[i] * a[j] % kMod);
	}

	//printf("res2: "); for(int x : res) printf("%d ", x); puts("");

	while(res.size() > k) res.pop_back();
	return res;
}
vector<int> fpow(int n) { // mod x^k - (a_k + a_{k - 1}x + ... + a_1x^{k - 1})
	vector<int> res;
	res.push_back(1);
	vector<int> now(2, 0); now[1] = 1;
	while(n) {
		if(n & 1) res = Mul(res, now);
		n >>= 1;
		now = Mul(now, now);
	}
	while(res.size() > k) res.pop_back();
	while(res.size() < k) res.push_back(0);
	return res;
}
int main() {
	scanf("%d", &k);
	for(int i = 1; i <= k; i++) scanf("%d", &a[i]);
	fpow(3);
	for(int i = 1; i <= k; i++) scanf("%d", &b[i]);
	vector<int> ans = fpow(b[k]);
	vector<vector<int>> v(k);
	for(int i = 0; i < k; i++) v[i] = fpow(b[k] - b[i + 1]);
	vector<vector<int>> A(k, vector<int>(k));
	for(int i = 0; i < k; i++)
		for(int j = 0; j < k; j++) A[i][j] = v[j][i];
	//printf("A:\n");
	//for(int i = 0; i < k; i++) {
	//	for(int j = 0; j < k; j++) printf("%d ", A[i][j]); puts("");
	//}
	// C = A^-1 * ans
	vector<int> c(k);
	vector<vector<int>> AA = Gauss(A);
	//printf("AA:\n");
	//for(int i = 0; i < k; i++) {
	//	for(int j = 0; j < k; j++) printf("%d ", AA[i][j]); puts("");
	//}
	for(int i = 0; i < k; i++) {
		for(int j = 0; j < k; j++) add(c[i], 1LL * AA[i][j] * ans[j] % kMod);
	}
	for(int i = 0; i < k; i++) printf("%d ", c[i]); puts("");
	return 0;
} 
