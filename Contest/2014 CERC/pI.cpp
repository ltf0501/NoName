#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
int num[kN];
string s;
long long int pre[2][kN];
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T;
	cin >> T;
	while(T--) { 
 
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++) {
			int x;
			cin >> x >> s;
			pre[0][i] = pre[0][i - 1];
			pre[1][i] = pre[1][i - 1];
			if(s[0] == 'B') pre[0][i] += x;
			else pre[1][i] += x;
		}
		if(pre[0][n] == 0 || pre[1][n] == 0) {
			cout << pre[0][n] + pre[1][n] << '\n';
			continue;
		}
		long long int b = pre[0][n], w = pre[1][n], lb = 0, lw = 0;
		long long int cnt = 0;
		long long int pre_flag = 0;
		for(int i = 1; i <= n; i++) {
			lb += pre[0][i] - pre[0][i - 1];
			lw += pre[1][i] - pre[1][i - 1];
			if (lb * w < lw * b) {
				if (pre_flag == -1) {
					if (lb * w % b == 0) {
						lw -= lb * w / b;
						lb = 0;
						cnt++;
					}
				}
				pre_flag = 1;
			}
			else if (lb * w > lw * b) {
				if (pre_flag == 1) {
					if (lw * b % w == 0) {
						lb -= lw * b / w;
						lw = 0;
						cnt++;
					}
				}
				pre_flag = -1;
			}
			else {
				lb = lw = 0;
				cnt++;
				pre_flag = 0;
			}
		}
		cout << cnt << '\n';
	}
	return 0;
}
