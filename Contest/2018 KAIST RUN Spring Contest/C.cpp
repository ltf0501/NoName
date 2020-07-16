#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 260000, kC = 310000;
constexpr double kInf = 1e16;

int64_t dp[kN];
int fs[kN], cs[kN], ls[kN];

struct HLine {
	static bool flag;
	int64_t a, b;
	double l, r;
	double operator()(double x) const {
		return a * x + b;
	}
	bool operator<(const HLine &rhs) const {
		return flag ? a < rhs.a || (a == rhs.a && b < rhs.b) : l < rhs.l;
	}
};

double Intersect(HLine p, HLine q) {
	assert(p.a != q.a);
	return double(q.b - p.b)  / double(p.a - q.a);
}

bool HLine::flag = true;

struct ConvexHull {
	set<HLine> lines_;
	ConvexHull() { HLine::flag = true; }
	void Init() { lines_.clear(); }
	void Insert(int64_t a, int64_t b) {
		HLine now = {a, b, -kInf, kInf};
		if (lines_.empty()) {
			lines_.insert(now);
			return;
		}
		HLine::flag = true;
		auto it = lines_.lower_bound(now);
		auto prv = (it == lines_.begin()) ? it : prev(it);
		if (it != lines_.end()) {
			if (it == lines_.begin() && it->a == now.a) {
				return;
			}
			double x = it->l;
			if (it != lines_.begin() && now(x) <= (*it)(x)) {
				return;
			}
		}
		if (it != lines_.begin()) {
			for (; prv != lines_.begin() && (*prv)(prv->l) <= now(prv->l);) {
				prv = --lines_.erase(prv);
			}
			if (prv == lines_.begin() && now.a == prv->a) {
				lines_.erase(prv);
			}
		}
		if (it != lines_.end()) {
			while (it != --lines_.end() && (*it)(it->r) <= now(it->r)) {
				it = lines_.erase(it);
			}
		}
		if (it != lines_.begin()) {
			prv = prev(it);
			double x = Intersect(*prv, now);
			const_cast<HLine*>(&*prv)->r = now.l = x;
		}
		if (it != lines_.end()) {
			double x = Intersect(now, *it);
			const_cast<HLine*>(&*it)->l = now.r = x;
		}
		lines_.insert(now);
	}
	double Query(double a) {
		if (lines_.empty()) return -kInf;
		HLine::flag = 0;
		auto it = --lines_.upper_bound({0, 0, a, 0});
		return (*it)(a);
	}
} hull[kC + 1];

int64_t Query(int p, int x) {
	int64_t ret = int64_t(-kInf);
	for (; p; p -= p & -p) ret = max(ret, int64_t(hull[p].Query(x)));
	return ret;
}

void Modify(int64_t p, int64_t a, int64_t b) {
	for (; p <= kC; p += p & -p) hull[p].Insert(a, b);
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> fs[i];
		fs[i] += i;
	}
	for (int i = 1; i <= n; i++) cin >> cs[i];
	for (int i = 1; i <= n; i++) {
		cin >> ls[i];
		ls[i] += i;
	}
	for (int i = 1; i <= n; i++) {
		dp[i] = int64_t(-kInf);
		if (fs[i] >= ls[i]) {
			dp[i] = max<int64_t>(dp[i], dp[i - 1] + 1LL * (fs[i] - i) * cs[i]);
		}
		dp[i] = max<int64_t>(dp[i], Query(kC - ls[i], cs[i]) - 1LL * i * cs[i]);
		Modify(kC - fs[i], fs[i], dp[i - 1]);
	}
	if (dp[n] < 0) cout << "Impossible\n";
	else cout << dp[n] << '\n';
} 
