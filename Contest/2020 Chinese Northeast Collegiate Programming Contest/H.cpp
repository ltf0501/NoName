#include <bits/stdc++.h>
using namespace std;

string ToHex(int x) {
	string s;
	auto f = [](int c) {
		if (c < 10) return char('0' + c);
		return char('A' + (c - 10));
	};
	while (x) {
		s.push_back(f(x % 16));
		x /= 16;
	}
	reverse(s.begin(), s.end());
	return s;
}

int main() {
	cin.tie(nullptr), ios_base::sync_with_stdio(false);
	string s;
	while (cin >> s && !s.empty()) {
		vector<pair<char, string>> ans;
		{
			int i = 0;
			while (i < int(s.size())) {
				char cur = s[i];
				int cnt{};
				while (i < int(s.size()) && s[i] == cur) {
					++i;
					++cnt;
				}
				ans.emplace_back(cur, ToHex(cnt));
			}
		}
		//for (auto [ch, cnt] : ans) cerr << ch << cnt;
		//cerr << '\n';
		int onecnt = 0, del_one = 0, twocnt = 0, del_two = 0;
		for (int i = 1; i < int(ans.size()); i++) {
			if (ans[i - 1].second == "1") {
				++onecnt;
				if (!del_one && ans[i].first < ans[i - 1].first) {
					del_one = onecnt;
				}
			}
			if (ans[i - 1].second == "2") {
				++twocnt;
				del_two = twocnt;
			}
		}
		if (!del_one && ans.back().second == "1") {
			del_one = ++onecnt;
		}
		if (ans.back().second == "2") {
			del_two = ++twocnt;
		}
		if (onecnt && !del_one) del_one = onecnt;
		string anss;
		auto replace = [&](string &ss) {
			if (anss.empty()) anss = ss;
			else if (anss.size() > ss.size()) anss = ss;
			else if (anss.size() == ss.size() && anss > ss) anss = ss;
		};
		if (del_one) {
			string anss2;
			onecnt = 0;
			for (auto [ch, cnt] : ans) {
				if (cnt == "1" && ++onecnt == del_one) continue;
				anss2.push_back(ch);
				if (cnt != "1") anss2 += cnt;
			}
			replace(anss2);
		}
		if (del_two) {
			string anss2;
			twocnt = 0;
			for (auto [ch, cnt] : ans) {
				anss2.push_back(ch);
				if (cnt == "2" && ++twocnt == del_two) continue;
				anss2 += cnt;
			}
			replace(anss2);
		}
		{
			string anss2;
			int k = 0, del = 0;
			for (auto [ch, cnt] : ans) {
				auto origlen = cnt.size();
				auto newlen = ToHex(stoi(cnt, nullptr, 16) - 1).size();
				++k;
				if (newlen < origlen) {
					del = k;
				}
			}
			if (!del) del = 1;
			k = 0;
			for (auto [ch, cnt] : ans) {
				if (++k == del) {
					anss2.push_back(ch);
					string tmp = ToHex(stoi(cnt, nullptr, 16) - 1);
					if (tmp != "1") anss2 += tmp;
				} else {
					anss2.push_back(ch);
					if (cnt != "1") anss2 += cnt;
				}
			}
			if (anss.empty()) anss = anss2;
			else replace(anss2);
			//cerr << anss2 << '\n';
			//cerr << anss << '\n';
		}
		//cerr << anss << '\n';
		replace(s);
		string tmp;
		for (int i = 0; i < int(s.size()) - 1; i++) {
			if (i == int(tmp.size()) && s[i] > s[i + 1]) continue;
			tmp.push_back(s[i]);
		}
		tmp.push_back(s.back());
		if (tmp.size() == s.size()) tmp.pop_back();
		replace(tmp);
		cout << anss;
		cout << '\n';
	}
} 
