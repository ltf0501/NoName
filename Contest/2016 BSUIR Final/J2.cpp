#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define x first
#define y second
const int kC = 1e5 + 10;
using D = long double;
const D kEps = 1e-6;

char CheckTriangle(pii p, pii q) {
	constexpr pii ps[3] = {
		{-3,-3},{2,3},{1,5}
		//{2, 1},
		//{1, 2},
		//{-1, -1},
	};

	bool flag = 0;	
	int a = q.y - p.y, b = q.x - p.x;
	if(a < 0 || (a == 0 && b < 0)) {
		flag = 1;
		a = -a, b = -b;
	}
	printf("a = %d, b = %d\n", a, b);
	int cnt[3] = {};
	for(int i = 0; i < 3; i++) {
		long long val = 1LL * a * (ps[i].x - p.x) - 1LL * b * (ps[i].y - p.y);
		printf("val = %lld\n", val);
		if(val == 0) cnt[1]++;
		else if(val > 0) cnt[2]++;
		else cnt[0]++;
	}
	printf("flag = %d\n", flag);
	printf("cnt: %d %d %d\n", cnt[0], cnt[1], cnt[2]);
	if(cnt[1]) return 'X';
	if(cnt[!flag ? 2 : 0] == 3) return '+';
	if(cnt[!flag ? 0 : 2] == 3) return '-';
	return 'X';
}

int Query(pii p, pii q) {
	printf("Q %d %d %d %d\n", p.x, p.y, q.x, q.y); fflush(stdout);
	char c[2];
	c[0] = CheckTriangle(p, q);
	//scanf("%s", c);
	int res = c[0] == '+' ? 1 : c[0] == '-' ? -1 : 0;
	printf("res = %d\n", res);
	return res;
}

void Answer(const vector<pii> &v) {
	printf("A ");
	for(pii p : v) printf("%d %d ", p.x, p.y); puts("");
	fflush(stdout);
	exit(0);
}
int main() { 
	int x[2], y[2];
	{
		int l = -kC, r = kC;	
		while(r - l > 1) {
			int m = (l + r) >> 1;
			if(Query({m, 0}, {m, 1}) < 0) r = m;
			else l = m;
		}
		x[1] = l;
	}
	{
		int l = -kC, r = kC;	
		while(r - l > 1) {
			int m = (l + r) >> 1;
			if(Query({0, m}, {-1, m}) < 0) r = m;
			else l = m;
		}
		y[1] = l;
	}
	{
		int l = -kC, r = kC;	
		while(r - l > 1) {
			int m = (l + r) >> 1;
			if(Query({m, 0}, {m, -1}) < 0) l = m;
			else r = m;
		}
		x[0] = r;
	}
	{
		int l = -kC, r = kC;	
		while(r - l > 1) {
			int m = (l + r) >> 1;
			if(Query({0, m}, {1, m}) < 0) l = m;
			else r = m;
		}
		y[0] = r;
	}
	printf("x[0] = %d, x[1] = %d, y[0] = %d, y[1] = %d\n", x[0], x[1], y[0], y[1]);

	bool isvertex[4];
	if(Query({x[1], y[1]}, {x[1] + 1, y[1] - 1}) == 0) isvertex[0] = 1;
	if(Query({x[0], y[1]}, {x[0] + 1, y[1] + 1}) == 0) isvertex[1] = 1;
	if(Query({x[0], y[0]}, {x[0] + 1, y[0] - 1}) == 0) isvertex[2] = 1;
	if(Query({x[1], y[0]}, {x[1] + 1, y[0] + 1}) == 0) isvertex[3] = 1;

	vector<pii> ans;
	if(isvertex[0]) v.emplace_back(x[1], y[1]);
	if(isvertex[1]) v.emplace_back(x[0], y[1]);
	if(isvertex[2]) v.emplace_back(x[0], y[0]);
	if(isvertex[3]) v.emplace_back(x[1], y[0]);

	int cnt = 0;
	for(int i = 0; i < 4; i++) cnt += isvertex[i];
	assert(cnt >= 1 && cnt <= 3);

	if(cnt == 3) {
		Answer(v);
	}
	else if(cnt == 2) {
		if(isvertex[0] && isvertex[2]) {
			{
				pii p = {x[0] - 1, y[0] - 1};
				int l = y[0], r = y[1];
				while(r - l > 1) {
					int m = (l + r) >> 1;
					if(Query({x[0], m}, p) < 0) r = m;
					else l = m;
				}
				if(l != y[0]) {
					ans.emplace_back(x[0], l);
					break;
				}
			}
			{
				pii p = {x[0] - 1, y[0] - 1};
				int l = x[0], r = x[1];
				while(r - l > 1) {
					int m = (l + r) >> 1;
					if(Query(p, {m, y[0]}) < 0) r = m;
					else l = m;
				}
				if(l != x[0]) {
					ans.emplace_back(l, y[0]);
					break;
				}
			}
			{
				pii p = {x[1] + 1, y[1] + 1};
				int l = y[0], r = y[1];
				while(r - l > 1) {
					int m = (l + r) >> 1;
					if(Query({x[1], m}, p) < 0) l = m;
					else r = m;
				}
				if(r != y[1]) {
					ans.emplace_back(x[1], r);
					break;
				}
			}
			{
				pii p = {x[1] + 1, y[1] + 1};
				int l = x[0], r = x[1];
				while(r - l > 1) {
					int m = (l + r) >> 1;
					if(Query(p, {m, y[1]}) < 0) l = m;
					else r = m;
				}
				if(r != x[1]) {
					ans.emplace_back(r, y[1]);
					break;
				}
			}
		}
		else if(isvertex[1] && isvertex[3]) {
		}
		else if(isvertex[0] && isvertex[1]) {
		}
		else if(isvertex[1] && isvertex[2]) {
		}
		else if(isvertex[2] && isvertex[3]) {
		}
		else if(isvertex[3] && isvertex[0]) {
		}
	}
	else {
		if(isvertex[0]) {
		}
		else if(isvertex[1]) {
		}
		else if(isvertex[2]) {
		}
		else if(isvertex[3]) {
		}
	}
	return 0;
}
