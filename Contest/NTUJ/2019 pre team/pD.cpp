#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
typedef long long ll;
mt19937 rng;
struct P {
	int p, e, id;
	bool operator < (const P& rhs) const {
		return e > rhs.e;
	}
};
struct treap {
	treap *lc, *rc, *fa;
	int pri, sz, p, e;
	ll sum, mx, tg;
	treap(int _p, int _e) {
		lc = rc = fa = nullptr;
		pri = rng();
		p = _p, e = _e;
		sum = _p;
		mx = _p + _e;
		sz = 1;
		tg = 0;
	}
	void pull() {
		sz = 1;
		sum = p, mx = p + e;
		fa = nullptr;
		if(lc) {
			sz += lc->sz;
			sum += lc->sum;
			mx = max(lc->mx, sum + e);
			lc->fa = this;
		}
		if(rc) {
			sz += rc->sz;
			mx = max(mx, sum + rc->mx);
			sum += rc->sum;
			rc->fa = this;
		}
	}
};
treap *merge(treap *a, treap *b) {
	if(!a || !b) return a ? a : b;
	if(a->pri > b->pri) {
		a->rc = merge(a->rc, b);
		a->pull();
		return a;
	}
	else {
		b->lc = merge(a, b->lc);
		b->pull();
		return b;
	}
}
void split_sz(treap *t, int k, treap *&a, treap *&b) {
    if (!t) return a = b = nullptr, void();
    int lsz = 1 + (t->lc ? t->lc->sz : 0);
    if (lsz <= k) a = t, split_sz(t->rc, k - lsz, a->rc, b), a->pull();
    else b = t, split_sz(t->lc, k, a, b->lc), b->pull();
}

void split_val(treap *t, int k, treap *&a, treap *&b) {
    if (!t) return a = b = nullptr, void();
    if (t->e >= k) a = t, split_val(t->rc, k, a->rc, b), a->pull();
    else b = t, split_val(t->lc, k, a, b->lc), b->pull();
}
/*
void split_sz(treap *o, int k, treap *&a, treap *&b) {
	if(!o) {
		a = b = nullptr;
		return;
	}
	int lsz = 1 + (o->lc ? o->lc->sz : 0);
	if(lsz <= k) {
		a = o, split_sz(o->rc, k - lsz, a->rc, b);
		a->pull();
	}
	else {
		b = o, split_sz(o->lc, k, a, b->lc);
		b->pull();
	}
}
void split_val(treap *o, int k, treap *&a, treap *&b) {
	if(!o) {
		a = b = nullptr;
		return;
	}
	if(o->e >= k) {
		a = o, split_val(o->rc, k, a->rc, b);
		a->pull();
	}
	else {
		b = o, split_val(o->lc, k, a, b->lc);
		b->pull();
	}
}
*/
int rk(treap *o) { // number of node left to o
	assert(o);
	int res = o->lc ? o->lc->sz : 0;
	while(o->fa) {
		if(o->fa->rc == o) res += 1 + (o->fa->lc ? o->fa->lc->sz : 0);
		o = o->fa;
	}
	return res;
}
void print(treap *o) {
	if(!o) return;
	if(o->lc) print(o->lc);
	printf("p = %d, e = %d\n", o->p, o->e);
	if(o->rc) print(o->rc);
}
int p[maxn], e[maxn];
treap *tr[maxn];
P a[maxn];
int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &e[i]);
	for(int i = 1; i <= n; i++) a[i] = {p[i], e[i], i};
	sort(a + 1, a + n + 1);
	treap *root = nullptr;
	for(int i = 1; i <= n; i++) tr[a[i].id] = new treap(a[i].p, a[i].e);
	for(int i = 1; i <= n; i++) root = merge(root, tr[a[i].id]);
	print(root);
	printf("%lld\n", root->mx);
	while(q--) {
		int type, x, y;
		scanf("%d%d%d", &type, &x, &y);
		int pos = rk(tr[x]);
		if(type == 1) {
			if(p[x] == y) continue;
			treap *lt, *rt;
//			print(root);
			split_sz(root, pos, lt, rt);
			if(lt) lt->fa = nullptr;
			if(rt) rt->fa = nullptr;
			treap *x1, *x2;
//			printf("rt->sz = %d\n", rt->sz);
			split_sz(rt, 1, x1, x2);
			if(x1) x1->fa = nullptr;
			if(x2) x2->fa = nullptr;
			p[x] = y;
			*tr[x] = treap(p[x], e[x]);
			root = merge(lt, merge(tr[x], x2));
		}
		else {
			if(e[x] == y) continue;
			treap *lt, *rt;
			split_sz(root, pos, lt, rt);
			if(lt) lt->fa = nullptr;
			if(rt) rt->fa = nullptr;
			treap *x1, *x2;
			split_sz(rt, 1, x1, x2);
			if(x1) x1->fa = nullptr;
			if(x2) x2->fa = nullptr;
			root = merge(lt, x2);
			treap *aa, *bb;
			split_val(root, y, aa, bb);
			if(aa) aa->fa = nullptr;
			if(bb) bb->fa = nullptr;
			e[x] = y;
			*tr[x] = treap(p[x], e[x]);
			root = merge(aa, merge(tr[x], bb));
		}
		print(root);
		printf("%lld\n", root->mx);
	}
	return 0;
}
