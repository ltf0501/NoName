#include <bits/stdc++.h>
using namespace std;
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n, a, b; scanf("%d%d%d", &a, &b, &n);
		int flagx = 1, flagy = 1;
		if(a < 0) a = -a, flagx = -1;
		if(b < 0) b = -b, flagy = -1;
		vector<tuple<int, int, int, int>> ans;
		bool up = 1;
		while(true) {
			//printf("a = %d, b = %d\n", a, b);
			if(a >= n && b >= n) {
				if(a > b) {
					ans.emplace_back(a, b, a - n + 1, b - n + 1);
					a -= n, b -= n - 1;
					up = 1;
				}
				else {
					ans.emplace_back(a, b, a - n + 1, b - n + 1);
					a -= n - 1, b -= n;
					up = 0;
				}
			}
			else if(a >= n) {
				ans.emplace_back(a - n + 1, b - n + 1, a, b);
				a -= n, b = 0;
				up = 1;
			}
			else if(b >= n) {
				ans.emplace_back(a, b, a - n + 1, b - n + 1);
				b -= n, a = 0;
				up = 0;
			}
			else {
				if(up) {
					ans.emplace_back(a, n - 1, a - n + 1, 0);
				}
				else {
					ans.emplace_back(0, b - n + 1, n - 1, b);
				}
				break;
			}
		}
		reverse(ans.begin(), ans.end());
		printf("%d\n", int(ans.size()));
		for(auto p : ans) {
			printf("%d %d %d %d\n", get<0>(p) * flagx, get<1>(p) * flagy, get<2>(p) * flagx, get<3>(p) * flagy);
		}
	}
	return 0;
} 
