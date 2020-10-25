#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kC = 1e6 + 10;
const int kN = 1e5 + 10;
const ll kInf = 1E12;

static inline char GetRawChar() {
	static char buf[1 << 16], *p = buf, *end = buf;
	if (p == end) {
		if ((end = buf + fread(buf, 1, 1 << 16, stdin)) == buf) return '\0';
		p = buf;
	}
	return *p++;
}

static inline ll GetInt() {
	ll n = 0;
	char c;
	while ((c = GetRawChar()) && (unsigned)(c - '0') <= 10U) n = n * 10 + (c - '0');
	return n;
}

struct Data {
	int prime[40], sz, lsz;
	ll x;
	void Init(int x) {
		this->x = x;
		sz = 0; 
		for(int i = 2; 1LL * i * i <= (this->x); i++) {
			while(x % i == 0) {
				x /= i;
				prime[sz++] = i;
			}
			if(x == 1) break;
		}
		if(x != 1) prime[sz++] = x;
		lsz = sz;
	}

	bool operator < (const Data &b) const {
		for(int i = 0; i < min(sz, b.sz); i++) {
			if(prime[i] != b.prime[i]) return prime[i] > b.prime[i];
		}
		return sz < b.sz;
	}

	void add(int p, int num) {
		for(int i = 0; i < num; i++) prime[sz++] = p;
	}

	void rs(int num) {
		sz = lsz + num;
	}

	void pull() {
		for (int i = lsz; i < sz; i++) x *= prime[i];
		lsz = sz;
	}

	void print() {
		printf("sz = %d\n", sz);
		printf("prime: ");
		for(int i = 0; i < sz; i++) printf("%d ", prime[i]); puts("");
	}
};

Data Merge(Data a, Data b) {
	Data res;
	res.Init(1);
	int j = 0;
	for(int i = 0; i < a.sz; i++) {
		while(j < b.sz && b.prime[j] <= a.prime[i]) res.add(b.prime[j++], 1);
		res.add(a.prime[i], 1);
	}
	while(j < b.sz) res.add(b.prime[j++], 1);
	return res;
}
int n, m;
ll k;
Data a[kN], b[kN];

bool notp[kC];
vector<int> pr;
void pre() {
	for(int i = 2; i <= 1'000'000; i++) {
		if(!notp[i]) pr.push_back(i);
		for(int j = 0; j < int(pr.size()) && 1LL * i * pr[j] <= 1'000'000; j++) {
			notp[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}

int main() {
	int T = GetInt();
	pre();
	while(T--) {
		n = GetInt(), m = GetInt(), k = GetInt();
		//scanf("%d%d%lld", &n, &m, &k);
		for(int i = 1; i <= n; i++) {
			int x = GetInt();
			a[i].Init(x);
		}
		for(int i = 1; i <= m; i++) {
			int x = GetInt();
			b[i].Init(x);
		}
		sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);

		//for(int i = 1; i <= n; i++) printf("%d ", a[i].x); puts("");
		//for(int i = 1; i <= m; i++) printf("%d ", b[i].x); puts("");

		Data ans;
		ans.Init(1);

		auto Cal = [&]() {
			ll num = 0;
			for(int i = 1, j = m; i <= n;	i++) {
				while(j > 0) {
					Data tmp = Merge(a[i], b[j]);
					//printf("ans = %d, tmp = %d\n", ans.x, tmp.x);
					if(!(tmp < ans)) j--;
					//if(ans <= tmp) j--;
					else break;
				}
				//printf("i = %d, j = %d\n", i, j);
				num += j;
			}
			return num;
		};
		int o = 0, l, r;
		for(o = 0; pr[o] < 100; o++) {
			int p = pr[o];

			int l = 0, r = 0;
			ll mx = ans.x;
			while(mx < kInf) r++, mx *= p; 
			if (r < 5) break;
			ans.add(p, r - 1);
			while(r - l > 1) {
				int mid = (l + r) >> 1;
				ans.rs(mid);
				if(Cal() >= k) r = mid;
				else l = mid;
			}
			ans.rs(l);
			ans.pull();
		}

		while(true) {
			l = o - 1, r = int(pr.size());
			while(r - l > 1) {
				int mid = (l + r) >> 1;
				ans.add(pr[mid], 1);
				if(Cal() >= k) l = mid;
				else r = mid;
				ans.rs(0);
				ans.pull();
			}

			if(r == int(pr.size())) break;
			o = r;
			ans.add(pr[o], 1);
			ans.pull();
		}
		//ans.print();
		printf("%lld\n", ans.x);
	}
	return 0;
} 
