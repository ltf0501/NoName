#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define PB push_back

constexpr int kN = int(1E2 + 10);
constexpr double kEps = 1E-9;

map<string, int> m;
vector<int> a[kN], b[kN];
int now = 0;

void input(int x) {
	int n;
	bool f = false;
	string s, tmp;
	while (s.size() < 3) getline(cin, s);
	n = int(s.size());
	a[x].clear();
	b[x].clear();
	//cout << "input : " << s << '\n';
	for (int i = 0; i < n; i++) if (s[i] == ' ') {
		if (!f) {
			if (m.find(tmp) != m.end()) a[x].PB(m[tmp]);
			else a[x].PB(m[tmp] = now++);
		}
		else {
			if (m.find(tmp) != m.end()) b[x].PB(m[tmp]);
			else b[x].PB(m[tmp] = now++);
		}
		tmp.clear();
	}
	else if (s[i] == '=' || s[i] == '?') {
		f = true;
		i++;
	}
	else tmp += s[i];
	if (m.find(tmp) != m.end()) b[x].PB(m[tmp]);
	else b[x].PB(m[tmp] = now++);
	//cout << "a :";
	//for (int i : a[x]) cout << " " << i;
	//cout << '\n';
	//cout << "b :";
	//for (int i : b[x]) cout << " " << i;
	//cout << '\n';
	assert(now <= 40 && !a[x].empty() && !b[x].empty());
	return ;
}

double ABS(double n) {return n >= 0 ? n : -n;}
double val[1610];

struct Board {
	double a[1610][1610];
	int sz;
	void init() {
		memset(a, 0, sizeof(a));
		sz = 0;
		return ;
	}
	bool insert() {
		bool f = false;
		int now = 0;
		double tmp;
		//printf("insert\n");
		//for (int i = 0; i < 1610; i++) if (ABS(val[i]) > kEps) printf("(%d, %lf)\n", i, val[i]);
		//printf("\n");
		for (int i = 0; i < sz; i++) {
			if (ABS(val[now]) > kEps) {
				if (ABS(a[i][now]) > kEps) {
					tmp = val[now] / a[i][now];
					for (int j = 0; j < 1610; j++) val[j] -= a[i][j] * tmp;
					//printf("now = %d, fuck with %d\n", now, i);
					now++;
				}
				else {
					for (int j = 0; j < 1610; j++) swap(val[j], a[i][j]);
					//printf("now = %d, swp with %d\n", now, i);
					now++;
				}
			}
			else if (ABS(a[i][now]) <= kEps) {
				now++;
				i--;
			}
		}
		for (int i = 0; i < 1610; i++) if (ABS(val[i]) > kEps) {
			for (int j = 0; j < sz; j++) {
				tmp = a[j][i] / val[i];
				for (int k = 0; k < 1610; k++) a[j][k] -= val[k] * tmp; 
			}
			f = true;
			break;
		}
		//for (int i = 0; i < 1610; i++) if (ABS(val[i]) > kEps) printf("(%d, %lf)\n", i, val[i]);
		if (!f) return false;
		for (int i = 0; i < 1610; i++) a[sz][i] = val[i];
		sz++;
		return true;
	}
};
Board board;

int main() {
	freopen("equality.in", "r", stdin);
	freopen("equality.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) input(i);
	board.init();
	for (int i = 1; i <= n; i++) {
		memset(val, 0, sizeof(val));
		for (int j = 1; j < int(a[i].size()); j++) val[a[i][j - 1] * 40 + a[i][j]] += 1;
		for (int j = 1; j < int(b[i].size()); j++) val[b[i][j - 1] * 40 + b[i][j]] -= 1;
		board.insert();
	}
	for (int i = 1; i <= 1; i++) {
		input(i);
		memset(val, 0, sizeof(val));
		for (int j = 1; j < int(a[i].size()); j++) val[a[i][j - 1] * 40 + a[i][j]] += 1;
		for (int j = 1; j < int(b[i].size()); j++) val[b[i][j - 1] * 40 + b[i][j]] -= 1;
		if (board.insert()) cout << "DUNNO" << '\n';
		else cout << "YES" << '\n';
	}
} 
