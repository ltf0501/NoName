#include <bits/stdc++.h>
using namespace std;

const char c[] = {'a', 'i', 'y', 'e', 'o', 'u'};
const char d[] = {'b', 'k', 'x', 'z', 'n', 'h', 'd', 'c','w', 'g', 'p', 'v', 'j', 'q', 't', 's', 'r', 'l', 'm', 'f'};
bool Check(char x) {
    if( x == 'a' || x == 'i' || x == 'y' || x == 'e' || x == 'o' || x == 'u') return 1;
    return 0;
}
bool isalpha(char x) {
    return ('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z');
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s;
    while (getline(cin, s)) {
        int n = s.size();
        for(int i = 0; i < n; i++) {
            if(!isalpha(s[i])) continue;
            bool flag = 0;
            if('A' <= s[i] && s[i] <= 'Z') flag = 1, s[i] = s[i] - 'A' + 'a';

            if(Check(s[i])) {
                int id = -1;
                for(int j = 0; j < 6; j++) {
                    if(c[j] == s[i]) {id = j; break;}
                }
                s[i] = c[(id + 3) % 6];
            }
            else if(s[i] != ' ') {
                int id = -1;
                for(int j = 0; j < 20; j++) {
                    if(d[j] == s[i]) {id = j; break;}
                }
                s[i] = d[(id + 10) % 20];
            }
            if(flag) s[i] = s[i] + 'A' - 'a';
        }
        cout << s << '\n';
    }
    return 0;
}
