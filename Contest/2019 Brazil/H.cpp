#include <stdio.h>


int main() {
	int v, n;
	scanf("%d%d", &v, &n);
	printf("%d", (n * v + 9) / 10);
	for (int i = 2; i <= 9; i++) {
		printf(" %d", (n * i * v + 9) / 10);
	}
	printf("\n");
} 
