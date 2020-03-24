#include <iostream>
#include <algorithm>
using namespace std;

string s[10];
bool have[6][6];
int p[6];

void solve() {	
	bool f;
	for (int i = 0; i < 6; i++) cin >> s[i];
	for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++) have[i][j] = false;
	for (int i = 0; i < 6; i++) for (char j : s[i]) {
		if (j == 'h') have[i][0] = true;
		if (j == 'a') have[i][1] = true;
		if (j == 'r') have[i][2] = true;
		if (j == 'b') have[i][3] = true;
		if (j == 'i') have[i][4] = true;
		if (j == 'n') have[i][5] = true;
	}
	for (int i = 0; i < 6; i++) p[i] = i;
	for (int i = 0; i < 720; i++) {
		next_permutation(p, p + 6);
		f = true;
		for (int j = 0; j < 6; j++) if (!have[j][p[j]]) {
			f = false;
			break;
		}
		if (f) {
			cout << "Yes" << endl;
			return ;
		}
	}
	cout << "No" << endl;
	return ;
}

int main() {
	int t;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while (t--) solve();
} 
