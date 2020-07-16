#include <bits/stdc++.h>
using namespace std;
const int kN = 1e4 + 10;
int n;
char s[kN];
bool dp[kN][kN];
char a[kN];
int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	int len = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(s[i] == '-') {
			for(int j = 1; j <= len; j++) ans -= dp[j][len], dp[j][len] = 0;
			len--;
		}
		else {
			a[++len] = s[i];
			dp[len][len] = 1;
			if(len != 1) dp[len - 1][len] = (a[len - 1] == a[len]);
			for(int j = 1; j <= len - 2; j++) dp[j][len] = (dp[j + 1][len - 1] && (a[j] == a[len]));
			for(int j = 1; j <= len; j++) ans += dp[j][len];
		}
		printf("%d ", ans);
	}
	puts("");
} 
