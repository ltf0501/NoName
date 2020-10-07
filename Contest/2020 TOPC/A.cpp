#include <stdio.h>
int main() {
	int x, y;
	scanf("%d%d", &x, &y);
	for (int i = x; i >= 0; i--) printf("%d %d\n", i, y);
	for (int i = y - 1; i >= 0; i--) printf("%d %d\n", 0, i);
	for (int i = 0; i < 10; i++) {
		for (int j = 1; j < 10; j++) printf("%d %d\n", i, j);
		for (int j = 8; j >= 0; j--) printf("%d %d\n", i, j);
		if (i != 9) printf("%d %d\n", i + 1, 0);
	}
}
