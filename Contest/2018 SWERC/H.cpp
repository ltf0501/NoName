#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

#define F first
#define S second
#define PB push_back

constexpr int kN = int(1E5 + 10), kInf = int(1E9 + 10);

template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct BIT {
	Tree<int> val[kN];
	void init() {memset(val, 0, sizeof(val));}
	void add(int p, int x) {
		p++;
		//printf("add(%d, %d)\n", p, x);
		for (; p < kN; p += p & -p) {
			val[p].insert(x);
		}
	}
	int ask(int p, int x) {
		p++;
		//printf("ask(%d, %d)\n", p, x);
		for (; p; p -= p & -p) {
			if (val[p].order_of_key(x + 1) != 0) return true;
		}
		return false;
	}
};

vector<pair<int, int>> graph[kN];
BIT bit;
int dp[kN];
bool can[kN];
tuple<int, int, int> tp[kN];

int main() {
	int n, m, l, r, c, ans = 0;
	pair<int, int> nxt;
	std::priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &l, &r, &c);
		graph[l].PB({r, c});
		graph[r].PB({l, c});
	}
	for (int i = 0; i < n; i++) can[i] = true;
	
		for (int i = 0; i < n; i++) dp[i] = kInf;
		dp[0] = 0;
		pq.push({0, 0});
		while (!pq.empty()) {
			nxt = pq.top();
			pq.pop();
			if (dp[nxt.S] < nxt.F) continue;
			for (pair<int, int> i : graph[nxt.S]) if (nxt.F + i.S < dp[i.F]) {
				dp[i.F] = nxt.F + i.S;
				pq.push({dp[i.F], i.F});
			}
		}
		for (int i = 0; i < n; i++) get<0>(tp[i]) = dp[i];
		for (int i = 0; i < n; i++) dp[i] = kInf;
		dp[1] = 0;
		pq.push({0, 1});
		while (!pq.empty()) {
			nxt = pq.top();
			pq.pop();
			if (dp[nxt.S] < nxt.F) continue;
			for (pair<int, int> i : graph[nxt.S]) if (nxt.F + i.S < dp[i.F]) {
				dp[i.F] = nxt.F + i.S;
				pq.push({dp[i.F], i.F});
			}
		}
		for (int i = 0; i < n; i++) get<1>(tp[i]) = dp[i];
		for (int i = 0; i < n; i++) dp[i] = kInf;
		dp[2] = 0;
		pq.push({0, 2});
		while (!pq.empty()) {
			nxt = pq.top();
			pq.pop();
			if (dp[nxt.S] < nxt.F) continue;
			for (pair<int, int> i : graph[nxt.S]) if (nxt.F + i.S < dp[i.F]) {
				dp[i.F] = nxt.F + i.S;
				pq.push({dp[i.F], i.F});
			}
		}
		for (int i = 0; i < n; i++) get<2>(tp[i]) = dp[i];

	//for (int i = 0; i < n; i++) printf("tp[%d] = (%d, %d, %d)\n", i, get<0>(tp[i]), get<1>(tp[i]), get<2>(tp[i]));

	sort(tp, tp + n);
	vector<int> vals;
	for (int i = 0; i < n; i++) vals.push_back(get<1>(tp[i]));
	sort(vals.begin(), vals.end());
	vals.erase(unique(vals.begin(), vals.end()), vals.end());
	for (int i = 0; i < n; i++) get<1>(tp[i]) = int(lower_bound(vals.begin(), vals.end(), get<1>(tp[i])) - vals.begin());

	for (int i = 0; i < n; i++) {
		if (i && tp[i] == tp[i - 1]) {
			can[i] = can[i - 1];
		} else {
			can[i] = !bit.ask(get<1>(tp[i]), get<2>(tp[i]));
			bit.add(get<1>(tp[i]), get<2>(tp[i]));
		}
	}
	for (int i = 0; i < n; i++) {
		if (can[i]) {
			ans++;
			//cerr << get<0>(tp[i]) << '/' << get<1>(tp[i]) << '/' << get<2>(tp[i]) << '\n';
		}
	}
	printf("%d\n", ans);
} 
