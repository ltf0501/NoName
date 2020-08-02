#include <bits/stdc++.h>
using namespace std;
const int kN = 2e5 + 10;

int n;
int a[kN];
bool ok[kN];
queue<int> q[kN];
int deg[kN];

void Add(int x);

void Del(int x) {
	if(!ok[x]) return;
	ok[x] = 0;
	if(--deg[a[x]] == 0) Add(a[x]);
}

void Add(int x) {
	if(ok[x]) return;
	ok[x] = 1;

	while(!q[x].empty()) {
		Del(q[x].front());
		q[x].pop();
	}

	q[a[x]].push(x);
	deg[a[x]]++;
	Del(a[x]);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= 2 * n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= 2 * n; i++)
		if(!deg[i]) Add(i);

	for(int i = 1; i <= 2 * n; i++)
		if(ok[i]) printf("%d ", i);
	puts("");
	return 0;
} 
