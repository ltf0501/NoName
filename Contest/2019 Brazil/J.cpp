#include <iostream>
using namespace std;

struct Hand {
	int hand[14];
	bool receive;
	Hand() {
		for (int i = 0; i < 14; i++) hand[i] = 0;
		receive = false;
	}
	void in() {
		string s;
		cin >> s;
		for (int i = 0; i < 14; i++) hand[i] = 0;
		receive = false;
		for (int i = 0; i < 4; i++) {
			if (s[i] == 'A') hand[1]++;
			else if (s[i] == 'D') hand[10]++;
			else if (s[i] == 'Q') hand[11]++;
			else if (s[i] == 'J') hand[12]++;
			else if (s[i] == 'K') hand[13]++;
			else hand[s[i] - '0']++;
		}
		return ;
	}
	void get(int x) {
		hand[x]++;
		if (x == 0) receive = true;	
		return ;
	}
	int give() {
		if (!receive && hand[0]) {
			hand[0]--;
			return 0;
		}
		else {
			receive = false;
			int idx = 1;
			for (int i = 1; i <= 13; i++) {
				if (hand[idx] == 0) idx = i;
				else if (hand[idx] > hand[i] && hand[i] != 0) idx = i;
			}
			hand[idx]--;
			return idx;
		}
	}
	bool win() {
		for (int i = 1; i <= 13; i++) if (hand[i] == 4) return true;
		return false;
	}
};

Hand hand[14];

int main() {
	int n, k, nxt, tmp;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) hand[i].in();
	hand[k].get(0);
	for (int i = 1; i <= n; i++) if (i != k) if (hand[i].win()) {
		printf("%d\n", i);
		return 0;
	}
	while (true) {
		nxt = k % n + 1;
		tmp = hand[k].give();
		//printf("%d give %d card %d\n", k, nxt, tmp);
		hand[nxt].get(tmp);
		if (hand[k].win()) break;
		k = nxt;
	}
	printf("%d\n", k);
} 
