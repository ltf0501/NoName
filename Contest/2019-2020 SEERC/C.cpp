bool debug = false;
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define PB push_back
constexpr int kN = int(3E2 + 10);

int ABS(int n) {return n >= 0 ? n : -n;}

int answ[kN];

vector<int> query(vector<int> v) {
	vector<int> ans;
	if (v.size() <= 1) return ans;
	int tot = int(v.size());
	if (debug) {
		for (int i = 0; i < tot; i++) for (int j = i + 1; j < tot; j++) 
			ans.PB(ABS(answ[v[i]] - answ[v[j]]));
		sort(ans.begin(), ans.end());
		return ans;
	}
	printf("2 %d", int(v.size()));
	for (int i : v) printf(" %d", i);
	printf("\n");
	fflush(stdout);
	tot = tot * (tot - 1);
	tot >>= 1;
	ans.resize(tot);
	for (int i = 0; i < tot; i++) scanf("%d", &ans[i]);
	sort(ans.begin(), ans.end());
	return ans;
}

int ask(int pos) {
	if (debug) {
		return answ[pos];
	}
	int ans;
	printf("1 %d\n", pos);
	fflush(stdout);
	scanf("%d", &ans);
	return ans;
}

vector<int> vand(vector<int> &a, vector<int> &b) {
	int lpos = 0, rpos = 0, lsz = int(a.size()), rsz = int(b.size());
	vector<int> ans;
	while (lpos < lsz && rpos < rsz) {
		if (a[lpos] == b[rpos]) {
			ans.PB(a[lpos]);
			lpos++;
			rpos++;
		}
		else if (a[lpos] < b[rpos]) lpos++;
		else rpos++;
	}
	return ans;
}


int a[kN];

void answer(int n) {
	if (debug) {
		for (int i = 1; i <= n; i++) if (answ[i] != a[i]) {
			printf("Wrong at pos %d\n", i);
			for (int j = 1; j <= n; j++) printf("%d ", answ[j]);
			printf("\n");
			for (int j = 1; j <= n; j++) printf("%d ", a[j]);
			printf("\n");
			return ;
		}
		printf("Done\n");
		return ;
	}
	printf("3");
	for (int i = 1; i <= n; i++) printf(" %d", a[i]);
	printf("\n");
	fflush(stdout);
	return ;
}

int db() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) answ[i] = rand();
	random_shuffle(answ + 1, answ + n + 1);
	return n;
}

int main() {
	int n, l = 1, r, mid, mx, pos;
	vector<int> tmp, v, have[kN], all, ttmp, allvalue;
	if (debug) n = db();
	else scanf("%d", &n);
	if (n == 1) {
		a[1] = ask(1);
		answer(n);
		return 0;
	}
	r = n;
	v.resize(n);
	for (int i = 1; i <= n; i++) v[i - 1] = i;
	all = query(v);
	mx = all.back();
	while (r - l > 1) {
		mid = (l + r) >> 1;
		v.clear();
		v.resize(mid);
		for (int i = 1; i <= mid; i++) v[i - 1] = i;
		tmp = query(v);
		if (mx == tmp.back()) r = mid;
		else l = mid;
	}
	pos = r;
	a[pos] = ask(pos);

	v.clear();
	for (int i = 1; i <= n; i++) if (i != pos) v.PB(i);
	tmp = query(v);
	l = 0;
	for (int j : all) if (l < tmp.size() && j == tmp[l]) l++;
	else allvalue.PB(j);
	
	for (int i = 1; i <= n; i <<= 1) {
		v.clear();
		for (int j = 1; j <= n; j++) if (j != pos && j & i) v.PB(j);
		tmp = query(v);
		v.PB(pos);
		ttmp = query(v);
		l = 0;
		for (int j : ttmp) if (l < tmp.size() && j == tmp[l]) l++;
		else have[i].PB(j);
	}
	
	for (int i : allvalue) {
	int		npos = 0;
		for (int j = 1; j <= n; j <<= 1) {
			for (int k : have[j]) if (i == k) npos ^= j;
		}
		a[npos] = i;
	}

	
	for (int i = 1; i <= n; i++) if (i != pos) {
		mx = ask(i);
		if (a[pos] < mx) {
			for (int j = 1; j <= n; j++) if (j != pos) a[j] = a[pos] + a[j];
		}
		else {
			for (int j = 1; j <= n; j++) if (j != pos) a[j] = a[pos] - a[j];
		}
		break;
	}
	answer(n);

} 
