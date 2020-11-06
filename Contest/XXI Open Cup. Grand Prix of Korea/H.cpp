#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;
const long long kInf = 1e18;

int main() {
	int n;
	scanf("%d", &n);
	vector<int> c(n);
	long long tot = 0;
	for(int i = 0; i < n; i++) scanf("%d", &c[i]), tot += c[i];
	if(tot == 1) {
		int id = -1;
		for(int i = 0; i < n; i++) {
			if(c[i]) {id = i; break;}
		}
		printf("%d\n", id <= 1 ? 1 : id);
		return 0;
	}

	auto Check = [&](int x) {
		vector<long long> tmp(kN);
		for(int i = 0; i < n; i++) tmp[i] = c[i];
		for(int i = x + 1; i < n; i++) tmp[0] += tmp[i], tmp[i] = 0;
		if(tmp[x]) tmp[0] += tmp[x] - 1, tmp[x] = 1;

		long long need = 1;
		for(int i = x; i; i--) {
			if(tmp[i] < need) need += need - tmp[i];
			else if(tmp[i] > need) tmp[0] += tmp[i] - need;
			if(need >= kInf) break;
		}
		//printf("x = %d: tmp[0] = %lld, need = %lld\n", x, tmp[0], need);
		if(tmp[0] >= need) return 1;
		else return 0;
	};

	int l = 1, r = n + 1000;
	while(r - l > 1) {
		int mid = (l + r) >> 1;
		if(Check(mid)) l = mid;
		else r = mid;
	}
	printf("%d\n", r);
	return 0;
} 
