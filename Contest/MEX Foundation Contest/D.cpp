#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 120010, kBlk = 256, kBs = 2 * (kN / kBlk + 5);

struct Block {
	int l, r, mn, mx, has_left_mn, has_right_mx;
	bool complete, dirty;
	vector<int> vals, vals_sorted;
};

void RebuildBlock(Block &blk, bool resort = true) {
	static int pref_mn[kBlk], suff_mx[kBlk];
	blk.has_left_mn = INT_MAX;
	blk.has_right_mx = INT_MIN;
	blk.complete = false;
	int r = int(blk.vals.size());
	pref_mn[0] = blk.vals[0];
	suff_mx[r - 1] = blk.vals[r - 1];
	for (int i = 1; i < r; i++) pref_mn[i] = min(pref_mn[i - 1], blk.vals[i]);
	for (int i = r - 2; i >= 0; i--)
		suff_mx[i] = max(suff_mx[i + 1], blk.vals[i]);
	blk.mn = pref_mn[r - 1];
	blk.mx = suff_mx[0];
	for (int i = 1; i < r; i++) {
		if (pref_mn[i - 1] < blk.vals[i]) {
			blk.has_left_mn = min(blk.has_left_mn, blk.vals[i]);
		}
	}
	for (int i = 0; i < r - 1; i++) {
		if (blk.vals[i] < suff_mx[i + 1]) {
			blk.has_right_mx = max(blk.has_right_mx, blk.vals[i]);
		}
	}
	for (int i = 1; i < r - 1; i++) {
		if (pref_mn[i - 1] < blk.vals[i] && blk.vals[i] < suff_mx[i + 1]) {
			blk.complete = true;
			break;
		}
	}
	if (resort) {
		blk.vals_sorted.clear();
	}
}

bool BlockHasRange(Block &blk, int l, int r) {
	if (blk.vals_sorted.empty()) {
		blk.vals_sorted = blk.vals;
		sort(blk.vals_sorted.begin(), blk.vals_sorted.end());
	}
	return upper_bound(blk.vals_sorted.begin(), blk.vals_sorted.end(), r) !=
	       lower_bound(blk.vals_sorted.begin(), blk.vals_sorted.end(), l);
}

bool QueryAns(vector<Block> &blks) {
	static int pref_mn[kBs], suff_mx[kBs];
	int bs = int(blks.size());
	pref_mn[0] = blks[0].mn;
	suff_mx[bs - 1] = blks[bs - 1].mx;
	for (int i = 0; i < bs; i++) {
		if (blks[i].complete) return true;
	}
	for (int i = 1; i < bs; i++) pref_mn[i] = min(pref_mn[i - 1], blks[i].mn);
	for (int i = bs - 2; i >= 0; i--)
		suff_mx[i] = max(suff_mx[i + 1], blks[i].mx);
	for (int i = 1; i < bs; i++) {
		if (pref_mn[i - 1] < blks[i].has_right_mx) return true;
	}
	for (int i = 0; i < bs - 1; i++) {
		if (blks[i].has_left_mn < suff_mx[i + 1]) return true;
	}
	for (int i = 1; i < bs - 1; i++) {
		if (blks[i].dirty && pref_mn[i - 1] < suff_mx[i + 1]) {
			blks[i].dirty = false;
			if (BlockHasRange(blks[i], pref_mn[i - 1], suff_mx[i + 1])) return true;
		}
	}
	return false;
}

void SplitAt(vector<Block> &blks, int p) {
	int bs = int(blks.size());
	for (int i = 0; i < bs; i++) {
		if (blks[i].l <= p && p <= blks[i].r) {
			if (blks[i].l == p) return;
			Block new_blk{};
			new_blk.l = p;
			new_blk.r = blks[i].r;
			new_blk.vals = vector<int>(blks[i].vals.begin() + (p - blks[i].l), blks[i].vals.end());
			new_blk.dirty = blks[i].dirty;
			RebuildBlock(new_blk);
			blks.insert(blks.begin() + i + 1, std::move(new_blk));
			blks[i].r = p - 1;
			blks[i].vals.erase(blks[i].vals.begin() + (p - blks[i].l), blks[i].vals.end());
			RebuildBlock(blks[i]);
			return;
		}
	}
}

void Merge(vector<Block> &blks) {
	for (int i = 0; i < int(blks.size()) - 1; i++) {
		if (blks[i].vals.size() + blks[i + 1].vals.size() <= kBlk) {
			blks[i].r = blks[i + 1].r;
			blks[i].dirty |= blks[i + 1].dirty;
			blks[i].vals.insert(blks[i].vals.end(), blks[i + 1].vals.begin(), blks[i + 1].vals.end());
			RebuildBlock(blks[i], blks[i].vals_sorted.empty() || blks[i + 1].vals_sorted.empty());
			vector<int> sorted(blks[i].vals_sorted.size() + blks[i + 1].vals_sorted.size());
			merge(blks[i].vals_sorted.begin(), blks[i].vals_sorted.end(),
					blks[i + 1].vals_sorted.begin(), blks[i + 1].vals_sorted.end(), sorted.begin());
			blks[i].vals_sorted = std::move(sorted);
			blks.erase(blks.begin() + i + 1);
		}
	}
}

void SwapRange(vector<Block> &blks, int l, int m, int r) {
	SplitAt(blks, l);
	SplitAt(blks, m);
	SplitAt(blks, r + 1);
	int bs = int(blks.size());
	int lb = bs, mb = bs, rb = bs;
	for (int i = 0; i < bs; i++) {
		if (blks[i].l == l) lb = i;
		if (blks[i].l == m) mb = i;
		if (blks[i].l == r + 1) rb = i;
	}
	for (int i = lb; i < rb; i++) blks[i].dirty = true;
	rotate(blks.begin() + lb, blks.begin() + mb, blks.begin() + rb);
	int sum = 1;
	for (int i = 0; i < bs; i++) {
		blks[i].l = sum;
		blks[i].r = (sum += int(blks[i].vals.size())) - 1;
	}
	Merge(blks);
}

int main() {
	int n;
	cin >> n;
	vector<Block> blks(n / kBlk + 1);
	for (auto &b : blks) b.l = INT_MAX, b.dirty = true;
	for (int i = 1; i <= n; i++) {
		int h;
		cin >> h;
		int b = i / kBlk;
		blks[b].l = min(blks[b].l, i);
		blks[b].r = max(blks[b].r, i);
		blks[b].vals.push_back(h);
	}
	for (int i = 0; i < int(blks.size()); i++) {
		RebuildBlock(blks[i]);
	}
	int q;
	cin >> q;
	while (q--) {
		int l, r, k;
		cin >> l >> r >> k;
		if (k && k != r - l + 1) SwapRange(blks, l, r + 1 - k, r);
		cout << (QueryAns(blks) ? "YES" : "NO") << '\n';
	}
} 
