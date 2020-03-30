#include <bits/stdc++.h>
using namespace std;
const int kN = 505;
char a[kN][kN];
bool is[kN][kN];
int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%s", a[i]);

	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			int cnt = 0;
			for(int k = i + 1; k < j; k++)
				if(is[i][k]) cnt += a[k][j] - '0';

			if(cnt % 10 != a[i][j] - '0') is[i][j] = 1;
		}
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) printf("%d", is[i][j]);
		puts("");
	}
	return 0;
} 
