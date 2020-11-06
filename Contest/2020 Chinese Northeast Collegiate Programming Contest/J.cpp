#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n; scanf("%d", &n);
		if(n == 1) {
			puts("2");
		}
		else if(n == 2) {
			puts("16");
		}
		else if(n == 3) {
			puts("32");
		}
		else puts("4");
	}
	return 0;
} 
