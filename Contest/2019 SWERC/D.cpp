#include <bits/stdc++.h>
using namespace std;

constexpr int64_t kMod = (1LL << 61) - 1;

struct Node {
	Node *l, *r;
	uint64_t hash;
	Node() {}
	Node(Node *ll, Node *rr, uint64_t h) : l(ll), r(rr), hash(h) {}
} pool[1'000'000], *head;

uint64_t MergeHash(uint64_t a, uint64_t b) {
	return uint64_t((__int128_t(a) * 318934129 + b) % kMod);
}

vector<uint64_t> CalcHash(const string &s) {
	head = pool;
	mt19937_64 rng(12378907);
	stack<Node*> stk;
	for (int i = 0; i < 20000; i++) {
		stk.push(new(head++) Node {nullptr, nullptr, uint64_t(rng() % kMod)});
	}
	Node *tmp = nullptr, *tmp2 = nullptr;
	for (char c : s) {
		switch (c) {
			case 'C':
				stk.push(stk.top());
				break;
			case 'D':
				stk.pop();
				break;
			case 'L':
			case 'R':
			case 'U':
				if (!stk.top()->l || !stk.top()->r) return {};
				tmp = stk.top();
				stk.pop();
				if (c == 'R' || c == 'U') stk.push(tmp->r);
				if (c == 'L' || c == 'U') stk.push(tmp->l);
				break;
			case 'P':
				tmp = stk.top();
				stk.pop();
				tmp2 = stk.top();
				stk.pop();
				stk.push(new(head++) Node {tmp, tmp2, MergeHash(tmp->hash, tmp2->hash)});
				break;
			case 'S':
				tmp = stk.top();
				stk.pop();
				tmp2 = stk.top();
				stk.pop();
				stk.push(tmp);
				stk.push(tmp2);
				break;
		}
	}
	vector<uint64_t> hash(stk.size());
	for (int i = 0; i < int(stk.size()); i++) {
		hash[i] = stk.top()->hash;
		stk.pop();
	}
	return hash;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	string a, b; cin >> a >> b;
	cout << (CalcHash(a) == CalcHash(b) ? "True\n" : "False\n");
} 
