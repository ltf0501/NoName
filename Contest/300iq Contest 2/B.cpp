#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long int ll;
constexpr ll kC = (1ll << 61);
constexpr int kN = int(3E5 + 10), kMod = 998244353;

struct Node {
	Node *l, *r;
	ll val;
	Node(){l = r = nullptr; val = 0;}
};

void insert(Node* u, ll x, ll v, ll bit) {
	u->val += v;
	u->val %= kMod;
	if (!bit) return ;
	if (x & bit) {
		if (!u->r) u->r = new Node();
		insert(u->r, x, v, bit >> 1);
	}
	else {
		if (!u->l) u->l = new Node();
		insert(u->l, x, v, bit >> 1);
	}
	return ;
}

ll ask(Node* u, ll y, ll x, ll bit) {
	if (!u) return 0;
	if (!bit) return u->val;
	ll ans;
	if (x & y & bit) ans = ask(u->l, y, x, bit >> 1);
	else if (x & bit) ans = ask(u->r, y, x, bit >> 1);
	else if (y & bit) ans = (u->l ? u->l->val : 0) + ask(u->r, y, x, bit >> 1);
	else ans = (u->r ? u->r->val : 0) + ask(u->l, y, x, bit >> 1);
	return ans % kMod;
}

ll a[kN];

int main() {
	ll n, x;
	ll tmp, ans = 0, vv;
	Node* root = new Node();
	scanf("%lld%lld", &n, &x);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		vv = 1;
		insert(root, a[i], tmp = (ask(root, a[i], x, kC) + 1) * vv % kMod, kC);
		ans += tmp;
	}
	printf("%lld\n", ans % kMod);
}
