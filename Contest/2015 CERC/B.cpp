#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	string s;
	getline(cin, s);
	int a, b; cin >> a >> b;
	int n = int(s.size());
	s.push_back(' ');
	//cerr << s << '\n';
	vector<int> jmp(n + 1), len(n + 1);
	{
		int last = -1;
		for (int i = 0; i < n; i++) {
			if (s[i + 1] == ' ') {
				jmp[i] = last = i;
			} else {
				jmp[i] = last;
			}
		}
	}
	{
		int last = -1;
		for (int i = 0; i <= n; i++) {
			if (s[i] == ' ') {
				for (int j = last + 1; j <= i; j++) {
					len[j] = i - last - 1;
				}
				last = i;
			}
		}
	}
	for (int k = a; k <= b; k++) {
		int p = 0, ans = -1;
		while (p < n) {
			ans += len[p] + 1;
			int p1 = p + k - 1;
			if (p1 >= n) break;
			p1 = jmp[p1] + 2;
			p = p1;
			//cerr << "p: " << p << '\n';
		}
		cout << ans << '\n';
	}
} 
