#include <bits/stdc++.h>
using namespace std;
const int kN = 105;

int n, m;
char a[kN], b[kN];
int k[kN];
int main() {
	scanf("%d%d", &n, &m);
	scanf("%s", a + (m - n));
	scanf("%s", b);
	for(int i = m - 1; i >= m - n; i--) k[i] = (b[i] - a[i] + 26) % 26;
	for(int i = m - n - 1; i >= 0; i--) {
		a[i] = k[i + n] + 'a';
		k[i] = (b[i] - a[i] + 26) % 26;
	}
	printf("%s\n", a);
	return 0;
} 
