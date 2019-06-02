#include <bits/stdc++.h>
using namespace std;

string str[1001];

void dfs(int l, int r, int d) {
	int prev = l;
	for (int i = l + 1; i <= r; i++) {
		if (str[i][d] != str[prev][d] || (str[prev][d] != '#' && str[prev][d] != '*')) {
			if (d) cout << "<li>\n";
			if (i - 1 == prev) {
				for (int j = d; str[prev][j]; j++) cout << str[prev][j];
				cout << '\n';
			} else {
				cout << (str[prev][d] == '*' ? "<ul>\n" : "<ol>\n");
				dfs(prev, i - 1, d + 1);
				cout << (str[prev][d] == '*' ? "</ul>\n" : "</ol>\n");
			}
			prev = i;
			if (d) cout << "</li>\n";
		}
	}
	if (d) cout << "<li>\n";
	if (r == prev) {
		for (int j = d; str[prev][j]; j++) cout << str[prev][j];
		cout << '\n';
	} else {
		cout << (str[prev][d] == '*' ? "<ul>\n" : "<ol>\n");
		dfs(prev, r, d + 1);
		cout << (str[prev][d] == '*' ? "</ul>\n" : "</ol>\n");
	}
	if (d) cout << "</li>\n";
}

int main() {
			        freopen("input.txt","r",stdin);
				freopen("output.txt","w",stdout);
	int cnt = 0;
	while (cin >> str[cnt]) {
		str[cnt].resize(1010);
	       	cnt++;
	}
	dfs(0, cnt - 1, 0);
}
