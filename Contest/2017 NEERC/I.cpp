#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string.h>
using namespace std;

#define F first
#define S second
#define PB push_back

constexpr int kN = int(1E4 + 10), kInf = int(1E9 + 10);

struct BIT {
	int val[kN];
	void init() {memset(val, 0, sizeof(val));}
	void add(int pos, int x) {
		while (pos < kN) {
			val[pos] += x;
			pos += pos & -pos;
		}
		return ;
	}
	int ask(int pos) {
		int ans = 0;
		while (pos) {
			ans += val[pos];
			pos ^= pos & -pos;
		}
		return ans;
	}
	int ask_pos(int v) {
		int ans = 0, nval = 0;
		for (int i = 20; i >= 0; i--) if (ans + (1 << i) < kN && nval + val[ans + (1 << i)] < v) {
			nval += val[ans + (1 << i)];
			ans += (1 << i);
		}
		return ans + 1;
	}
};

BIT bit;

bool ask(int a, int b) {
	string ans;
	cout << "? " <<  a << ' ' << b << endl;
	cin >> ans;
	return ans[0] == '<';
}

int ans[kN], num[kN], nsz;

pair<int, int> ask_position(int x) {
	int l = 1, r = nsz;
	while (r - l > 1) {
		int mid = (l + r) >> 1;
		if (ask(x, num[bit.ask_pos(mid)])) r = mid;
		else l = mid;
	}
	return {bit.ask_pos(l), bit.ask_pos(r + 1) - 1};
}

int main() {
	int n, l, r, mid_pos;
	pair<int, int> tmp;
	vector<int> emp, empA, empB;
	cin >> n;
	bit.init();
	if (n == 1) cout << "! 1" << endl;
	else {
		for (int i = 1; i <= (n + 1) / 2; i++) num[i] = i;
		bit.add((n + 1) / 2 + 1, kInf);
		bit.add(1, 1);
		nsz = 1;
		
		for (int i = 1; i <= n / 2; i++) {
			tmp = ask_position(i);
			empA.clear();
			empB.clear();
			l = bit.ask(tmp.F), r = bit.ask(tmp.S);
			if (l == r) {
				for (int j = tmp.F; j <= tmp.S; j++) {
					if (ask(i, num[j])) empB.PB(num[j]);
					else empA.PB(num[j]);
				}
				ans[i] = (tmp.F - 1 + int(empA.size())) << 1;
				bit.add(tmp.F + int(empA.size()), 1);
				for (int j : empB) empA.PB(j);
				for (int j = tmp.F; j <= tmp.S; j++) num[j] = empA[j - tmp.F];
			}
			else {
				mid_pos = bit.ask_pos(l + 1);
				for (int j = tmp.F; j < mid_pos; j++) {
					if (ask(i, num[j])) empB.PB(num[j]);
					else empA.PB(num[j]);
				}
				if (empB.empty()) {
					empA.clear();
					for (int j = mid_pos; j <= tmp.S; j++) {
						if (ask(i, num[j])) empB.PB(num[j]);
						else empA.PB(num[j]);
					}
					ans[i] = (mid_pos - 1 + int(empA.size())) << 1;
					bit.add(mid_pos + int(empA.size()), 1);
					for (int j : empB) empA.PB(j);
					for (int j = mid_pos; j <= tmp.S; j++) num[j] = empA[j - mid_pos];
				}
				else {
					ans[i] = (tmp.F - 1 + int(empA.size())) << 1;
					bit.add(tmp.F + int(empA.size()), 1);
					for (int j : empB) empA.PB(j);
					for (int j = tmp.F; j < mid_pos; j++) num[j] = empA[j - tmp.F];
				}
			}
			nsz++;
		}
		
		for (int i = 1; i <= (n + 1) / 2; i++) ans[num[i] + n / 2] = (i - 1) << 1 | 1;
		cout << '!';
		for (int i = 1; i <= n; i++) cout << ' ' << ans[i];
		cout << endl;
	} 
} 
