#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n;
int zero;
char c[maxn];
int bit1[maxn], bit2[maxn];
int f[maxn];
int now1, now2;
void add(int *v, int x, int d) {
	for(int i = x; i < maxn; i += i & -i)
		v[i] += d;
}
int query(int *v, int x) {
	int res = 0;
	for(int i = x; i; i -= i & -i)
		res += v[i];
	return res;
}
int main() {
	scanf("%d", &n);
	scanf("%s", c);
	for(int i = n - 1; i >= 0; i--) {
		bool flag = (now1 <= 0 && now2 <= 0);
		if(c[i] == '1') now1++;
		else now1--;
		if(c[i] == '2') now2++;
		else now2--;
		
		if(now1 > 0) {
			f[0]++;
			f[now1]--;
		} 
		else if(now2 > 0) {
			f[0] += 2;
			f[now2] -= 2;
		}
		else if((n - i) & 1) {
			if(flag && c[i] == '0') {
				add(bit1, now1 + n, 1);
				add(bit2, now2 + n, 1);
				zero++;
			}
			else {
				int res = query(bit1, now1 + n - 1) + query(bit2, now2 + n - 1);
				if(res == zero) {
					f[0]++, f[1]--;
				}
			}
		}
	}
	int tp = 0;
	for(int i = maxn - 1; i; i--)
		if(f[i]) {tp = i; break;}
 
	for(int i = 1; i <= tp; i++) 
		f[i] += f[i - 1];
 
	for(int i = 0, tmp = 0; i <= tp; i++) {
		f[i] += tmp;
		tmp = f[i] / 10;
		f[i] %= 10;
		if(tmp && i == tp) tp++;
	}
	tp = 0;
	for(int i = maxn - 1; i; i--) 
		if(f[i] != 0) {tp = i; break;}
	for(int i = tp; i >= 0; i--) printf("%d", f[i]);
	puts("");
	return 0;
}
