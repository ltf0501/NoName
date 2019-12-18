#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i < n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
		}
		if(n & 1) puts("Alice");
		else puts("Bob");
	}
	return 0;
}
