#include <stdio.h>

int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}

int main() {
	int p, q, r, xa, xb, ya, yb, g;
	scanf("%d%d%d", &p, &q, &r);
	xa = 3 * p - 2 * q + r;
	xb = 2 * (p + r);
	ya = (p + 2 * q - r);
	yb = 2 * (p + r);
	if (xa <= 0 || ya <= 0) {
		printf("-1\n");
		return 0;
	}
	g = gcd(xa, xb);
	xa /= g;
	xb /= g;
	g = gcd(ya, yb);
	ya /= g;
	yb /= g;
	if (xa >= xb || ya >= yb) {
		printf("-1\n");
		return 0;
	}
	printf("%d/%d %d/%d\n", xa, xb, ya, yb);
}
