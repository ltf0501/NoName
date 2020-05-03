#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define PB push_back
constexpr int kN = int(1E4 + 10);

int a[kN], n, d[kN];

bool work(int x) {
	cout << x << endl;
	string s;
	cin >> s;

	if (s[0] == 'E') return true;
	else if (s[0] == '<') {
		for (int i = 1; i <= n; i++) if (a[i] <= x) d[i] >>= 1;
	}
	else {
		for (int i = 1; i <= n; i++) if (a[i] >= x) d[i] >>= 1;
	}
	
	for (int i = 1; i <= n; i++) cin >> a[i];
	return false;
}

int main() {
	vector<int> v;
	int k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) d[i] = 1 << (k - 1);

	while (true) {
		v.clear();
		for (int i = 1; i <= n; i++) for (int j = 1; j <= d[i]; j++) v.PB(a[i]);
		sort(v.begin(), v.end());	
		if (work(v[int(v.size()) >> 1])) return 0;
	} 
} 
