#include <stdio.h>
#include <random>
using namespace std;

typedef long long int ll;
constexpr int kN = int(3E4 + 10);
constexpr ll kInf = ll(1E16 + 10);

mt19937 rng;

struct Node {
	Node *l, *r;
	ll val, wei;
	int sz;
	Node() {}
	Node(ll x) {l = r = nullptr; val = x; wei = rng(); sz = 1;}
	void pull() {
		sz = 1;
		if (l) sz += l -> sz;
		if (r) sz += r -> sz;
		return ;
	}
};

int size(Node* s) {return s ? s -> sz : 0;}

Node* Merge(Node *a, Node *b) {
	if (!a) return b;
	if (!b) return a;
	if (a -> wei > b -> wei) {
		a -> r = Merge(a -> r, b);
		a -> pull();
		return a;
	}
	else {
		b -> l = Merge(a, b -> l);
		b -> pull();
		return b;
	}
}

void Split(Node *s, ll x, Node *&a, Node *&b) {
	if (!s) a = b = nullptr;
	else if (s -> val <= x) {
		a = s;
		Split(s -> r, x, a -> r, b);
		a -> pull();
	}
	else {
		b = s;
		Split(s -> l, x, a, b -> l);
		b -> pull();
	}
	return ;
}

void Split_by_size(Node *s, int sz, Node *&a, Node *&b) {
	if (!s) a = b = nullptr;
	else if (size(s -> l) + 1 <= sz) {
		a = s;
		Split_by_size(s -> r, sz - size(s -> l) - 1, a -> r, b);
		a -> pull();
	}
	else {
		b = s;
		Split_by_size(s -> l, sz, a, b -> l);
		b -> pull();
	}
	return ;
}

void Insert(Node*& s, ll x) {
	Node *a, *b;
	Split(s, x, a, b);
	s = Merge(a, Merge(new Node(x), b));
	return ;
}

void Erase(Node*& s, ll x) {
	Node *a, *b, *c, *d;
	Split(s, x, a, b);
	Split_by_size(a, size(a) - 1, c, d);
	s = Merge(c, b);
	return ;
}

int Cnt(Node* s, ll x) {
	if (!s) return 0;
	else if (s -> val <= x) return size(s -> l) + 1 + Cnt(s -> r, x);
	else return Cnt(s -> l, x);
}

ll a[kN], b[kN], c[kN], sa[kN], sb[kN], sc[kN];

int n, len;

inline ll A(int l, int r) {return sa[r] - sa[l - 1];}
inline ll B(int l, int r) {return sb[r] - sb[l - 1];}
inline ll C(int l, int r) {return sc[r] - sc[l - 1];}

inline ll getval(int x, int y) {
	// AAABBBCCCBBBAAA
	// AAABBBAAABBBAAA
	if (x + len - 1 >= y) return A(1, x - 1) + B(x, y - 1) + C(y, x + len - 1) + B(x + len, y + len - 1) + A(y + len, n);
	else return A(1, x - 1) + B(x, x + len - 1) + A(x + len, y - 1) + B(y, y + len - 1) + A(y + len, n);
}

ll cnt(ll val) { // solutions <= val
	ll ans = 0, inv = 0, outv = 0;
	Node *inx = nullptr, *out = nullptr;
	for (int i = 2; i + len - 1 <= n; i++) {
		if (i <= len) Insert(inx, getval(1, i));
		else Insert(out, getval(1, i));
	}

	ans += Cnt(inx, val - inv);
	ans += Cnt(out, val - outv);
	for (int i = 2; i + len <= n; i++) {
		Erase(inx, getval(i - 1, i) - inv);
		if (i + len - 1 + len - 1 <= n) Erase(out, getval(i - 1, i + len - 1) - outv);

		inv += c[i + len - 1] - b[i + len - 1] - b[i - 1] + a[i - 1];
		outv += b[i + len - 1] - a[i + len - 1] - b[i - 1] + a[i - 1];

		if (i + len - 1 + len - 1 <= n && len > 1) Insert(inx, getval(i, i + len - 1) - inv);

		ans += Cnt(inx, val - inv);
		ans += Cnt(out, val - outv);
	}

	return ans;
}

int main() {
	ll k, l = 0, r = kInf, mid;
	scanf("%d%d%lld", &n, &len, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", &c[i]);
	for (int i = 1; i <= n; i++) sa[i] = sa[i - 1] + a[i];
	for (int i = 1; i <= n; i++) sb[i] = sb[i - 1] + b[i];
	for (int i = 1; i <= n; i++) sc[i] = sc[i - 1] + c[i];
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (cnt(mid) >= k) r = mid;
		else l = mid;
	}
	printf("%lld\n", r);
} 
