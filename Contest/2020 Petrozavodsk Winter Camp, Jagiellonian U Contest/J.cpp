#include <bits/stdc++.h>
using namespace std;

constexpr int kDir[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
constexpr int kN = 300100, kC = 1000100;

int par[kN + kC * 4], px[kN], py[kN], pz[kN], n;

int Find(int x) {
	return par[x] == x ? x : par[x] = Find(par[x]);
}

void Merge(int x, int y) {
	//cerr << "Merge: " << x << ' ';
	//if (y < n) cerr << "P" << y << '\n';
	//else if (y < n + kC * 1) cerr << "X" << y - 1 - n - kC * 0 << '\n';
	//else if (y < n + kC * 2) cerr << "Y" << y - 1 - n - kC * 1  << '\n';
	//else if (y < n + kC * 3) cerr << "Z" << y - 1 - n - kC * 2  << '\n';
	int xp = Find(x), yp = Find(y);
	par[xp] = yp;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	while (t--) {
		cin >> n;
		map<tuple<int, int, int>, int> st;
		map<int, int> st_plane[3][3];
		for (int i = 0; i < n; i++) {
			cin >> px[i] >> py[i] >> pz[i];
			auto it = st.find({px[i], py[i], pz[i]});
			if (it != st.end()) {
				Merge(i, it->second);
			} else {
				st[{px[i], py[i], pz[i]}] = i;
			}
			if (px[i] == -1) {
				st_plane[0][1][py[i]] = i;
				st_plane[0][2][pz[i]] = i;
			} else if (py[i] == -1) {
				st_plane[1][0][px[i]] = i;
				st_plane[1][2][pz[i]] = i;
			} else if (pz[i] == -1) {
				st_plane[2][0][px[i]] = i;
				st_plane[2][1][py[i]] = i;
			}
		}
		for (int i = 0; i < n + kC * 4; i++) par[i] = i;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 4; j++) {
				if (px[i] == -1) {
					auto it = st.find({-1, py[i] + kDir[j][0], pz[i] + kDir[j][1]});
					if (it != st.end()) Merge(i, it->second);
				} else if (py[i] == -1) {
					auto it = st.find({px[i] + kDir[j][0], -1, pz[i] + kDir[j][1]});
					if (it != st.end()) Merge(i, it->second);
				} else if (pz[i] == -1) {
					auto it = st.find({px[i] + kDir[j][0], py[i] + kDir[j][1], -1});
					if (it != st.end()) Merge(i, it->second);
				}
			}
		}
		//for (int i = 0; i < n; i++) {
		//	if (px[i] != -1) Merge(i, px[i] + 1 + n + kC * 0);
		//	if (py[i] != -1) Merge(i, py[i] + 1 + n + kC * 1);
		//	if (pz[i] != -1) Merge(i, pz[i] + 1 + n + kC * 2);
		//}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					if (j == k) continue;
					int vs[3] = {px[i], py[i], pz[i]};
					if (vs[3 - j - k] == -1) {
						int v = vs[k];
						if (st_plane[j][k].count(v + 1)) {
							Merge(i, ((v + 1) + 1) + n + kC * k);
							Merge(i, ((v + 0) + 1) + n + kC * k);
						}
						if (st_plane[j][k].count(v + 0)) {
							Merge(i, ((v + 0) + 1) + n + kC * k);
						}
						if (st_plane[j][k].count(v - 1)) {
							Merge(i, ((v - 1) + 1) + n + kC * k);
							Merge(i, ((v + 0) + 1) + n + kC * k);
						}
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			//cerr << i << ' ' << Find(i) << '\n';
		}
		int q; cin >> q;
		while (q--) {
			int x[2], y[2], z[2]; cin >> x[0] >> y[0] >> z[0] >> x[1] >> y[1] >> z[1];
			int blk[2] = {-1, -1};
			for (int i = 0; i < 2; i++) {
				decltype(st)::iterator it;
				if ((it = st.find({-1, y[i], z[i]})) != st.end()) {
					blk[i] = Find(it->second);
				} else if ((it = st.find({x[i], -1, z[i]})) != st.end()) {
					blk[i] = Find(it->second);
				} else if ((it = st.find({x[i], y[i], -1})) != st.end()) {
					blk[i] = Find(it->second);
				} else {
					assert(0);
				}
			}
			//cerr << blk[0] << ' ' << blk[1] << '\n';
			cout << (blk[0] == blk[1] ? "YES\n" : "NO\n");
		}
	}
}
