#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
const int kMod = 1e9 + 7;

char c[kN];
int add(int x, int y) {
	x += y;
	if(x >= kMod) x -= kMod;
	return x;
}
int sub(int x, int y) {
	x -= y;
	if(x < 0) x += kMod;
	return x;
}

int main() {
	scanf("%s", c);
	int n = strlen(c);

	int ans = 0, num = 0;
	for(int i = 0; i < n; i++) {
		int new_num = add(10LL * num % kMod, c[i] - '0');
		int diff = sub(new_num, num);

		int tmp = abs(9 * (n - i - 1) - 1);
		ans = add(ans, 1LL * diff * tmp % kMod);
		num = new_num;
	}
	ans = sub(ans, 1);
	printf("%d\n", ans);
	return 0;
} 
