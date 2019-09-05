#include <bits/stdc++.h>
using namespace std;

string str[16];
vector<string> sub_strs[16];
int dp[16][1 << 16];

int main() {
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    int n; cin >> n;
    sub_strs[0].emplace_back("");
    for (int i = 1; i <= n; i++) {
        cin >> str[i];
        for (int j = 1; j < (1 << str[i].size()); j++) {
            string sub_str;
            for (int k = 0; k < int(str[i].size()); k++) {
                if (j & (1 << k)) sub_str.push_back(str[i][k]);
            }
            sub_strs[i].push_back(sub_str);
        }
        sort(sub_strs[i].begin(), sub_strs[i].end());
    }
    for (int i = 1; i <= n; i++) {
        int k = 0, pref_max = INT_MIN;
        for (int j = 0; j < int(sub_strs[i].size()); j++) {
            while (k < int(sub_strs[i - 1].size()) && sub_strs[i - 1][k] < sub_strs[i][j]) {
                pref_max = max(pref_max, dp[i - 1][k]);
                k++;
            }
            dp[i][j] = pref_max + int(sub_strs[i][j].size());
        }
    }
    int ans = *max_element(dp[n], dp[n] + sub_strs[n].size());
    cout << (ans >= 0 ? ans : -1) << '\n';
}
