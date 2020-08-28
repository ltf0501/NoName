#include <stdio.h>

int main() {
	int n, s1, tmp;
	bool ans = true;
	scanf("%d%d", &n, &s1);
	for (int i = 2; i <= n; i++) {
		scanf("%d", &tmp);
		if (tmp > s1) ans = false;
	}
	if (ans) printf("S\n");
	else printf("N\n");

} 
