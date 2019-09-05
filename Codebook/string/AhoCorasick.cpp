struct AC {
	int ch[maxn][26], fail[maxn], cnt[maxn], end[maxn];
	int num, root;
	int newnode() {
		for(int i = 0; i < 26; i++) ch[num][i] = 0;
		fail[num] = 0;
		end[num] = 0;
		cnt[num] = 0;
		return num++;
	}
	void init() {
		num = 0;
		root = newnode();
	}
	void insert(string s, int id) {
		int len = s.length();
		int cur = root;
		for(int i = 0; i < len; i++) {
			if(ch[cur][s[i] - 'a'] == 0) ch[cur][s[i] - 'a'] = newnode();
			cur = ch[cur][s[i] - 'a'];
		}
		cnt[cur]++;
		end[cur] = id;
	}
	void build_fail() {
		queue<int> q;
		for(int i = 0; i < 26; i++) {
			if(ch[0][i]) q.push(ch[0][i]), fail[ch[0][i]] = 0;
		}
		while(!q.empty()) {
			int x = q.front(); q.pop();
			for(int i = 0; i < 26; i++) {
				if(ch[x][i]) {
					fail[ch[x][i]] = ch[fail[x]][i];
					cnt[ch[x][i]] += cnt[fail[ch[x][i]]];
					q.push(ch[x][i]);
				} 
				else ch[x][i] = ch[fail[x]][i];
			}
		}
	}
	void cal(string t, int *a) {// calculate the number of appearance of every pattern strings
		int n = t.length();
		int cur = root;
		for(int i = 0; i < n; i++) {
			while(cur != root && !ch[cur][t[i] - 'a']) cur = fail[cur];
			cur = ch[cur][t[i] - 'a'];
			int now = cur;
			while(now != root) {
				if(end[now]) a[end[now]]++;
				now = fail[now];
			}
		}
	}
}; 
/*
 cur = root;
 for(int i = 0; i < t.length(); i++) {
	cur = ch[cur][t[i] - 'a'];
	pre[i] = cnt[cur];
 }
 */
