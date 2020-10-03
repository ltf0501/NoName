#include <iostream>
using namespace std;

constexpr int kN = int(5E3 + 10);

bool can[kN][kN], have[kN][kN];

int main() {
	int ssz, tsz;
	string s, t;
	cin >> s >> t;
	ssz = int(s.size());
	tsz = int(t.size());
	if (s[0] != t[0]) cout << "No\n";
	else {
		can[0][0] = true;
		for (int i = 0; i < ssz; i++) {
			for (int j = 1; j < tsz; j++) {
				if (i > 0 && can[i - 1][j - 1] && s[i] == t[j]) can[i][j] = true;
				if (can[i][j - 1] && t[j - 1] != t[j]) {
					for (int k = j; k < tsz; k++) can[i][k] = true;
					break;
				}
			}
		}
		if (can[ssz - 1][tsz - 1]) cout << "Yes\n";
		else cout << "No\n";
	}
} 
