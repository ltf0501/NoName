#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	multiset<int> st;
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (x >= 0) {
			st.insert(x);
		} else {
			auto it = st.find(-x);
			auto it2 = st.find(0);
			if (it != st.end()) {
				st.erase(it);
			} else if (it2 != st.end()) {
				st.erase(it2);
				ans.push_back(-x);
			} else {
				cout << "No\n";
				exit(0);
			}
		}
	}
	while (!st.empty()) {
		int x = *st.begin();
		if (!x) ans.push_back(1);
		st.erase(st.begin());
	}
	cout << "Yes\n";
	for (int x : ans) cout << x << ' ';
	cout << '\n';
} 
