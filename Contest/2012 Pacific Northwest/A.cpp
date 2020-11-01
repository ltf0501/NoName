#include <bits/stdc++.h>
using namespace std;
const int a[] = {1, 2, 3, 3, 4, 10};
const int b[] = {1, 2, 2, 2, 3, 5, 11};
int main() {
    int T; scanf("%d", &T);
    int cas = 0;
    while(T--) {
        int A = 0, B = 0;
        for(int i = 0; i < 6; i++) {
            int x; scanf("%d", &x);
            A += a[i] * x;
        }
        for(int i = 0; i < 7; i++) {
            int x; scanf("%d", &x);
            B += b[i] * x;
        }
        printf("Battle %d: ", ++cas);
        //printf("A= %d, B = %d\n", A, B);
        if(A > B) {
            puts("Good triumphs over Evil");
        }
        else if(A < B) {
            puts("Evil eradicates all trace of Good");
        }
        else {
            puts("No victor on this battle field");
        }
    }
    return 0;
}
