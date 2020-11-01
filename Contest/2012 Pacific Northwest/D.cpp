#include <bits/stdc++.h>
using namespace std;
const int kN = 5e4 + 10;
const double kEps = 1e-9;
const double kPi = 4 * atan(1);
int dcmp(double x) {
    if(fabs(x) < kEps) return 0;
    return x > 0 ? 1 : -1;
}
bool same(double a, double b) {
    return dcmp(a - b) == 0;
}

struct P {
    double x, y;
    P(double x = 0, double y = 0) : x(x), y(y) {}
    P operator + (P b) const {return P(x + b.x, y + b.y);}
    P operator - (P b) const {return P(x - b.x, y - b.y);}
    P operator * (double b) const {return P(x * b, y * b);}
    P operator / (double b) const {return P(x / b, y / b);}
    double operator * (P b) const {return x * b.x + y * b.y;}
    double operator ^ (P b) const {return x * b.y - y * b.x;}
};
int n, w, h;
P p[kN];

bool cmp(P a, P b) {
    return dcmp(atan2(a.y, a.x) - atan2(b.y, b.x)) == -1;   
}
int main() {
    while(~scanf("%d%d%d", &n, &w, &h) && n + w + h) {
        int num0 = 0;
        int tot = 0;
        for(int i = 0; i < n; i++) {
            int x, y; scanf("%d%d", &x, &y);
            if(x * 2 == w && y * 2 == h) num0++;
            else p[tot++] = P(x - w / 2.0, y - h / 2.0);
        }
        if(num0 >= n / 2) {
            for(int i = 0; i < n / 2; i++) {
                printf("%d %d\n", w / 2, h / 2);
            }
            continue;
        }
        //printf("tot = %d\n", tot);
        sort(p, p + tot, cmp);
        //puts("");
        //for(int i = 0; i < n; i++) printf("%f %f\n", p[i].x, p[i].y);
        //puts("");
        P O(0, 0);

        auto Num = [&](int x, int y) {
            if(x < y) return y - x;
            return y + tot - x;
        };
        for(int i = 0, j = 1, k = 1; i < tot; i++) {
            while(j != i && dcmp((p[i] - O) ^ (p[j] - O)) == 1) j = (j + 1) % tot;
            while(k != i && dcmp((p[i] - O) ^ (p[k] - O)) != -1) k = (k + 1) % tot;

            //printf("i = %d, j = %d, k = %d\n", i, j, k);
            if(Num(i, j) <= n / 2 && num0 + Num(i, k) >= n / 2) {
                for(int t = i; t != j; t = (t + 1) % tot) {
                    int x = int(p[t].x + w / 2.0);
                    int y = int(p[t].y + h / 2.0);
                    printf("%d %d\n", x, y);
                }
                int rest = n / 2 - Num(i, j);
                for(int i = 0; i < min(rest, num0); i++) {
                    printf("%d %d\n", w / 2, h / 2);
                }
                rest -= min(rest, num0);
                if(rest) {
                    int now = j;
                    while(rest--) {
                        int x = int(p[now].x + w / 2.0);
                        int y = int(p[now].y + h / 2.0);
                        printf("%d %d\n", x, y); 
                        now = (now + 1) % tot;
                    }
                }
                break;
            }
        }
    }
    return 0;
}
