#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		int n; scanf("%d", &n);
		printf("Case #%d:\n", ++cas);
		puts("YES");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= i; j++) {
				printf("%d %d %d %d %d %d %d %d\n", j, i, j, 1, i, j, 2, i);
			}
		}
	}
	return 0;
}
