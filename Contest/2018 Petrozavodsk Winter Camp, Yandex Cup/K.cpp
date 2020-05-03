#include <stdio.h>
#include <assert.h>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back

constexpr int kN = int(1E5 + 10);
int d[kN], num[kN], a[kN];
pair<int, int> p[kN];
vector<int> v;

bool cant(int x, int n) {
	if (x > n) return false;
	if (x == 0) return true;
	if (num[x] == x) {
		if (d[x] & 1) return true;
		else if (a[x]) {
			num[x] = 1E7;
			return false;
		}
		else return true;
	}
	return true;
}

int main() {
	int n, now, l, r, cnt;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &p[i].F, &p[i].S);
		d[p[i].F]++;
		d[p[i].S]++;
	}
	now = n;
	for (int i = 1; i <= n; i++) num[i] = i;
	for (int i = 1; i <= n; i++) if ((d[i] & 1) && a[i]) v.PB(i);
	for (int i = 1; i <= n; i++) if (d[i] & 1) now ^= i;
	if (now == 0) {
		printf("%d\n", n);
		for (int i = 1; i < n; i++) printf("%d %d\n", p[i].F, p[i].S);
			now = n;
			for (int i = 1; i < n; i++) now ^= num[p[i].F] ^ num[p[i].S];
			assert(now == 0);
		return 0;
	}
	else if (int(v.size()) == 1) {
		num[v[0]] = v[0] ^ now;
		if (cant(num[v[0]], n)) printf("-1\n");
		else {
			printf("%d\n", n);
			for (int i = 1; i < n; i++) printf("%d %d\n", num[p[i].F], num[p[i].S]);
			now = n;
			for (int i = 1; i < n; i++) now ^= num[p[i].F] ^ num[p[i].S];
			assert(now == 0);
		}
	}
	else if (!v.empty()) {
		num[v[0]] ^= now;
		if (cant(num[v[0]], n)) {
			if (num[v[1]] == num[v[0]]) {
				if (v.size() > 2) {
				num[v[2]] ^= num[v[0]];
				num[v[0]] = 2E6;
				num[v[2]] ^= num[v[0]];
				printf("%d\n", n);
				for (int i = 1; i < n; i++) printf("%d %d\n", num[p[i].F], num[p[i].S]);
			now = n;
			for (int i = 1; i < n; i++) now ^= num[p[i].F] ^ num[p[i].S];
			assert(now == 0);
				}
				else printf("-1\n");
			}
			else {
				num[v[1]] ^= num[v[0]];
				num[v[0]] = 1E6;
				num[v[1]] ^= num[v[0]];
				printf("%d\n", n);
				for (int i = 1; i < n; i++) printf("%d %d\n", num[p[i].F], num[p[i].S]);
			now = n;
			for (int i = 1; i < n; i++) now ^= num[p[i].F] ^ num[p[i].S];
			assert(now == 0);
			}
		}
		else {
			printf("%d\n", n);
			for (int i = 1; i < n; i++) printf("%d %d\n", num[p[i].F], num[p[i].S]);
			now = n;
			for (int i = 1; i < n; i++) now ^= num[p[i].F] ^ num[p[i].S];
			assert(now == 0);
		}
	}
	else printf("-1\n");
} 
