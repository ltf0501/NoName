#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1000000;
int cnt[kN + 1], np[kN + 1];

int main() {
	for (int i = 2; i <= kN; i++) {
		for (int j = i + i; j <= kN; j += i) np[j] = true;
		cnt[i] = cnt[i - 1] + !np[i];
	}
	cout << cnt[kN] << '\n';
}
