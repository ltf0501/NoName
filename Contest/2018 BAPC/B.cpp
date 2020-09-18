#include <iostream>
using namespace std;

int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int idx[20][40], val[400], M[400], D[400];
bool have[400];

int date(string s) {
	int m = (s[0] - '0') * 10 + (s[1] - '0'), d = (s[3] - '0') * 10 + (s[4] - '0');
	return idx[m][d];
}

int main() {
	int n, now = 0, x, pos = 2, st = 0;
	string s, t;
	cin >> n;
	for (int i = 1; i <= 12; i++) for (int j = 1; j <= month[i]; j++) idx[i][j] = ++now;
	x = idx[10][27];
	for (int i = 1; i <= 12; i++) for (int j = 1; j <= month[i]; j++) {
		idx[i][j] = idx[i][j] - x + 1;
		if (idx[i][j] <= 0) idx[i][j] += now;
	}
	for (int i = 1; i <= n; i++) {
		cin >> s >> t;
		have[st = date(t)] = true;
	}
	
	for (int i = 1; i <= 12; i++) for (int j = 1; j <= month[i]; j++) {
		M[idx[i][j]] = i;
		D[idx[i][j]] = j;
	}
	for (int i = 1; i <= now; i++) {
		if (have[(i + st - 1 + now) % now + 1]) val[(i + st - 1 + now) % now + 1] = 0;
		else val[(i + st - 1 + now) % now + 1] = val[(i + st - 2 + now) % now + 1] + 1;
	}

	
	for (int i = 2; i <= now; i++) if (val[pos] < val[i]) pos = i;
	if (val[pos] < val[1]) pos = 1;

	cout << M[pos] / 10 << M[pos] % 10 << '-' << D[pos] / 10 << D[pos] % 10 << '\n';
} 
