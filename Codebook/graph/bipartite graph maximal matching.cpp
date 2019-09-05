int match[maxn];
bool vis[maxn];
bool dfs(int u) {
    vis[u] = 1;
    for(int v : g[u]) if(!vis[match[v]]) {
        if(!match[v] || dfs(match[v])) {
            if(!match[v]) cnt++;
            match[v] = u;
            return 1;
        }
    }
    return 0;
}
int cal() {
	memset(match,0,sizeof(match));
	int	res = 0;
	for(int i = 1; i <= n; i++) {
		dfs(i);
		memset(vis, 0, sizeof(vis));
	}
	return res;
}
//(u,v) -> g[u].push_back(v)
