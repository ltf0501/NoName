#include <bits/stdc++.h>
using namespace std;

int a, b;
char c[10];

void Output(int x) {
	x = (x + 43200) % 43200;
	int h = x / 3600 + 1;
	x %= 3600;
	int m = x / 60, s = x % 60;
	printf("%d:%02d:%02d\n", h, m, s);
}
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		scanf("%d %s %d", &a, c, &b);
		int now = (12 - b) * 30;	
		printf("Case %d: ", ++cas);
		if(c[0] == 'a') { //after
			int need = a - now;
			if(need <= 0) need += 360;
			int ans = int(round((double)need / (11.0 / 120.0)));
			Output((b - 1) * 3600 + ans);
		}
		else { //before
			int need = now - a;
			if(need <= 0) need += 360;
			int ans = int(round((double)need / (11.0 / 120.0)));
			Output((b - 1) * 3600 - ans);
		}
	}
	return 0;
} 
