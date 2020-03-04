#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		int n, m; scanf("%d%d", &n, &m);
		if(n > m) swap(n, m);
		printf("Case #%d: ", ++cas);
		if(n == 1 && m == 1) puts("1");
		else if(n == 1) puts("2");
		else printf("%d\n", 2 * (n + m - 2));
	}
	return 0; 
}
