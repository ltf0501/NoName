#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
/*
 * ..----..----..----..----..----..
 * ..    ..    ..    ..    ..    ..
 * | \                          / |
 * |  \                        /  |
 * |   \                      /   |
 * |     ..                ..     |
 * ..    ..                ..    ..
 * ..      \              /      ..
 * |        \            /        |
 * |         \          /         |
 * |          ..      ..          |
 * |          ..      ..          |
 * ..           \    /           ..
 * ..            \  /            ..
 * |              \/              |
 * |              ..              |
 * |              ..              |
 * |             /  \             |
 * ..           /    \           ..
 * ..          /      \          ..
 * |         ..        ..         |
 * |         ..        ..         |
 * |        /            \        |
 * |       /              \       |
 * ..     /                \     ..
 * ..   ..                  ..   ..
 * |    ..                  ..    |
 * |   /                      \   |
 * |  /                        \  |
 * | /                          \ |
 * ..    ..    ..    ..    ..    ..
 * ..----..----..----..----..----..
 *
 * ..----..----..----..----..----..
 * 11    10    .9    .8    .7    .6
 * | \                          / |
 * |  \                        /  |
 * |   \                      /   |
 * |     ..                ..     |
 * ..    26                21    ..
 * 12      \              /      .5
 * |        \            /        |
 * |         \          /         |
 * |          ..      ..          |
 * |          27      22          |
 * ..           \    /           ..
 * 13            \  /            .4
 * |              \/              |
 * |              ..              |
 * |              23              |
 * |             /  \             |
 * ..           /    \           ..
 * 14          /      \          .3
 * |         ..        ..         |
 * |         24        28         |
 * |        /            \        |
 * |       /              \       |
 * ..     /                \     ..
 * 15   ..                  ..   .2
 * |    25                  29    |
 * |   /                      \   |
 * |  /                        \  |
 * | /                          \ |
 * ..    ..    ..    ..    ..    ..
 * 16----17----18----19----20----.1
 */

//ABCDabcd
//12345678

int ToInt[256];
char ToToken[10];

int Team(int x) {
	return (x - 1) >> 2;
}

bool SameTeam(int a, int b) {
	return Team(a) == Team(b);
}

struct Board {
	struct Station {
		vector<int> here;
		Station() {here.clear();}
		void Start(vector<int> &v) {
			if (!here.empty()) {
				if (SameTeam(here[0], v[0])) {
					for (int i : here) v.PB(i);
					here.clear();
				}
			}
			else return ;
		}
		void arrive(vector<int> v) {
			if (!here.empty() && !SameTeam(here[0], v[0])) here.clear();	
			for (int i : v) here.PB(i);
			return ;
		}
		void clear() {here.clear();}
		void pull() {
			sort(here.begin(), here.end());
			here.resize(unique(here.begin(), here.end()) - here.begin());
			return ;
		}
	};
	int position[9], xposition[30], yposition[30];
	Station station[30];
	pair<int, int> nxt[30];
	Board() {
		for (int i = 1; i <= 8; i++) position[i] = 0;
		for (int i = 1; i <= 29; i++) station[i].clear();
		nxt[ 0] = { 1,  1}; xposition[ 0] =  0; yposition[ 0] =  0; 
		nxt[ 1] = { 2,  2}; xposition[ 1] = 30; yposition[ 1] = 30; 
		nxt[ 2] = { 3,  3}; xposition[ 2] = 24; yposition[ 2] = 30; 
		nxt[ 3] = { 4,  4}; xposition[ 3] = 18; yposition[ 3] = 30; 
		nxt[ 4] = { 5,  5}; xposition[ 4] = 12; yposition[ 4] = 30; 
		nxt[ 5] = { 6,  6}; xposition[ 5] =  6; yposition[ 5] = 30; 
		nxt[ 6] = {21,  7}; xposition[ 6] =  0; yposition[ 6] = 30; 
		nxt[ 7] = { 8,  8}; xposition[ 7] =  0; yposition[ 7] = 24; 
		nxt[ 8] = { 9,  9}; xposition[ 8] =  0; yposition[ 8] = 18; 
		nxt[ 9] = {10, 10}; xposition[ 9] =  0; yposition[ 9] = 12; 
		nxt[10] = {11, 11}; xposition[10] =  0; yposition[10] =  6; 
		nxt[11] = {26, 12}; xposition[11] =  0; yposition[11] =  0; 
		nxt[12] = {13, 13}; xposition[12] =  6; yposition[12] =  0; 
		nxt[13] = {14, 14}; xposition[13] = 12; yposition[13] =  0; 
		nxt[14] = {15, 15}; xposition[14] = 18; yposition[14] =  0; 
		nxt[15] = {16, 16}; xposition[15] = 24; yposition[15] =  0; 
		nxt[16] = {17, 17}; xposition[16] = 30; yposition[16] =  0; 
		nxt[17] = {18, 18}; xposition[17] = 30; yposition[17] =  6; 
		nxt[18] = {19, 19}; xposition[18] = 30; yposition[18] = 12; 
		nxt[19] = {20, 20}; xposition[19] = 30; yposition[19] = 18; 
		nxt[20] = { 1,  1}; xposition[20] = 30; yposition[20] = 24; 
		nxt[21] = {22, 22}; xposition[21] =  5; yposition[21] = 25; 
		nxt[22] = {23, 23}; xposition[22] = 10; yposition[22] = 20; 
		nxt[23] = {28, 24}; xposition[23] = 15; yposition[23] = 15; 
		nxt[24] = {25, 25}; xposition[24] = 20; yposition[24] = 10; 
		nxt[25] = {16, 16}; xposition[25] = 25; yposition[25] =  5; 
		nxt[26] = {27, 27}; xposition[26] =  5; yposition[26] =  5; 
		nxt[27] = {23, 23}; xposition[27] = 10; yposition[27] = 10; 
		nxt[28] = {29, 29}; xposition[28] = 20; yposition[28] = 20; 
		nxt[29] = { 1,  1}; xposition[29] = 25; yposition[29] = 25;
	}
	void pull() {
		for (int i = 1; i <= 8; i++) position[i] = 0;
		for (int i = 1; i <= 29; i++) station[i].pull();
		for (int i = 1; i <= 29; i++) for (int j : station[i].here) position[j] = i;
		//for (int i = 1; i <= 8; i++) printf("position[%d] = %d\n", i, position[i]);
		return ;
	}
	void Move(int Token, int Steps) {
		//cout << "Move " << ToToken[Token] << " " << Steps << '\n';
		pull();
		int now = position[Token], lst;
		vector<int> v = {Token};
		//cout << now << '\n';
		if (now == 0) station[Steps + 1].arrive(v);
		else {
			station[now].Start(v);
			if (now == 1) {
				v.clear();
				pull();
				return ;
			}
			lst = now;
			now = nxt[now].F;
			for (int i = 1; i < Steps; i++) {
				if (now == 1) {
					v.clear();
					pull();
					return ;
				}
				else if (lst == 27 && now == 23) lst = 23, now = 28;
				else {
					lst = now;
					now = nxt[now].S;
				}
			}
			station[now].arrive(v);
		}
		pull();
	}
	void out() {
		string s[32];
		int x[4] = {0, 0, 1, 1}, y[4] = {0, 1, 0, 1};
		s[ 0] = "..----..----..----..----..----.."; 
		s[ 1] = "..    ..    ..    ..    ..    ..";
		s[ 2] = "| \\                          / |";
		s[ 3] = "|  \\                        /  |";
		s[ 4] = "|   \\                      /   |";
		s[ 5] = "|    ..                  ..    |";
		s[ 6] = "..   ..                  ..   ..";
		s[ 7] = "..     \\                /     ..";
		s[ 8] = "|       \\              /       |";
		s[ 9] = "|        \\            /        |";
		s[10] = "|         ..        ..         |";
		s[11] = "|         ..        ..         |";
		s[12] = "..          \\      /          ..";
		s[13] = "..           \\    /           ..";
		s[14] = "|             \\  /             |";
		s[15] = "|              ..              |";
		s[16] = "|              ..              |";
		s[17] = "|             /  \\             |";
		s[18] = "..           /    \\           ..";
		s[19] = "..          /      \\          ..";
		s[20] = "|         ..        ..         |";
		s[21] = "|         ..        ..         |";
		s[22] = "|        /            \\        |";
		s[23] = "|       /              \\       |";
		s[24] = "..     /                \\     ..";
		s[25] = "..   ..                  ..   ..";
		s[26] = "|    ..                  ..    |";
		s[27] = "|   /                      \\   |";
		s[28] = "|  /                        \\  |";
		s[29] = "| /                          \\ |";
		s[30] = "..    ..    ..    ..    ..    ..";
		s[31] = "..----..----..----..----..----..";

		for (int i = 1; i <= 29; i++) {
			for (int j : station[i].here) {
				int posx = xposition[i] + x[(j - 1) & 3], posy = yposition[i] + y[(j - 1) & 3];
				s[posx][posy] = ToToken[j];
			}
		}

		for (int i = 0; i < 32; i++) cout << s[i] << '\n';
		return ;
	}
};

int ToStep(string s) {
	int b = 0, f = 0;
	for (char i : s) if (i == 'B') b++;
	else f++;
	return (f + 4) % 5 + 1;
}

void init() {
	ToInt['A'] = 1; ToToken[1] = 'A';
	ToInt['B'] = 2; ToToken[2] = 'B';
	ToInt['C'] = 3; ToToken[3] = 'C';
	ToInt['D'] = 4; ToToken[4] = 'D';
	ToInt['a'] = 5; ToToken[5] = 'a';
	ToInt['b'] = 6; ToToken[6] = 'b';
	ToInt['c'] = 7; ToToken[7] = 'c';
	ToInt['d'] = 8; ToToken[8] = 'd';
	return ;
}

int main() {
	string s, c;
	int n;
	Board board;
	init();
	cin >> n;
	while (n--) {
		cin >> c >> s;
		board.Move(ToInt[c[0]], ToStep(s));
		//board.out();
	}
	board.out();
} 
