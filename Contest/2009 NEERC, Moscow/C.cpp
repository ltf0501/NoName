#include <bits/stdc++.h>
using namespace std;
const int kN = 5e4 + 10;

struct Node {
	char c;
	Node *l, *r;
	int seed, sz;
	Node(): l(nullptr), r(nullptr), sz(1) {}
	Node(char _c) {
		c = _c;
		l = r = nullptr;
		seed = rand();
		sz = 1;
	}
	void pull() {
		sz = 1;
		if(l) sz += l->sz;
		if(r) sz += r->sz; 
	}
};
int SZ(Node *o) {return o ? o->sz : 0;}

Node *Merge(Node *a, Node *b) {
	if(!a || !b) {
		return a ? a : b;
	}
	if(a->seed > b->seed) {
		a->r = Merge(a->r, b);
		a->pull();
		return a;
	}
	else {
		b->l = Merge(a, b->l);
		b->pull();
		return b; 
	}
} 
void print(Node *o) {
	//printf("sz = %d\n", SZ(o));
	if(SZ(o) == 0) return;
	//printf("[");
	print(o->l);
	printf("%c", o->c);
	print(o->r);
	//printf("]");
}
void Split(Node *o, Node* &a, Node* &b, int k) {

	if(!o) {
		a = b = nullptr;
		return;
	}
	//printf("k = %d: ", k);
	//print(o); puts("");
	if(SZ(o->l) >= k) {
		b = o;
		Split(o->l, a, b->l, k);
		b->pull();
	}
	else {
		a = o;
		Split(o->r, a->r, b, k - SZ(o->l) - 1);
		a->pull();
	}
}
char c[kN];
int l[kN], r[kN], k[kN];
Node *root;
int main() {
	srand(time(NULL));
	freopen("coding.in", "r", stdin);
	freopen("coding.out", "w", stdout);
	
	scanf("%s", c);
	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; i++) scanf("%d%d%d", &l[i], &r[i], &k[i]);
	int n = strlen(c);
	for(int i = 0; i < n; i++) root = Merge(root, new Node(c[i]));
	for(int i = q - 1; i >= 0; i--) {
		Node *a, *b, *c, *d, *e, *f;

		Split(root, a, b, l[i] - 1);
		//puts("a:");
		//print(a); puts("");
		//puts("b:");
		//print(b); puts("");
		Split(b, c, d, r[i] - l[i] + 1);
		Split(c, e, f, k[i]);
		//puts("c:");
		//print(c); puts("");
		//puts("d:");
		//print(d); puts("");
		//puts("e:");
		//print(e); puts("");
		//puts("f:");
		//print(f); puts("");
		root = Merge(Merge(a, Merge(f, e)), d);
		//print(root);
		//puts("");
	}
	print(root);
	puts("");
	return 0;
} 
