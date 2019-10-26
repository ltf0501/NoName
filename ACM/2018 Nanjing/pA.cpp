#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, k;
	scanf("%d%d",&n, &k);
	if(k == 1) {
		if(n & 1) puts("Adrien");
		else puts("Austin");
	}
	else {
		if(n == 0) puts("Austin");
		else puts("Adrien");
	}
	return 0;
}
