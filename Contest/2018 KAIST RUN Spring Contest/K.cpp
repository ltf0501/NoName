#include <bits/stdc++.h>
using namespace std;
const int kN = 5e3 + 10;

int n;
int a[kN];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	int ans = 2;
	for(int i = 0; i < n; i++) {
		for(int j = i + 2; j < n; j++) {
			if(!(a[j - 2] <= a[j - 1] && a[j - 1] <= a[j]) && !(a[j - 2] >= a[j - 1] && a[j - 1] >= a[j]))
				ans = max(ans, j - i + 1);
			else break;
		}
	}
	printf("%d\n", ans);
} 
