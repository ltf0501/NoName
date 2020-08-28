#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>
#include <set>
#include <vector>
using namespace std;
#define PB push_back

constexpr int kN = int(1E3 + 10);
map<string, int> ma;
int now = 0;

int input() {
	string s;
	cin >> s;
	if (ma.find(s) != ma.end()) return ma[s];
	else return ma[s] = now++;
}

tuple<int, int, int> tp[kN];
set<tuple<int, int, int>> st;

bool same(tuple<int, int, int> a, tuple<int, int, int> b) {
	vector<int> v;
	v.PB(get<0>(a));
	v.PB(get<1>(a));
	v.PB(get<2>(a));
	v.PB(get<0>(b));
	v.PB(get<1>(b));
	v.PB(get<2>(b));
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	if (v.size() < 6) return true;
	return false;
}

bool have(int a, int b, int c) {
	if (st.find({a, b, c}) != st.end()) return true;
	if (st.find({b, c, a}) != st.end()) return true;
	if (st.find({c, a, b}) != st.end()) return true;
	return false;
}

bool can(int a, int b, int c, int d, int e, int f) {
	return have(a, b, c) &&
				 have(a, d, b) &&
				 have(a, e, d) &&
				 have(a, c, e) &&
				 have(f, d, e) &&
				 have(f, e, c) &&
				 have(f, c, b) &&
				 have(f, b, d);
}

int main() {
	freopen("laboratory.in", "r", stdin);
	freopen("laboratory.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, a, b, c;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		a = input();
		b = input();
		c = input();
		tp[i] = {a, b, c};
	}
	for (int i = 1; i <= n; i++) st.insert(tp[i]);
	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) if (!same(tp[i], tp[j])) {
		for (int k = 1; k <= 3; k++) {
			tp[j] = {get<1>(tp[j]), get<2>(tp[j]), get<0>(tp[j])};
			if (can(get<0>(tp[i]), get<1>(tp[i]), get<2>(tp[i]), get<0>(tp[j]), get<1>(tp[j]), get<2>(tp[j]))) {
				cout << "YES" << '\n';
				return 0;
			}
		}
	}
	cout << "NO" << '\n';
} 
