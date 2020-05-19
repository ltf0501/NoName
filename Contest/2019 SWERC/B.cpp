#include <iostream>
#include <unordered_map>
using namespace std;
int main() {
	int n;
	unordered_map<string, int> m;
	string s;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		m[s]++;
	}
	for (pair<string, int> i : m) {
		if (i.second > n / 2) {
			cout << i.first << '\n';
			return 0;
		}
	}
	cout << "NONE\n";
} 
