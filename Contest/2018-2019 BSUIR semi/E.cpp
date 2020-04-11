#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define F first
#define S second

int main() {
	string s;
	int n, zero = 0;
	char low = '0' + 10;
	cin >> s;
	n = int(s.size());
	for (char i : s) if (i == '0') zero++;
	if (n == 1) cout << "-1 -1" << endl;
	else if (zero == n) {
		if (n == 2) cout << "0 0" << endl;
		else cout << "-1 -1" << endl;
	}
	else if (n <= 19) {
		for (char i : s) low = min(low, i);
		for (char &i : s) if (i == low) {
			i = '0' + 10;
			break;	
		}
		sort(s.begin(), s.end());
		s.pop_back();
		if (s[0] == '0') {
			for (int i = 1; i < n; i++) if (s[i] != '0') {
				swap(s[i], s[0]);
				break;
			}
		}
		cout << low << " " << s << endl;
	}
	else {
		bool cant1e18 = true, cantnormal = false;
		pair<string, string> try1e18, normal;
		pair<ll, ll> ans;
		for (char i : s) if (i == '1') cant1e18 = false;
		if (zero < 18) cant1e18 = true;
		if (!cant1e18) {
			int cnt = 18;
			bool one = true;
			string tmp = s;
			try1e18.S = "1";
			for (int i = 0; i < 18; i++) try1e18.S += "0";
			for (char &i : tmp) if(i == '1' && one) {
				one = false;
				i = '0' + 10;
			}
			else if (i == '0' && cnt > 0) {
				cnt--;
				i = '0' + 10;
			}
		
			sort(tmp.begin(), tmp.end());
			while (tmp.back() == '0' + 10) tmp.pop_back();
			try1e18.F = tmp;
			if (try1e18.F.size() == 1) ;
			else if (try1e18.F.back() == '0') cant1e18 = true;
			else if (try1e18.F.size() <= 18) {
				if (try1e18.F[0] == '0') {
					for (char &i : try1e18.F) if (i != '0') {
						swap(i, try1e18.F[0]);
						break;
					}
				}
			}
			else if (try1e18.F.size() == 19) {
				if (try1e18.F[18] == '1' && try1e18.F[17] == '0') swap(try1e18.F[0], try1e18.F[18]);
				else cant1e18 = true;
			}
			else if (try1e18.F.size() > 19) cant1e18 = true;
		}
		sort(s.begin(), s.end());
		if (zero == n - 1) cantnormal = true;
		for (int i = n - 18; i < n; i++) normal.S += s[i];
		for (int i = 0; i < n - 18; i++) normal.F += s[i];

		if (normal.F.size() > 18) cantnormal = true;
		else if (normal.F.size() == 1) ;
		else if (normal.F.back() == '0') {
			bool first = true;
			for (char &i : normal.S) if (i != '0') {
				if (first) {
					first = false;
					swap(normal.F[0], i);
				}
				else {
					swap(normal.S[0], i);
					break;
				}
			}
		}
		else if (normal.F[0] == '0') {
			for (char &i : normal.F) if (i != '0') {
				swap(i, normal.F[0]);
				break;
			}
		}

		//cout << (cant1e18 ? "cant1e18" : "can1e18") << " " << (cantnormal ? "cantnormal" : "cannormal") << endl;
		//cout << try1e18.F << " " << try1e18.S << endl;
		//cout << normal.F << " " << normal.S << endl;
	

		if (cant1e18 && cantnormal) ans = make_pair(-1, -1);
		else if (cant1e18) ans = make_pair(stoll(normal.F), stoll(normal.S));
		else if (cantnormal) ans = make_pair(stoll(try1e18.F), stoll(try1e18.S));
		else ans = min(make_pair(stoll(try1e18.F), stoll(try1e18.S)), make_pair(stoll(normal.F), stoll(normal.S)));
		cout << ans.F << " " << ans.S << endl;
	}
}
