#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
constexpr int kN = int(3E3 + 10), kMod = int(1E9 + 7);

//ll rng() {
//	static ll x = 1293847195ll, y = 1235283975ll;
//	x = ((x << 15) | (x >> 5)) ^ y ^ (y << 13);
//	y = ((y << 3) ^ (y >> 14));
//	return x;
//}
mt19937 rng;

struct Node {
	shared_ptr<Node> l, r;
	ll sz;
	int val, cha;
	Node(shared_ptr<Node> n) {
		if (!n) {
			l = r = nullptr;
			val = sz = cha = 0;
		} else {
			l = n->l;
			r = n->r;
			val = n->val; sz = n->sz; cha = n->cha;
		}
	}
	Node(char c): l(), r() { val = c; sz = 1; cha = c;}
	Node(): Node('\0') {}
	void pull() {
		val = cha;
		sz = 1;
		if (l) sz += l->sz, val += l->val;
		if (r) sz += r->sz, val += r->val;
		val %= kMod;
		return ;
	}
};

ll GetSz(shared_ptr<Node> a) {
	return a ? a->sz : 0;
}

shared_ptr<Node> Merge(shared_ptr<Node> a, shared_ptr<Node> b) {
	if (!a) return b;
	if (!b) return a;
	float r = rng() / INT_MAX;
	if (r * (a->sz + b->sz) < a->sz) {
		auto n = make_shared<Node>(a);
		n->l = a->l;
		n->r = Merge(a->r, b);
		n->pull();
		return n;
	} else {
		auto n = make_shared<Node>(b);
		n->l = Merge(a, b->l);
		n->r  = b->r;
		n->pull();
		return n;
	}
}

void Split(shared_ptr<Node> s, int64_t val, shared_ptr<Node> &a, shared_ptr<Node> &b) {
	if (!s) {
		a = b = nullptr;
	} else {
		if (GetSz(s->l) + 1 <= val) {
			a = make_shared<Node>(s);
			Split(s->r, val - GetSz(s->l) - 1, a->r, b);
			a->pull();
		} else {
			b = make_shared<Node>(s);
			Split(s->l, val, a, b->l);
			b->pull();
		}
	}
	return ;
}

shared_ptr<Node> root[kN];

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int64_t n, x, y, l, r; 
	shared_ptr<Node> a, b, c, d;
	string s; 
	cin >> n >> s;
	--n;
	root[0] = nullptr;
	for (char i : s) root[0] = Merge(root[0], make_shared<Node>(i));
	for (int i = 1; i <= n; i++) {
		cin >> s;
		if (s[0] == 'S') {
			cin >> x >> l >> r;
			Split(root[x], r, a, b);
			Split(a, l, c, d);
			root[i] = d;
		}
		else {
			cin >> x >> y;
			root[i] = Merge(make_shared<Node>(root[x]), make_shared<Node>(root[y]));
		}
	}
	cout << root[n]->val << endl;
} 
