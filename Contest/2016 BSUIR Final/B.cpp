#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	if (n == 1) printf("1\n1\n");
	else if (n <= 3) printf("-1\n");
	else if (n == 4) {
		printf("4\n");
		printf("7 4 8 3\n15 12 16 11\n5 2 6 1\n13 10 14 9\n");
	}
	else if (n & 1) {
		printf("%d\n", n);
		for (int i = 1; i <= n; i++) {
			printf("%d", (i - 1) * n + 1);
			for (int j = 2; j <= n; j++) printf(" %d", (i - 1) * n + (j * 2 - 2) % n + 1);
			printf("\n");
		}
	}
	else {
		printf("%d\n", n);
		for (int i = 1; i <= n; i++) {
			printf("%d", (i - 1) * n + 1);
			for (int j = 3; j <= n; j += 2) printf(" %d", (i - 1) * n + j);
			for (int j = 2; j <= n; j += 2) printf(" %d", (i - 1) * n + j);
			printf("\n");
		}
	}
}


