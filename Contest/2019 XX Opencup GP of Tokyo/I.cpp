#include <bits/stdc++.h>
using namespace std;
const int kN = 1e3 + 10;
int p[kN][kN];
int q[3][kN];
int lg[kN];
int main() {
	int n; scanf("%d", &n);
	if(n == 1) {
		printf("1\n1\n");
		return 0;
	}
	if(n == 2) {
		puts("-1");
		return 0;
	}

	lg[1] = 0;
	for(int i = 2; i <= n + 1; i++) lg[i] = lg[i >> 1] + 1;
	int k = (lg[n] + (lg[n] == lg[n - 1])) + 1;

	for(int i = 0; i < k; i++) {
		for(int j = 0; j < n; j++) p[i][j] = (j + (1 << i)) % n;
	}
	printf("%d\n", k);
	if(n & 1) {
		for(int i = 0; i < k; i++) {
			for(int j = 0; j < n; j++) printf("%d ", p[i][j] + 1);
			puts("");
		} 
	}
	else if(n % 4 == 0) {
		for(int i = 0; i < n / 4; i++) {
			q[0][i * 4] = 2 + i * 4;
			q[0][i * 4 + 1] = 3 + i * 4;
			q[0][i * 4 + 2] = 1 + i * 4;
			q[0][i * 4 + 3] = 0 + i * 4;
		} 
		for(int j = 0; j < n; j++) printf("%d ", q[0][j] + 1); puts("");
		for(int i = 0; i < k - 1; i++) {
			for(int j = 0; j < n; j++) printf("%d ", p[i][j] + 1);
			puts("");
		}
	}
	else {
		for(int i = 0; i < n / 4; i++) {
			q[0][i * 4] = 2 + i * 4;
			q[0][i * 4 + 1] = 3 + i * 4;
			q[0][i * 4 + 2] = 1 + i * 4;
			q[0][i * 4 + 3] = 0 + i * 4;
		} 
		q[0][n - 2] = n - 2, q[0][n - 1] = n - 1;
		for(int i = 0; i < n; i++) q[1][i] = i;
		q[1][n - 4] = n - 1, q[1][n - 3] = n - 2, q[1][n - 2] = n - 4, q[1][n - 1] = n - 3;

		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < n; j++) printf("%d ", q[i][j] + 1); puts("");
		}
		for(int i = 0; i < k - 2; i++) {
			for(int j = 0; j < n; j++) printf("%d ", p[i][j] + 1); puts("");
		}
	}
	return 0;
}
