#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 1E5;
int a[MAXN], b[MAXN], p[MAXN], r[MAXN], par[MAXN];

int find(int x) {
	return par[x] == x ? x : par[x] = find(par[x]);
}

void join(int aa, int bb) {
	int pa = find(aa), pb = find(bb);
	if (pa != pb) par[pa] = pb;
}

vector<int> vv;
int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n; cin >> n;
	vector<pair<int, int> > vvv;
	vector<tuple<int, int, int> > v;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i] >> r[i] >> p[i];
		vv.push_back(a[i]),vv.push_back(b[i]);
		v.push_back({ -r[i], -p[i], i });
		vvv.push_back({ p[i], i });
	}
	sort(vv.begin(),vv.end());
	sort(vvv.begin(), vvv.end());
	vv.resize(unique(vv.begin(),vv.end())-vv.begin());
	for(int i=0;i<n;i++)
	{
		a[i]=lower_bound(vv.begin(),vv.end(),a[i])-vv.begin()+1;
		b[i]=lower_bound(vv.begin(),vv.end(),b[i])-vv.begin()+1;

	}
	iota(par, par + 2*n + 1, 0);
	sort(v.begin(), v.end());
	int64_t cost = 0;
	for (int i = 0; i < n; i++) {
		int idx = get<2>(v[i]);
		
		if (find(a[idx]) != find(b[idx])) {
			// cout<<"a="<<a[idx]<<" b="<<b[idx]<<endl;
			join(a[idx], b[idx]);
			cost += p[idx];
		}
	}
	cout << cost << '\n';
	for (int i = n - 1; i >= 0; i--) cout << get<2>(v[i]) + 1 << ' ';
}
