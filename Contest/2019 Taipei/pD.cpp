#include <bits/stdc++.h>
using namespace std;

int main() {
	vector<string> v;
	string str;
	while (cin >> str) {
		if (str != "bubble" && str != "tapioka") {
			v.push_back(str);
		}
	}
	if (v.empty()) v.push_back("nothing");
	bool first = true;
	for (auto s : v) {
		if (!first) cout << ' ';
		first = false;
		cout << s;
	}
}
