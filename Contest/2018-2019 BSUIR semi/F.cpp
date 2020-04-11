#include <stdio.h>

int main() {
	long long int n;
	scanf("%lld", &n);
	if (n == 1) {
		printf("No\n");
		return 0;
	}
	n &= n ^ 1;
	n ^= n & -n;
	
	if (n) printf("No\n");
	else printf("Yes\n");
}
