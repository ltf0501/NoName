#include <bits/stdc++.h>
using namespace std;

constexpr int kBlk = 512, kN = 100010, kC = 1'000'000'010;

int n;
vector<tuple<int, int, int>> red, blue;
vector<pair<int, int>> qu;
vector<vector<tuple<int, int, int>>> blk_val; // red
vector<vector<int>> blk_pfx, blk_blu;
vector<int> blk_ans, ans;
vector<vector<int>> mods, mod_y_to_blk_idx;

void Build(int b) {
	blk_val[b].clear();
	blk_pfx[b].clear();
	blk_blu[b].clear();
	int l = b * kBlk, r = min((b + 1) * kBlk, n) - 1;
	blk_val[b].reserve(r - l + 1);
	for (int i = l; i <= r; i++) blk_val[b].emplace_back(red[i]);
	sort(blk_val[b].begin(), blk_val[b].end(), [](auto lhs, auto rhs) {
			return get<1>(lhs) < get<1>(rhs); // Compare by height
		});
	blk_pfx[b].resize(blk_val[b].size());
	blk_pfx[b][0] = get<2>(blk_val[b][0]); // Prefix by weight
	for (int i = 1; i < int(blk_val[b].size()); i++) {
		blk_pfx[b][i] = max(blk_pfx[b][i - 1], get<2>(blk_val[b][i]));
	}
	blk_blu[b].resize(blk_val[b].size());
	fill(blk_blu[b].begin(), blk_blu[b].end(), -kC);
	blk_ans[b] = blk_pfx[b].back() - kC;
}

int Query(int l) {
	int ret = -kC, b = 0, max_blu = -kC;
	for (b = 0; ; b++) {
		int nxt_l = (b + 1) * kBlk;
		if (nxt_l >= n || get<0>(red[nxt_l]) >= l) break;
		if (ret < blk_ans[b]) ret = blk_ans[b];
	}
	for (int i = int(blk_val[b].size()) - 1; i >= 0; i--) {
		if (max_blu < blk_blu[b][i]) max_blu = blk_blu[b][i];
		if (get<0>(blk_val[b][i]) < l) {
			int tmp = get<2>(blk_val[b][i]) + max_blu;
			if (ret < tmp) ret = tmp;
		}
	}
	return ret;
}

void Modify(int height, int val, int idx) {
	for (int b = 0; b * kBlk < n; b++) {
		if (get<1>(blk_val[b][0]) >= height) continue;
		int p = mod_y_to_blk_idx[idx][b];
		if (blk_blu[b][p] < val) blk_blu[b][p] = val;
		blk_ans[b] = max(blk_ans[b], blk_pfx[b][p] + val);
	}
}

void RebuildModHeight(int mb) {
	vector<pair<int, int>> tmp_vec;
	tmp_vec.reserve(mods[mb].size());
	for (int i = 0; i < int(mods[mb].size()); i++) {
		tmp_vec.emplace_back(get<1>(blue[mods[mb][i]]), i);
	}
	sort(tmp_vec.begin(), tmp_vec.end());
	mod_y_to_blk_idx.resize(mods[mb].size());
	for (auto &v : mod_y_to_blk_idx) v.resize((n + kBlk - 1) / kBlk);
	for (int b = 0; b * kBlk < n; b++) {
		for (int i = 0, j = 0; i < int(mods[mb].size()); i++) {
			while (j + 1 < int(blk_val[b].size()) &&
					get<1>(blk_val[b][j + 1]) < tmp_vec[i].first) {
				++j;
			}
			mod_y_to_blk_idx[tmp_vec[i].second][b] = j;
		}
	}
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	cin >> n;
#ifdef RAND
	n = 99997;
#endif
	red.resize(n);
	blue.resize(n);
#ifdef RAND
	mt19937 rng;
	auto rnd = [&rng]() { return rng() % 1'000'000'000 + 1; };
#endif
	for (int i = 0; i < n; i++) {
		cin >> get<0>(red[i]) >> get<1>(red[i]) >> get<2>(red[i]);
#ifdef RAND
		red[i] = {-rnd(), rnd(), rnd()};
#endif
	}
	for (int i = 0; i < n; i++) {
		cin >> get<0>(blue[i]) >> get<1>(blue[i]) >> get<2>(blue[i]);
#ifdef RAND
		blue[i] = {rnd(), rnd(), rnd()};
#endif
	}
	int q; cin >> q;
#ifdef RAND
	q = 500000;
#endif
	qu.resize(q);
	ans.resize(q);
	for (int i = 0; i < q; i++) {
		cin >> qu[i].first >> qu[i].second;
#ifdef RAND
		qu[i] = {-rnd(), rnd()};
#endif
	}
	for (int kind = 0; kind < 2; kind++) {
		vector<tuple<int, int, int, int>> operations;
		operations.reserve(n + q);
		if (kind == 1) {
			// Flip x coordinates
			for (int i = 0; i < n; i++) get<0>(red[i]) = -kC - get<0>(red[i]);
			for (int i = 0; i < n; i++) get<0>(blue[i]) = kC - get<0>(blue[i]);
			for (int i = 0; i < q; i++) qu[i] = {-kC - qu[i].first, kC - qu[i].second};
		}
		sort(red.begin(), red.end());
		for (int i = 0; i < n; i++) {
			// x, y, w, id
			operations.emplace_back(get<0>(blue[i]), get<1>(blue[i]), get<2>(blue[i]), i);
		}
		for (int i = 0; i < q; i++) {
			// r, l, -1, id
			operations.emplace_back(qu[i].second, qu[i].first, -1, i);
		}
		sort(operations.begin(), operations.end(), greater<tuple<int, int, int, int>>());
		blk_val.resize((n + kBlk - 1) / kBlk);
		blk_pfx.resize((n + kBlk - 1) / kBlk);
		blk_blu.resize((n + kBlk - 1) / kBlk);
		blk_ans.resize((n + kBlk - 1) / kBlk);
		for (int b = 0; b * kBlk < n; b++) Build(b);
		mods.clear();
		mods.reserve((n + kBlk - 1) / kBlk);
		mods.emplace_back();
		for (auto _t : operations) {
			if (get<2>(_t) != -1) { // Blue point
				mods.back().push_back(get<3>(_t));
				if (mods.back().size() >= kBlk) mods.emplace_back();
			}
		}
		int mod_blk = 0, mod_id = 0;
		for (auto _t : operations) {
			if (get<2>(_t) == -1) { // Query
				auto [r, l, _, idx] = _t;
				ans[idx] = max(ans[idx], Query(l));
			} else { // Blue point
				auto [x, y, w, idx] = _t;
				if (!mod_id) RebuildModHeight(mod_blk);
				Modify(y, w, mod_id);
				if (++mod_id == kBlk) {
					++mod_blk;
					mod_id = 0;
				}
			}
		}
	}
	for (int i = 0; i < q; i++) cout << (ans[i] > 0 ? ans[i] : -1) << '\n';
} 
