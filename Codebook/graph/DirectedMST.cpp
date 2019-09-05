template <typename T> struct DMST {
	bool vis[maxn], flag[maxn];
	int n;
	T w[maxn][maxn];
	int pre[maxn];
	void init(int n) { // 1-base
		this->n = n;
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= n; j++) w[i][j] = INF;
		memset(vis, 0, sizeof(vis));
		memset(flag, 0, sizeof(flag));
	}
	void AddEdge(int u, int v, T d) {
		w[u][v] = min(w[u][v], d);
	}
	T directed_mst(int u) {
		T ans = 0;
		memset(vis, 0, sizeof(vis));
		while(1) {
			for(int i = 1; i <= n; i++) if(i != u && !flag[i]) {
				w[i][i] = INF, pre[i] = i;
				for(int j = 1; j <= n; j++) 
					if(!flag[j] && w[j][i] < w[pre[i]][i]) pre[i] = j;
				if(pre[i] == i) return -1;
			}
			
			int i;
			for(i = 1; i <= n; i++) if(i != u && !flag[i]) {
				int j = i, cnt = 0;
				while(j != u && pre[j] != i && cnt <= n) j = pre[j], cnt++;
				if(j == u || cnt > n) continue;
				break;
			}

			if(i > n) {
				for(int i = 1; i <= n; i++) 
					if(i != u && !flag[i]) ans += w[pre[i]][i];
				return ans;
			} 

			int now = i;
			memset(vis, 0, sizeof(vis));
			do {
				ans += w[pre[now]][now], now = pre[now], vis[now] = flag[now] = 1;
			} while(now != i);
			flag[i] = 0;

			for(int k = 1; k <= n; k++) if(vis[k]) {
				for(int j = 1; j <= n; j++) if(!vis[j]) {
					if(w[i][j] > w[k][j]) w[i][j] = w[k][j];
					if(w[j][k] < INF && w[j][k] - w[pre[k]][k] < w[j][i])
						w[j][i] = w[j][k] - w[pre[k]][k];
				}
			}
		}
		return ans;
	}
};
