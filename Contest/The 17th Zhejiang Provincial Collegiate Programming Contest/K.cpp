#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int m; scanf("%d", &m);
		vector<int> a(m + 1), b(m + 1);
		for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++) scanf("%d", &b[i]);

		int ans = -1;
		for(int i = 1; i <= m; i++) {
			if(b[i] > 3 * a[i]) {ans = i; break;}
		}
		printf("%d\n", ans);
	}

	return 0;
} 
