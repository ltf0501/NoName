#include <bits/stdc++.h>
using namespace std;

enum Kind { kUnsorted, kSorted, kShuffle };

using Result = deque<pair<Kind, deque<int>>>;

deque<int> &MergeDeque(deque<int> &q1, deque<int> &q2) {
	if (q1.size() > q2.size()) {
		for (auto x : q2) q1.push_back(x);
		return q1;
	}
	reverse(q1.begin(), q1.end());
	for (auto x : q1) q2.push_front(x);
	return q2;
}

Result &MergeResult(Result &q1, Result &q2) {
	if (q1.size() > q2.size()) {
		for (auto x : q2) q1.push_back(x);
		return q1;
	}
	reverse(q1.begin(), q1.end());
	for (auto x : q1) q2.push_front(x);
	return q2;
}

pair<int, Result> Parse(const string &str, int p = 0) {
	if (str[p] == '[') {
		p += 1;
		deque<int> vec;
		while (str[p] != ']') {
			int x = 0;
			while (str[p] != ',' && str[p] != ']') {
				//cerr << "R:" << str[p] << '\n';
				x = x * 10 + (str[p] - '0');
				++p;
			}
			vec.push_back(x);
			if (str[p++] == ']') break;
		}
		Result ret;
		ret.emplace_back(kUnsorted, move(vec));
		return make_pair(p, move(ret));
	} else if (str[p] == 'c') {
		p += 7;
		auto res1 = Parse(str, p);
		p = res1.first + 1;
		auto res2 = Parse(str, p);
		p = res2.first + 1;
		return {p, move(MergeResult(res1.second, res2.second))};
	} else if (str[p] == 's') {
		bool is_shuffle = str[p + 1] == 'h';
		p += is_shuffle ? 8 : 7;
		auto res = Parse(str, p);
		p = res.first + 1;
		deque<int> q1 = move(res.second.front().second);
		res.second.pop_front();
		for (auto &q2 : res.second) {
			q1.swap(MergeDeque(q1, q2.second));
		}
		Result ret;
		ret.emplace_back(is_shuffle ? kShuffle : kSorted, move(q1));
		return {p, move(ret)};
	}
	assert(0);
}

Result Normalize(Result res) {
	Result ret;
	ret.push_back(move(res.front()));
	res.pop_front();
	auto Norm = [](auto &qq) {
		auto same = [](auto l, auto r) {
			auto s = l;
			for (auto p = l; p != r; p++) {
				if (*p != *s) return false;
			}
			return true;
		};
		if (qq.first == kShuffle && same(qq.second.begin(), qq.second.end())) {
			qq.first = kUnsorted;
		}
		if (qq.first == kSorted) {
			sort(qq.second.begin(), qq.second.end());
			qq.first = kUnsorted;
		}
	};
	Norm(ret.back());
	for (auto &qq : res) {
		Norm(qq);
		if (ret.back().first != qq.first || ret.back().first == kShuffle) {
			ret.push_back(move(qq));
		} else {
			ret.back().second.swap(MergeDeque(ret.back().second, qq.second));
		}
	}
	for (auto &qq : ret) {
		if (qq.first == kShuffle) {
			sort(qq.second.begin(), qq.second.end());
		} else {
			qq.first = kUnsorted;
		}
		//cerr << qq.first << ": ";
		//for (auto x : qq.second) cerr << x << ' ';
		//cerr << "\n";
	}
	//cerr << "---\n";
	return ret;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	string s1, s2; cin >> s1 >> s2;
	auto r1 = Normalize(Parse(s1).second);
	auto r2 = Normalize(Parse(s2).second);
	cout << (r1 == r2 ? "equal\n" : "not equal\n");
} 
