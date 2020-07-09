#include <bits/stdc++.h>
using namespace std;

bool resup[200010], rm[200010];

int main() {
	int n, m; cin >> n >> m;
	priority_queue<pair<int, int>> pq;
	int64_t sum = 0;
	for (int i = 0; i < n + m; i++) {
		int x; cin >> x;
		if (x > 0) resup[i] = true;
		sum += x;
		pq.emplace(-x, i);
		while (sum < 0) {
			auto p = pq.top();
			pq.pop();
			sum += p.first;
			rm[p.second] = true;
		}
	}
	for (int i = 0; i < n + m; i++) {
		if (resup[i]) cout << "resupplied\n";
		else if (rm[i]) cout << "declined\n";
		else cout << "approved\n";
	}
} 
