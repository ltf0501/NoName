#include <bits/stdc++.h>
using namespace std;


int main() {
	int n;
	while(~scanf("%d", &n) && n) {
		char c;
		int h[2], m[2], s[2];
		auto GetTime = [&](int H, int M, int S) {
			return H * 3600 + M * 60 + S;
		};
		int ans = 0;
		for(int i = 0; i < n; i++) {
			scanf(" %c:%d:%d:%d:%d:%d:%d", &c, &h[0], &m[0], &s[0], &h[1], &m[1], &s[1]);
			int t[2];
			for(int j = 0; j < 2; j++) t[j] = GetTime(h[j], m[j], s[j]);
			assert(t[0] <= t[1]);
			if(t[0] < GetTime(8, 30, 0)) t[0] = GetTime(8, 30, 0);
			if(c == 'D' && t[0] > GetTime(9, 30, 0)) ans++;
			else if(c == 'E' && t[0] > GetTime(12, 30, 0)) ans++;
			else if(c == 'D' && t[1] - t[0] < GetTime(8, 0, 0)) ans++;
			else if(c == 'E' && t[1] - t[0] < GetTime(9, 0, 0)) ans++;
		}

		if(ans == 0) puts("All OK");
		else if(ans > 3) puts("Issue Show Cause Letter");
		else printf("%d Point(s) Deducted\n", ans);
	}
	return 0;
}

