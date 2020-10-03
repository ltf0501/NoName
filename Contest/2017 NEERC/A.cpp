#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define PB push_back

typedef long long int ll;
constexpr int kN = int(4E5 + 10), kInf = int(2E9 + 10);

vector<int> v;
int x[kN], y[kN], k[kN], nx[kN], ny[kN];

bool intersect(ll X, ll Y, ll XC, ll YC) {
	return (X - XC) * (X - XC) + (Y - YC) * (Y - YC) < YC * YC;
}

struct seg_tree {
	set<int> s[kN << 2];
	void insert(int n, int l, int r, int L, int R, int idx) {
		if (L <= l && r <= R) s[n].insert(idx);
		else if (L > r || l > R) ;
		else {
			int mid = (l + r) >> 1;
			insert(n << 1, l, mid, L, R, idx);
			insert(n << 1 | 1, mid + 1, r, L, R, idx);
		}
		return ;
	}

	void erase(int n, int l, int r, int L, int R, int idx) {
		if (L <= l && r <= R) s[n].erase(idx);
		else if (L > r || l > R) ;
		else {
			int mid = (l + r) >> 1;
			erase(n << 1, l, mid, L, R, idx);
			erase(n << 1 | 1, mid + 1, r, L, R, idx);
		}
		return ;
	}

	int ask(int n, int l, int r, int X, int idx) {
		for (int i : s[n]) if (intersect(x[idx], y[idx], x[i], y[i])) return i;
		if (l < r) {
			int mid = (l + r) >> 1;
			if (X <= mid) return ask(n << 1, l, mid, X, idx);
			else return ask(n << 1 | 1, mid + 1, r, X, idx);
		}
		else return -1;
	}
};


seg_tree sg;

int main() {
	int n, tx, sz;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &k[i], &x[i], &y[i]);
	for (int i = 1; i <= n; i++) 
		if (k[i] == 1) v.PB(x[i] - y[i]), v.PB(x[i] + y[i]); 
		else v.PB(x[i]);
	
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for (int i = 1; i <= n; i++) 
		if (k[i] == 1) {
			nx[i] = lower_bound(v.begin(), v.end(), x[i] - y[i]) - v.begin() + 1;
			ny[i] = lower_bound(v.begin(), v.end(), x[i] + y[i]) - v.begin() + 1;
		}
		else nx[i] = lower_bound(v.begin(), v.end(), x[i]) - v.begin() + 1;	
		
	sz = int(v.size());

	for (int i = 1; i <= n; i++) {
		if (k[i] == 1) sg.insert(1, 1, sz, nx[i], ny[i], i);
		else {
			tx = sg.ask(1, 1, sz, nx[i], i);
			printf("%d\n", tx);
			if (tx >= 0) sg.erase(1, 1, sz, nx[tx], ny[tx], tx);
		}
	}
} 
