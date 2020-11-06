#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 5e5 + 10;

int k = 500000;
int n, m;
int a[kN], a2[kN], b[kN];
ll cnt[kN];
ll prea[kN], preb[kN];

#define lc (o << 1)
#define rc (o << 1 | 1)
ll mn[kN << 2], tg[kN << 2];
void push_up(int o) {
	mn[o] = min(mn[lc], mn[rc]);
}
void push_down(int o) {
	if(!tg[o]) return;
	mn[lc] += tg[o], mn[rc] += tg[o];
	tg[lc] += tg[o], tg[rc] += tg[o];
	tg[o] = 0;
}
void Build(int l = 1, int r = k, int o = 1) {
	tg[o] = 0;
	if(l == r) {
		mn[o] = preb[l] - prea[l];
		return;
	}
	int mid = (l + r) >> 1;
	Build(l, mid, lc), Build(mid + 1, r, rc);
	push_up(o);
}

void Update(int ql, int qr, int x, int l = 1, int r = k, int o = 1) {
	if(ql <= l && r <= qr) {
		tg[o] += x, mn[o] += x;
		return;
	}
	push_down(o);
	int mid = (l + r) >> 1;
	if(ql <= mid) Update(ql, qr, x, l, mid, lc);
	if(qr > mid) Update(ql, qr, x, mid + 1, r, rc);
	push_up(o);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a2[i] = a[i];
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]), cnt[b[i]]++;
	sort(a2 + 1, a2 + n + 1, greater<int>());
	for(int i = kN - 2; i >= 0; i--) cnt[i] += cnt[i + 1];
	for(int i = 1; i <= n; i++) prea[i] = prea[i - 1] + a2[i];
	for(int i = n + 1; i <= k; i++) prea[i] = prea[i - 1];

	for(int i = 1; i <= k; i++) preb[i] = preb[i - 1] + cnt[i];
	//for(int i = 1; i <= n; i++) preb[i] = preb[i - 1] + cnt[i];
	//for(int i = n + 1; i <= k; i++) preb[i] = preb[i - 1];

	//for(int i = 1; i <= n; i++) printf("%d ", a2[i]); puts("");
	//for(int i = 1; i <= n; i++) printf("%d ", cnt[i]); puts("");
	Build();
	//printf("mn = %d\n", mn[1]);
	int q; scanf("%d", &q);
	while(q--) {
		int type, id; scanf("%d%d", &type, &id);
		if(type == 1) {
			int val = a[id];
			int pos = lower_bound(a2 + 1, a2 + n + 1, val, greater<int>()) - a2;
			a2[pos]++; 
			Update(pos, k, -1);
			a[id]++;
		}
		else if(type == 2) {
			int val = a[id];
			int pos = upper_bound(a2 + 1, a2 + n + 1, val, greater<int>()) - a2 - 1;
			a2[pos]--;
			Update(pos, k, 1); 
			a[id]--;
		}
		else if(type == 3) {
			int val = b[id];	
			b[id]++;
			cnt[val + 1]++;
			Update(val + 1, k, 1);
		}
		else {
			int val = b[id];	
			b[id]--;
			cnt[val]--;
			Update(val, k, -1);
		}
		//printf("mn = %lld\n", mn[1]);
		printf("%d\n", mn[1] >= 0 ? 1 : 0);
	}
	return 0;
} 
