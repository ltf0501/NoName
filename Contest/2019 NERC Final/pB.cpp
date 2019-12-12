#include <iostream>
#include <vector>
#include <utility>
using namespace std;
 
#define F first
#define S second
#define PB push_back
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, last = 0, mid;
	string s;
	vector<pair<char, int>> v;
	cin >> s;
	n = int(s.size());
	for (int i = 1; i < n; i++) if (s[i] != s[i - 1]) {
		v.PB({s[i - 1], i - last});
		last = i;
	}
	v.PB({s[n - 1], n - last});
	n = int(v.size());
	if (n & 1) {
		mid = n >> 1;
		if (v[mid].S < 2) {
			printf("0\n");
			return 0;
		}
		for (int i = mid + 1, j = mid - 1; i < n; i++, j--) {
			if (v[i].F != v[j].F || v[i].S + v[j].S < 3) {
				printf("0\n");
				return 0;
			}
		}
		printf("%d\n", v[mid].S + 1);
	}
	else printf("0\n");
}
