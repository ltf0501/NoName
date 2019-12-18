#include <bits/stdc++.h>
using namespace std;
const int kN = 5e3 + 10;
int a[kN];
int b[kN];
int n, m;
bool check1(int res) {
	int now0 = 0, now1 = 0;
	for(int i = 1; i <= m; i++) {
		if(b[i] == res) {
			if(!now1) now0++;
			else now1--;
		}
		else {
			if(++now1 >= 3) now1 -= 2;
		}
	}
	return now0 - now1 > 0;
}
bool check2() {
	if(m & 1) return 0;
	int tot0 = 0, tot1 = 0;
	for(int i = 1; i <= m; i++) {
		if(b[i] == 0) tot0++;
		else tot1++;
	}
 
	int res = (tot0 > tot1);
	int diff = abs(tot0 - tot1);
	int now0 = 0, now1 = 0;
	for(int i = 1; i <= m && diff > 0; i++) {
		if(b[i] == res) {
			if(!now1) now0++;
			else now1--;
		}
		else {
			if(++now1 >= 3) now1 -= 2, diff -= 2;
		} 
	}
	return diff == 0;
}
bool check(int x) {
	m = 0;
	for(int i = 1; i < x; i++) b[++m] = (a[i] > a[x]);
	int l1 = check1(1), l0 = check1(0), l2 = check2();
	m = 0;
	for(int i = x + 1; i <= n; i++) b[++m] = (a[i] > a[x]);
	int r1 = check1(1), r0 = check1(0), r2 = check2();
	//printf("x = %d: l0 = %d, l1 = %d, l2 = %d, r0 = %d, r1 = %d, r2 = %d\n", x, l0, l1, l2, r0, r1, r2); 
	return (l1 && r0) || (l0 && r1) || (l2 && r2);
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) {
			//check(i);
			putchar(check(i) ? '1' : '0');	
		}
		puts("");
	}
	return 0;
}
