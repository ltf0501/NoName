#include <bits/stdc++.h>
using namespace std;

constexpr int kC = 21'0000 - 5;
using L = tuple<int, int, int, int>;
using D = long double;
constexpr D kEps = 1e-6;
int query_cnt;

char CheckTriangle(L l) {
	constexpr pair<int, int> ps[3] = {
		{-3,-3},{2,3},{1,5}
		//{2, 1},
		//{1, 2},
		//{-1, -1},
	};
	int cnt[3] = {};
	D dy = (get<3>(l) - get<1>(l));
	D dx = (get<2>(l) - get<0>(l));
	//cerr << dy << ' ' << dx << '\n';
	bool rev = false;
	if (dy < 0) {
		rev = true;
		dy *= -1;
		dx *= -1;
		swap(get<0>(l), get<2>(l));
		swap(get<1>(l), get<3>(l));
	}
	for (auto p : ps) {
		//cerr << dy << ' ' << p.first << ' ' << p.second << ' ' << get<0>(l) << ' ' << get<1>(l) << '\n';
		D c = dy * p.first - dx * p.second - dy * get<0>(l) + dx * get<1>(l);
		//cerr << c << '\n';
		if (abs(c) < kEps) ++cnt[1];
		else if (c > 0) ++cnt[2];
		else ++cnt[0];
	}
	//for (int i = 0; i < 3; i++) cerr << cnt[i] << ' ';
	//cerr << '\n';
	if (cnt[1]) return 'X';
	if (cnt[rev ? 2 : 0] == 3) return '+';
	if (cnt[rev ? 0 : 2] == 3) return '-';
	return 'X';
}

int Query(int x1, int y1, int x2, int y2) {
	++query_cnt;
	cout << "Q " << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
//	char ch;
//	cin >> ch;
	char ch = CheckTriangle({x1,y1,x2,y2});
	cerr << ch << '\n';
	return ch == '+' ? 1 : ch == '-' ? -1 : 0;
}

void Answer(vector<pair<int, int>> v) {
	cout << 'A';
	for (auto p : v) {
		cout << ' ' << p.first << ' ' << p.second;
	}
	cout << endl;
	cerr << query_cnt << '\n';
	//exit(0);
}

pair<int, int> Intersection(L a, L b) {
	int64_t dy1 = get<3>(a) - get<1>(a);
	int64_t dx1 = get<2>(a) - get<0>(a);
	int64_t dy2 = get<3>(b) - get<1>(b);
	int64_t dx2 = get<2>(b) - get<0>(b);
	int64_t a1 = dy1, b1 = -dx1, c1 = dy1 * get<0>(a) - dx1 * get<1>(a);
	int64_t a2 = dy2, b2 = -dx2, c2 = dy2 * get<0>(b) - dx2 * get<1>(b);
	D num = a1 * b2 - a2 * b1;
	D x = (c1 * b2 - c2 * b1) / num;
	D y = (a1 * c2 - a2 * c1) / num;
	return {int(round(x)), int(round(y))};
}

bool OnLine(L l, pair<int, int> p) {
	D dy = (get<3>(l) - get<1>(l));
	D dx = (get<2>(l) - get<0>(l));
	D lhs = dx * p.second;
	D rhs = dy * (p.first - get<0>(l)) + dx * get<1>(l);
	return abs(lhs - rhs) < kEps;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	vector<L> lines;
	vector<pair<L, L>> qs = {
		{{-kC, -kC, kC, -kC}, {0, 1, 0, 1}}, // N
		{{kC, -kC, kC, kC}, {-1, 0, -1, 0}}, // W
		{{kC, kC, -kC, kC}, {0, -1, 0, -1}}, // S
		{{-kC, kC, -kC, -kC}, {1, 0, 1, 0}}, // E
	};
	for (auto [_p, _d] : qs) {
		auto [x1, y1, x2, y2] = _p;
		auto [dx1, dy1, dx2, dy2] = _d;
		int l = 0, r = 4 * kC;
		int correct = Query(x1, y1, x2, y2);
		while (r - l > 1) {
			int m = (l + r) >> 1;
			int nx1 = x1 + dx1 * m;
			int ny1 = y1 + dy1 * m;
			int nx2 = x2 + dx2 * m;
			int ny2 = y2 + dy2 * m;
			int q = Query(nx1, ny1, nx2, ny2);
			if (q && ((q > 0) == (correct > 0))) l = m;
			else r = m;
		}
		int nx1 = x1 + dx1 * r;
		int ny1 = y1 + dy1 * r;
		int nx2 = x2 + dx2 * r;
		int ny2 = y2 + dy2 * r;
		lines.emplace_back(nx1, ny1, nx2, ny2);
	}
	for (auto l : lines) {
		cerr << get<0>(l) << ' ' << get<1>(l) << ' ' << get<2>(l) << ' ' << get<3>(l) << '\n';
	}
	vector<pair<int, int>> pts;
	int n = int(lines.size());
	for (int i = 0; i < n; i++) {
		pts.push_back(Intersection(lines[i], lines[(i + 1) % n]));
	}
	for (auto l : pts) {
		cerr << get<0>(l) << ' ' << get<1>(l) << '\n';
	}
	for (int i = 0; i < (1 << n); i++) {
		vector<pair<int, int>> cur;
		for (int j = 0; j < n; j++) {
			if (i & (1 << j)) cur.push_back(pts[j]);
		}
		sort(cur.begin(), cur.end());
		cur.erase(unique(cur.begin(), cur.end()), cur.end());
		if (cur.size() != 3) continue;
		bool fail = false;
		for (int j = 0; j < n; j++) {
			bool ok = false;
			for (int k = 0; k < 3; k++) {
				ok |= OnLine(lines[j], cur[k]);
			}
			if (!ok) {
				fail = true;
				break;
			}
		}
		if (!fail) {
			Answer(cur);
		}
	}
	assert(0);
}
