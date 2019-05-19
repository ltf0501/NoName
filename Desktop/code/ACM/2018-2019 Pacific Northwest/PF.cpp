#include <bits/stdc++.h>
using namespace std;

const int MOD = 1E9 + 9, SZ = 1 << 8;
const int DX[] = { -2, -2, -1, 1, 2, 2, 1, -1 }, DY[] = { -1, 1, 2, 2, 1, -1, -2, -2 };
int matrix[SZ * SZ], result[SZ * SZ], tmp[4][3];

void mult(int *a, int *b, int *res) {
	memset(res, 0, sizeof(int) * SZ * SZ);
	for (int i = 0; i < SZ; i++) {
		for (int j = 0; j < SZ; j++) {
			for (int k = 0; k < SZ; k++) {
				res[i * SZ + j] = (res[i * SZ + j] + int(1LL * a[i * SZ + k] * b[k * SZ + j] % MOD)) % MOD;
			}
		}
	}
}

void pow(int *x, int e, int *res) {
	for(int i=0;i<SZ;i++)for(int j=0;j<SZ;j++)res[i*SZ+j]=0;
	for(int i=0;i<SZ;i++)res[i*SZ+i]=1;
	while(e){
		int temp[SZ*SZ];
		if(e&1){
			mult(res,x,temp);
			for(int i=0;i<SZ;i++)for(int j=0;j<SZ;j++)res[i*SZ+j]=temp[i*SZ+j];
		}
		e>>=1;
		mult(x,x,temp);
		for(int i=0;i<SZ;i++)for(int j=0;j<SZ;j++)x[i*SZ+j]=temp[i*SZ+j];
	}
	return ;
}
int main() {
	int t; cin >> t;
	while (t--) {
		memset(matrix, 0, sizeof(matrix));
		int m, n; cin >> m >> n;
		if (n < 3) {
			int w = n;
			int ans = 0;
			for (int i = 0; i < (1 << (m * w)); i++) {
				int p = 0;
				for (int j = 0; j < m; j++) {
					for (int k = 0; k < w; k++) {
						tmp[j][k] = (i >> p) & 1;
						p++;
					}
				}
				bool fail = false;
				for (int j = 0; j < m; j++) {
					for (int k = 0; k < w; k++) {
						if (tmp[j][k]) {
							for (int z = 0; z < 8; z++) {
								int nj = j + DX[z], nk = k + DY[z];
								if (nj < 0 || nj >= m || nk < 0 || nk >= w) continue;
								if (tmp[nj][nk]) fail = true;
							}
						}
					}
				}
				if (!fail) ans++;
			}
			cout << ans << '\n';
		} else {
			int w = 3;
			for (int i = 0; i < (1 << (m * w)); i++) {
				int p = 0;
				for (int j = 0; j < m; j++) {
					for (int k = 0; k < w; k++) {
						tmp[j][k] = (i >> p) & 1;
						p++;
					}
				}
				bool fail = false;
				for (int j = 0; j < m; j++) {
					for (int k = 0; k < w; k++) {
						if (tmp[j][k]) {
							for (int z = 0; z < 8; z++) {
								int nj = j + DX[z], nk = k + DY[z];
								if (nj < 0 || nj >= m || nk < 0 || nk >= w) continue;
								if (tmp[nj][nk]) fail = true;
							}
						}
					}
				}
				if (!fail) {
					int p1 = 0, id1 = 0;
					for (int j = 0; j < m; j++) {
						for (int k = 0; k < 2; k++) {
							if (tmp[j][k]) id1 |= 1 << p1;
							p1++;
						}
					}
					int p2 = 0, id2 = 0;
					for (int j = 0; j < m; j++) {
						for (int k = 1; k < 3; k++) {
							if (tmp[j][k]) id2 |= 1 << p2;
							p2++;
						}
					}
					matrix[id1 * SZ + id2] = 1;
				}
			}
			pow(matrix, n - 2, result);
			int ans = 0;
			for (int i = 0; i < SZ * SZ; i++) ans = (ans + result[i]) % MOD;
			cout << ans << '\n';

		}
	}
}
