#include <bits/stdc++.h>
using namespace std;
#define PB push_back

int cnt[7];
int five(vector<int> v) {
	for (int i = 1; i <= 6; i++) cnt[i] = 0;
	for (int i : v) cnt[i]++;
	for (int i = 1; i <= 6; i++) if (cnt[i] == 5) return 50;
	if (cnt[1] && cnt[2] && cnt[3] && cnt[4] && cnt[5]) return 40;
	if (cnt[6] && cnt[2] && cnt[3] && cnt[4] && cnt[5]) return 40;
	if (cnt[1] && cnt[2] && cnt[3] && cnt[4]) return 30;
	if (cnt[5] && cnt[2] && cnt[3] && cnt[4]) return 30;
	if (cnt[5] && cnt[6] && cnt[3] && cnt[4]) return 30;
	for (int i = 1; i <= 6; i++) for (int j = 1; j <= 6; j++) if (cnt[i] == 3 && cnt[j] == 2) return 25;
	for (int i = 1; i <= 6; i++) if (cnt[i] == 4) return i * 4;
	for (int i = 1; i <= 6; i++) if (cnt[i] == 3) return i * 3;
	return 0;
}

struct Set {
	tuple<char, int, int> domino[14];
	void in() {
		int a, b;
		string type;
		for (int i = 1; i <= 13; i++) {
			cin >> type;
			if (type[0] == 'V') {
				cin >> a >> b;
				domino[i] = {type[0], a, b};
			}
			else if (type[0] == 'H') {
				cin >> a >> b;
				domino[i] = {type[0], a, b};
			}
			else {
				cin >> a;
				domino[i] = {type[0], a, 0};
			}
		}
		return ;
	}
};

struct Board {
	int val[5][5];
	void Make(Set se) {
		int a, b;
		char type;
		bool f;
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) val[i][j] = 0;
		for (int i = 1; i <= 13; i++) {
			type = get<0>(se.domino[i]);
			a = get<1>(se.domino[i]);
			b = get<2>(se.domino[i]);
			f = false;
			if (type == 'V') {
				for (int x = 0; x < 4 && !f; x++) for (int y = 0; y < 5 && !f; y++) if (val[x][y] == 0 && val[x + 1][y] == 0) {
					val[x][y] = a;
					val[x + 1][y] = b;
					f = true;
				}
			}
			else if (type == 'H') {
				for (int x = 0; x < 5 && !f; x++) for (int y = 0; y < 4 && !f; y++) if (val[x][y] == 0 && val[x][y + 1] == 0) {
					val[x][y] = a;
					val[x][y + 1] = b;
					f = true;
				}
			}
			else {
				for (int x = 0; x < 5 && !f; x++) for (int y = 0; y < 5 && !f; y++) if (val[x][y] == 0) {
					val[x][y] = a;
					f = true;
				}
			}
		}
		return ;
	}
	void out() {
		for (int i = 0; i < 5; i++, cout << "\n") for (int j = 0; j < 5; j++) cout << val[i][j];
		cout << "\n";
		return ;
	}
	int cal() {
		vector<int> tmp;
		int ans = 0, fcnt = 0, tval;
		for (int i = 0; i < 5; i++) {
			tmp.clear();
			for (int j = 0; j < 5; j++) tmp.PB(val[i][j]);
			tval = five(tmp);
			if (tval == 50) fcnt++;
			else ans += tval;
			tmp.clear();
			for (int j = 0; j < 5; j++) tmp.PB(val[j][i]);
			tval = five(tmp);
			if (tval == 50) fcnt++;
			else ans += tval;
		}
		tmp.clear();
		for (int i = 0; i < 5; i++) tmp.PB(val[i][i]);
		tval = five(tmp);
		if (tval == 50) fcnt++;
		else ans += tval;
		tmp.clear();
		for (int i = 0; i < 5; i++) tmp.PB(val[i][4 - i]);
		tval = five(tmp);
		if (tval == 50) fcnt++;
		else ans += tval;
		if (fcnt == 0) return ans;
		return ans + fcnt * 100 - 50;
	}
};

bool used[7][7];

int solve() {
	int ans, a, b;
	Set se;
	Board board;
	se.in();
	board.Make(se);
	ans = board.cal();
	for (int i = 1; i <= 6; i++) for (int j = 1; j <= 6; j++) used[i][j] = false;
	for (int i = 1; i <= 13; i++) {
		if (get<0>(se.domino[i]) != 'S') {
			used[get<1>(se.domino[i])][get<2>(se.domino[i])] = true;
			used[get<2>(se.domino[i])][get<1>(se.domino[i])] = true;
		}
	}

	for (int i = 1; i <= 6; i++) for (int j = 1; j <= 6; j++) if (!used[i][j]) {
		for (int k = 1; k <= 13; k++) {
			if (get<0>(se.domino[k]) != 'S') {
				a = get<1>(se.domino[k]);
				b = get<2>(se.domino[k]);
				se.domino[k] = {get<0>(se.domino[k]), i, j};
				board.Make(se);
				ans = max(ans, board.cal());
				se.domino[k] = {get<0>(se.domino[k]), a, b};
			}
		}
	}
	//board.out();
	return ans;
}

int main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) cout << "Case " << i << ": " << solve() << "\n";
} 
