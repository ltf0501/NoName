#include <stdio.h>
#include <string.h>
#include <vector>
#include <deque>
#include <utility>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define F first
#define S second
#define PB push_back
constexpr int kN = int(3E5 + 10), kInf = int(1E9 + 10), kMod = int(1E9 + 7);
ll Pow(ll a, ll b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % kMod;
		a = a * a % kMod;
		b >>= 1;
	}
	return ans;
}
ll Rev(ll n) {return Pow(n, kMod - 2);}
 
struct BIT {
	ll val[kN];
	void init() {memset(val, 0, sizeof(val));}
	void add(int pos, int x) {
		pos += 1;
		while (pos < kN) {
			val[pos] += x;
			pos += pos & -pos;
		}
		return ;
	}
	ll ask(int pos) {
		pos += 1;
		ll ans = 0;
		while (pos) {
			ans += val[pos];
			pos ^= pos & -pos;
		}
		return ans;
	}
};
 
struct seg_tree {
	ll aflag[kN << 2], bflag[kN << 2];
	void init() {
		for (int i = 0; i < (kN << 2); i++) aflag[i] = 1;
		memset(bflag, 0, sizeof(bflag));
		return ;
	}
 
	void push(int n) {
		if (aflag[n] != 1 || bflag[n]) {
			auto a = aflag[n], b = bflag[n];
			aflag[n << 1] = aflag[n << 1] * a % kMod;
			bflag[n << 1] = (bflag[n << 1] * a % kMod + b) % kMod;
			aflag[n << 1 | 1] = aflag[n << 1 | 1] * a % kMod;
			bflag[n << 1 | 1] = (bflag[n << 1 | 1] * a % kMod + b) % kMod;
			aflag[n] = 1;
			bflag[n] = 0;
		}
	}
 
	void modify(int n, int l, int r, int L, int R, int a, int b) {
		if (L <= l && r <= R)  {
			aflag[n] = aflag[n] * a % kMod;
			bflag[n] = (bflag[n] * a % kMod + b) % kMod;
		} else {
			push(n);
			int m = (l + r) >> 1;
			if (L <= m) modify(n << 1, l, m, L, R, a, b);
			if (m < R) modify(n << 1 | 1, m + 1, r, L, R, a, b);
		}
	}
 
	ll query(int n, int l, int r, int p) {
		if (l == r) {
			return bflag[n];
		} else {
			push(n);
			int m = (l + r) >> 1;
			if (p <= m) return query(n << 1, l, m, p);
			else return query(n << 1 | 1, m + 1, r, p);
		}
	}
};
 
ull rng() {
	static ull x = 19873242974LL, y = 1982374298LL;
	x ^= y;
	y += x;
	return x;
}
 
struct Node {
	Node *l, *r;
	ll val, aflag, bflag;
	ull wei;
	int id;
	Node() {}
	Node(ll x, int n) {id = n; aflag = 1; bflag = 0; wei = rng(); val = x; l = r = nullptr;}
	void addtag(ll a, ll b) {
		val = a * val + b;
		aflag *= a;
		bflag *= a;
		bflag += b;
		return ;
	}
	void push() {
		if (aflag != 1 || bflag != 0) {
			if (l) l->addtag(aflag, bflag);
			if (r) r->addtag(aflag, bflag);
			aflag = 1;
			bflag = 0;
		}
		return ;
	}
};
 
Node* merge(Node *a, Node* b) {
	if (!a) return b;
	if (!b) return a;
	if (a->wei > b->wei) {
		a->push();
		a->r = merge(a->r, b);
		return a;
	}
	else {
		b->push();
		b->l = merge(a, b->l);
		return b;
	}
}
 
void split(Node *s, ll pos, Node*& a, Node*& b) {
	if (!s) a = b = nullptr;
	else if (s->val > pos) {
		s->push();
		b = s;
		split(s->l, pos, a, b->l);
	}
	else {
		s->push();
		a = s;
		split(s->r, pos, a->r, b);
	}
	return ;
}
 
int Find(Node *s, int x) {
	if (!s) return -1;
	else if (s->val == x) return s->id;
	else {
		s->push();
		if (s->val < x) return Find(s->r, x);
		else return Find(s->l, x);
	}
}
 
int k[kN], cnt[kN];
bool too_big[kN];
BIT d;
seg_tree a;
 
void fix(Node* s) {
	if (!s) return ;
	too_big[s->id] = true;
	fix(s->l), fix(s->r);
	return ;
}
int main() {
	int q, now = 1, lft, rr, mid, zero = 0, type, g, x;
	ll ans;
	deque<pair<pair<ll, ll>, vector<int>>> dq;
	vector<int> emp;
	Node* root = nullptr, *l = nullptr, *r = nullptr;
	scanf("%d", &q);
	a.init();
	d.init();
	dq.push_front({{0, 0}, emp});
	dq[0].S.PB(0);
	cnt[0] = 0;
	for (int i = 1; i <= q; i++) {
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d", &k[i]);
			cnt[now] = k[i];
			if (k[i] == 0) {
				for (int j = 0; j < int(dq.size()); j++) {
					dq[j].F.F <<= 1;
					dq[j].F.S++;
				}
				dq.push_front({{1, 1}, emp});
				dq[0].S.PB(now);
				if (root) root->addtag(2, 0);
				split(root, 1, l, r);
				root = merge(merge(l, new Node(1, now)), r);
				a.modify(1, 0, q, 0, now, 2, 0);
				a.modify(1, 0, q, now, now, 1, 1);
				now++;
				d.add(0, 1);
				d.add(now, -1);
			}
			else {
				if (dq[0].F.S == 0) dq[0].S.PB(now);
				else {
					dq.push_front({{0, 0}, emp});
					dq[0].S.PB(now);
				}
				for (int j = 1; j < int(dq.size()); j++) dq[j].F.F += k[i];
				if (root) root->addtag(1, k[i]);
				a.modify(1, 0, q, 0, now - 1, 1, k[i]);
				root = merge(new Node(k[i], zero), root);
				zero = now;
				now++;
			}
			while (dq.back().F.S >= 30) dq.pop_back();
			split(root, kMod - 1, l, r);
			fix(r);
			root = l;
		}
		else if (type == 2) {
			scanf("%d%d", &g, &x);
			printf("%lld\n", (a.query(1, 0, q, g) + (x - 1) * Pow(2, d.ask(g))) % kMod);
		}
		else if (type == 3) {
			scanf("%d", &x);
			if (x == 0) ans = zero;
			else ans = Find(root, x);
			if (ans < 0) for (int j = 0; j < int(dq.size()); j++) { 
				if (dq[j].F.F <= x && (x - dq[j].F.F) % Pow(2, dq[j].F.S) == 0 && (too_big[dq[j].S[0]] || cnt[dq[j].S[0]] == 0 || a.query(1, 0, q, dq[j].S[0]) + Pow(2, dq[j].F.S) * (cnt[dq[j].S[0]] - 1) >= x)) {
					if (!too_big[dq[j].S[0]] && a.query(1, 0, q, dq[j].S[0]) <= x) ans = dq[j].S[0];
					else {
						lft = 0, rr = int(dq[j].S.size()) - 1;
						while (rr - lft > 1) {
							mid = (lft + rr) >> 1;
							if (too_big[dq[j].S[mid]]) lft = mid;
							else if (a.query(1, 0, q, dq[j].S[mid]) <= x) rr = mid;
							else lft = mid;
						}
						ans = dq[j].S[rr];
					}
					break;
				}
			}
			printf("%lld\n", ans);
		}
	}
}
