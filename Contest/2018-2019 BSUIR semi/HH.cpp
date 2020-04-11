#include <stdio.h>
typedef long long int ll;
constexpr ll LIM = ll(1E18 + 10);
bool havedigit(ll x) {
	ll tmp;
	while (x) {
		tmp = x % 10;
		if (tmp == 1 || tmp == 2 || tmp == 3 || tmp == 5 || tmp == 8) return true;
		x /= 10;
	}
	return false;
}
int main() {
	ll a = 1, b = 1, tmp;
	while (a < LIM) {
		printf("%d\n", havedigit(a) ? 1 : 0);
		tmp = a;
		a += b;
		b = tmp;
	}
}
