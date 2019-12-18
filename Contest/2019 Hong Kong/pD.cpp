#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
 
#define PB push_back
 
void solve() {
	int n, k;
	vector<int> v;
	scanf("%d%d", &k, &n);
	while (n) {
		n--;
		v.PB(n % k + (10 - k));
		n /= k;
	}
	reverse(v.begin(), v.end());
	for (int i : v) printf("%d", i);
	printf("\n");
	return ;
}
 
int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
}
