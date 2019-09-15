
#include <bits/stdc++.h>
using namespace std;

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(0);
    int a, b;
    while(cin >> a >> b && a + b) {
        __float128 ans = 0.0;
        for(int i = a; i <= b; i++) ans += 1 / (3.0 * pow(i, 2.0 / 3));
        printf("%.5E\n", (double)(ans / 1e15)); 
    }
    
    return 0;
}
