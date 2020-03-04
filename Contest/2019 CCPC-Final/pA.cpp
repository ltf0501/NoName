#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
 
#define F first
#define S second
#define PB push_back
 
map<string, int> ma;
 
struct Date {
	string a, b;
	int month, day;
	void in() {
		cin >> a >> b;
		month = ma[a];
		day = b[0] - '0';
		if ('0' <= b[1] && b[1] <= '9') {
			day *= 10;
			day += b[1] - '0';
		}
		return ;
	}
	void out() {
		cout << a << " " << b << endl;
		return ;
	}
};
 
 
bool cmp(Date a, Date b) {
	if (a.month == b.month) return a.day < b.day;
	else return a.month < b.month;
}
Date date[300];
 
void pre() {
	ma["Jan"] = 1;
	ma["Feb"] = 2;
	ma["Mar"] = 3;
	ma["Apr"] = 4;
	ma["May"] = 5;
	ma["Jun"] = 6;
	ma["Jul"] = 7;
	ma["Aug"] = 8;
	ma["Sept"] = 9;
	ma["Oct"] = 10;
	ma["Nov"] = 11;
	ma["Dec"] = 12;
	return ;
}
void solve() {
	string a, b;
	Date target;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) date[i].in();
	target.in();
	sort(date + 1, date + n + 1, cmp);
	for (int i = 1; i <= n; i++) if (cmp(target, date[i])) {
		date[i].out();
		return ;
	}
	cout << "See you next year" << endl;
	return ;
}
 
int main() {
	int t;
	pre();
	cin >> t;
	for (int i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
