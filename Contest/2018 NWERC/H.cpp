#include <stdio.h>


constexpr int kN = int(5E5 + 10);
bool ans[kN], broken[kN];
int z[kN];

int main() {
	int n, c, b; 
	scanf("%d%d%d", &n, &c, &b);
	for (int i = 1; i <= b; i++) scanf("%d", &z[i]);
	for (int i = 1; i <= b; i++) broken[z[i]] = true;
	if (c & 1) {
		ans[1] = true;
		c--;
		for (int i = 3; i <= n; i++) if (!broken[i]) {
			if (c > 0) {
				c -= 2;
				ans[i] = true;
				i++;
			}
		}
	}
	else {
		for (int i = 2; i <= n; i++) if (!broken[i]) {
			if (c > 0) {
				c -= 2;
				ans[i] = true;
				i++;
			}
		}
	}

	for (int i = 1; i <= n; i++) printf("%d", ans[i] ? 1 : 0);
	printf("\n");
} 
