#include <bits/stdc++.h>
using namespace std;
int n, s, p, t;
double solve(int now, int step) {
	if(now == 0) return 0;
	if(now == n) return 1;
	if(step == 0) {
		return now == n ? 1.0 : 0.0;
	}
	return (double)p / 100.0 * solve(now + min(now, n - now), step - 1) + double(100 - p) / 100.0 * solve(now - min(now, n - now), step - 1);
}
int main(){
	freopen("betting.in","r",stdin);
	freopen("betting.out","w",stdout);
	while(true){
		scanf("%d%d%d%d", &n, &s, &p, &t);
		if(n==0&&s==0&&p==0&&t==0)break;
		printf("%.12lf\n", solve(s, t));
	}
}
