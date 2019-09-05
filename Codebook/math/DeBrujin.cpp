int a[15];
int cur[maxn];
string s;
string get_string(int len) {
	string res = "";
	for(int i = 0; i < len; i++) res += '0' + a[cur[i]];
	return res;
}
// n = length of key, k = number of different key, m = number of character
void dfs(int n, int k, int m, int now, int last) { 
	if(now && n % now == 0 && last == -1) 
		s += get_string(now);
	if(s.length() >= k + n - 1) return;
	if(now == n) return;

	if(now > 0) {
		cur[now] = cur[last + 1];
		dfs(n, k, m, now + 1, last + 1);
	}

	for(int i = now ? cur[last + 1] + 1 : 0; i < m; i++) {
		cur[now] = i;
		dfs(n, k, m, now + 1, -1);
	}
}
string Debrujin(int n, int k, int m) {
	dfs(n, k, m, 0, -1);
	while(s.length() < k + n - 1) s += s;
	return s.substr(0, k + n - 1);
}
