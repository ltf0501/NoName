#pragma GCC optimize("O3", "tree-vectorize", "fast-math")
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
const int INF = 1e9;
int f[maxn];
char c[maxn];
int dp[maxn];
void failure(char *c, int *f) {
    int n = strlen(c);
    f[0] = f[1] = 0;
    for(int i = 1; i < n; i++) {
        int k = f[i];
        while(k && c[i] != c[k]) k = f[k];
        f[i + 1] = (c[i] == c[k]) ? k + 1 : 0;
    }
}
int main() {
    int T; 
    scanf("%d", &T);
    while(T--) {
        scanf("%s", c); 
        int n = strlen(c);
        for(int i = 1; i <= n + 5; i++) dp[i] = INF;
        for(int i = 0; i < n; i++) {
            failure(c + i, f);
            for(int j = i + 1; j <= n; j++) {
                int k = (j - i) - f[j - i];
                int tmp;
                if((j - i) % k == 0) tmp = k;
                else tmp = j - i;
                dp[j] = min(dp[j], dp[i] + tmp);
            }
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
