#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int kLim = int(1E6 + 10);
ll f[100];

void update(ll &x, ll &y, ll ax, ll ay) {
	if(ax < 0 || ay < 0) return ;
	if (ax + ay < x + y) x = ax, y = ay;
	else if (ax + ay == x + y && ax < x) x = ax, y = ay;
	return ;
}

template <typename T>
tuple<T, T, T> ExtGcd(T a, T b) {
	if(!b) return make_tuple(a, 1, 0);
	T d, x, y;
	tie(d, x, y) = ExtGcd(b, a % b);
	return make_tuple(d, y, x - (a / b) * y);
}

int main() {
	int n;
	scanf("%d", &n);
	ll nx = 0, ny = n;
	f[0] = f[1] = 1;
	for (int i = 2; i < 35; i++) f[i] = f[i - 1] + f[i - 2];
	for (int i = 1; i < 35; i++) {
		ll d, x, y;
		ll a = f[i - 1], b = f[i];
		tie(d, x, y) = ExtGcd(a, b);	
		assert(d == 1);
		x *= n, y *= n;
		//printf("a = %lld, b = %lld\n", a, b);
		//printf("i = %d, x = %lld, y = %lld\n", i, x, y);
		if(x >= 0) {
			ll t = x / b;
			x -= t * b, y += t * a;
		}
		else {
			ll t = (-x - 1) / b + 1;
			x += t * b, y -= t * a;
		}
		//printf("i = %d, x = %lld, y = %lld\n", i, x, y);
		update(nx, ny, x, y);
	}
	printf("%lld %lld\n", nx, ny);	

} 
