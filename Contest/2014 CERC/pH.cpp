#include <stdio.h>
#include <set>
using namespace std;
 
 
set<int> s;
 
int x[10] = {2, 1, 2, 3, 1, 2, 3, 1, 2, 3}, y[10] = {4, 1, 1, 1, 2, 2, 2, 3, 3, 3};
bool ok(int n) {
	int lx, ly, nx, ny;
	lx = x[n % 10];
	ly = y[n % 10];
	n /= 10;
	while (n) {
		nx = x[n % 10];
		ny = y[n % 10];
		if (nx > lx || ny > ly) return false;
		n /= 10;
		lx = nx;
		ly = ny;
	}
	return true;
}
 
void pre() {
	for (int i = 1; i <= 200; i++) if (ok(i)) s.insert(i);
	return ;
}
 
void solve() {
	int n;
	scanf("%d", &n);
	if (*s.upper_bound(n) - n > n - *(--s.upper_bound(n))) printf("%d\n", *(--s.upper_bound(n)));
	else printf("%d\n", *s.upper_bound(n));
}
 
int main() {
	pre();
	int t;
	scanf("%d", &t);
	while (t--) solve();
}
