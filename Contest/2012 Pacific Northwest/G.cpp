#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, C[60][60], pre[3][60][60];

ll dp[3][60];
void Dfs(int cur) {
    if(cur == 0) {
        dp[0][cur] = 1, dp[1][cur] = n & 1, dp[2][cur] = 0;
        return;
    }
    if(n & (1LL << cur)) {
        dp[0][cur] += pre[0][cur][cur];
        dp[1][cur] += pre[1][cur][cur];
        dp[2][cur] += pre[2][cur][cur];

        Dfs(cur - 1);
        for(int i = 0; i < 3; i++) {
            dp[i][cur] += dp[(i + 2) % 3][cur - 1];
        } 
    }
    else {
        Dfs(cur - 1);
        for(int i = 0; i < 3; i++) {
            dp[i][cur] += dp[i][cur - 1];
        }
    }
}

void preprocess() {
    C[0][0] = 1;
    for(int i = 1; i < 60; i++) {
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; j++) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }

    for(int i = 0; i < 60; i++) {
        pre[0][i][0] = 1, pre[1][i][0] = 0, pre[2][i][0] = 0;
        for(int j = 1; j <= i; j++) {
            pre[0][i][j] = pre[0][i][j - 1];
            pre[1][i][j] = pre[1][i][j - 1];
            pre[2][i][j] = pre[2][i][j - 1];
            pre[j % 3][i][j] += C[i][j];
        }
    }
}
int main() {
    preprocess();
    while(~scanf("%lld", &n) && n) {
        for(int i = 0; i < 60; i++) dp[0][i] = dp[1][i] = dp[2][i] = 0;
        int c = 0;
        while((1LL << c) <= n) c++;
        c--;
        Dfs(c);
        printf("Day %lld: Level = %lld\n", n, dp[0][c] - 1);
    }
    return 0;
}
