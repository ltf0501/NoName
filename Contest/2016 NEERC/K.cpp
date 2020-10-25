#include <iostream>
#include <string.h>
using namespace std;

constexpr int kN = int(2E3 + 10);

struct Board {
	int h, w, th, tw;
	bool board[kN][kN], emp;
	Board() {memset(board, false, sizeof(board));}
	void in() {
		cin >> h >> w;
		string s;
		for (int i = 0; i < h; i++) {
			cin >> s;
			for (int j = 0; j < w; j++) board[i][j] = (s[j] == '*');
		}
		return ;
	}
	void out() {
		for (int i = 0; i < h; i++, cout << '\n') for (int j = 0; j < w; j++) cout << (board[i][j] ? 1 : 0);
		return ;
	}
	void pull() {
		emp = true;
		for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) if (board[i][j]) {
			if (emp) {
				th = i, tw = j;
				emp = false;
			}
		}
		return ;
	}
};

Board b1, b2, b3;
int x, y;

Board Match(Board a, Board b) {
	if (a.emp) return b;
	if (b.emp) return a;
	int ax, ay, bx, by;
	x = a.th - b.th, y = a.tw - b.tw;
	Board ans;
	if (x > 0) {
		ans.h = max(x + b.h, a.h);
		ax = 0;
		bx = x;
	}
	else {
		ans.h = max(-x + a.h, b.h);
		ax = -x;
		bx = 0;
	}

	if (y > 0) {
		ans.w = max(y + b.w, a.w);
		ay = 0;
		by = y;
	}
	else {
		ans.w = max(-y + a.w, b.w);
		ay = -y;
		by = 0;
	}
	for (int i = 0; i < a.h; i++) for (int j = 0; j < a.w; j++) 
		ans.board[i + ax][j + ay] ^= a.board[i][j];
	for (int i = 0; i < b.h; i++) for (int j = 0; j < b.w; j++) 
		ans.board[i + bx][j + by] ^= b.board[i][j];
	ans.pull();
	return ans;
}

bool Equal(Board a, Board b) {
	return Match(a, b).emp;
}

int main() {
freopen("kids.in", "r", stdin);	
freopen("kids.out", "w", stdout);	
	b1.in();
	b2.in();
	b3.in();
	b1.pull(), b2.pull(), b3.pull();
	if (Equal(Match(b1, b2), b3)) {
		cout << "YES" << '\n' << b1.tw - b2.tw << " " << b1.th - b2.th << '\n';
	}
	else if (Equal(Match(b1, b3), b2)) {
		cout << "YES" << '\n' << y - (b3.tw - b1.tw > 0 ? b3.tw - b1.tw : 0) 
									 << " " << x - (b3.th - b1.th > 0 ? b3.th - b1.th : 0) << '\n';
	}
	else if (Equal(b1, Match(b2, b3))) {
		cout << "YES" << '\n' << y + (b3.tw - b2.tw > 0 ? b3.tw - b2.tw : 0) 
									 << " " << x + (b3.th - b2.th > 0 ? b3.th - b2.th : 0) << '\n';
	}
	else cout << "NO\n";
} 
