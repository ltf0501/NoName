#include <bits/stdc++.h>
using namespace std;
const int kMod = 1e9 + 7;

int n;
struct Matrix{
	int x[4][4];
	Matrix() {
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++) x[i][j] = 0;
	}
	Matrix operator*(const Matrix &b) const {
		Matrix c;
		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++){
				for(int k = 0; k < 4; k++)
					c.x[i][j] = (c.x[i][j] + 1LL * x[i][k] * b.x[k][j] % kMod) % kMod;
			}
		return c;
	}
};

void print(Matrix a) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) printf("%d ", a.x[i][j]); puts("");
	}
}
Matrix fpow(Matrix a, int n) {
	Matrix res;

	res.x[0][0] = 6;
	res.x[1][0] = 1;
	res.x[2][0] = 0;
	res.x[3][0] = 2;
	//print(res);
	while(n) {
		if(n & 1) res = a * res;
		a = a * a, n >>= 1;
	}
	return res;
}
const int C[4][4] = {{2, 4, 0, 2}, {1, 0, 0, 0}, {0, 8, 2, 0}, {0, 0, 0, 2}};
int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}
int main() {
	scanf("%d", &n);
	if(n == 1) return puts("2"), 0;

	Matrix A;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) A.x[i][j] = C[i][j];

	A = fpow(A, n - 2);
	//print(A);
	int ans = (4LL * A.x[0][0] + 2LL * A.x[2][0]) % kMod;
	printf("%d\n", ans);
	return 0;
} 
