bool debug=false;
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=2e5+10;
const long long int INF=1e16+10;
struct edge{
	int to,rev;
	long long int cap;
};
int dep[N],iter[N],went[N];
vector<edge> graph[N];
long long int min(long long int a,long long int b){return a>b?b:a;}
void addedge(int u,int v,long long int cap){
	graph[u].PB({v,(int)graph[v].size(),cap});
	graph[v].PB({u,(int)graph[u].size()-1,0});
	return ;
}
void bfs(int s,int t){
	int now;
	queue<int> q;
	dep[s]=iter[s]=0;
	went[s]=t;
	q.push(s);
	while(!q.empty()){
		now=q.front();
		q.pop();
		for(edge i:graph[now])if(i.cap>0&&went[i.to]!=t){
			went[i.to]=t;
			q.push(i.to);
			dep[i.to]=dep[now]+1;
			iter[i.to]=0;
		}
	}
	return ;
}
long long int dfs(int u,int t,long long int nv){
	if(u==t)return nv;
	long long int temp;
	for(int &i=iter[u];i<graph[u].size();i++){
		edge& nxt=graph[u][i];
		if(nxt.cap>0&&dep[nxt.to]>dep[u]){
			temp=dfs(nxt.to,t,min(nv,nxt.cap));
			if(temp>0){
				nxt.cap-=temp;
				graph[nxt.to][nxt.rev].cap+=temp;
				return temp;
			}
		}
	}
	return 0;
}
long long int dinic(int s,int t){
	long long int ans = 0,f;
	int cnt=0;
	for(int i=0;i<N;i++)went[i]=0;
	while(true){
		bfs(s,++cnt);
		if(went[s]!=went[t])break;
		while((f=dfs(s,t,INF))>0)ans+=f;
	}
	return ans;
}
int main(){
	cin.tie(nullptr); ios_base::sync_with_stdio(false);
	freopen("hentium.in", "r", stdin);
	freopen("hentium.out", "w", stdout);
	int n;
	while (cin >> n && n) {
		for (int i = 0; i <= n + n + 1; i++) graph[i].clear();
		for (int i = 1; i <= n; i++) {
			int64_t a, b; cin >> a >> b;
			addedge(0, i, b<<1);
			addedge(n + i, n + n + 1, a<<1);
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int64_t c; cin >> c;
				if (i == j) c = INF;
				addedge(i, n + j, c);
				addedge(n+i,j,c);
			}
		}
		cout << dinic(0, n + n + 1)/2 << '\n';
		if(debug){
			for(int i=0;i<=n+n+1;i++){
				printf("%d\n",i);
				for(edge j:graph[i])printf("%d %lld\n",j.to,j.cap);
			}
		}
		bfs(0, -1);
		for (int i = 1; i <= n; i++) {
			cout << (went[i] == -1 ? 1 : 2) << ' ';
		}
		cout << '\n';
	}
}
