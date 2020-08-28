#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 200000 + 10;
const int kInf = 1e9;
int sa[kN], tmp[2][kN], cnt[kN], hi[kN],
  r[kN];
// sa[i]: sa[i]-th suffix is the i-th smallest
// suffix hi[i]: LCP of suffix sa[i] and suffix
// sa[i - 1]
void build(string s) {
  int *rnk = tmp[0], *rkn = tmp[1];
  int sigma = 256;
  int n = int(s.length());
  for (int i = 0; i < 256; i++) cnt[i] = 0;
  for (int i = 0; i < n; i++) cnt[rnk[i] = s[i]]++;
  for (int i = 1; i < 256; i++)
    cnt[i] += cnt[i - 1];
  for (int i = n - 1; i >= 0; i--)
    sa[--cnt[uint8_t(s[i])]] = i;
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < sigma; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++) cnt[rnk[i]]++;
    for (int i = 1; i < sigma; i++)
      cnt[i] += cnt[i - 1];
    int *sa2 = rkn;
    int p = 0;
    for (int i = n - k; i < n; i++) sa2[p++] = i;
    for (int i = 0; i < n; i++) {
      if (sa[i] >= k) sa2[p++] = sa[i] - k;
    }
    for (int i = n - 1; i >= 0; i--)
      sa[--cnt[rnk[sa2[i]]]] = sa2[i];
    rkn[sa[0]] = p = 0;
    for (int i = 1; i < n; i++) {
      if (!(rnk[sa[i - 1]] == rnk[sa[i]] &&
            sa[i - 1] + k < n &&
            rnk[sa[i - 1] + k] == rnk[sa[i] + k]))
        p++;
      rkn[sa[i]] = p;
    }
    swap(rnk, rkn);
    if (p == n - 1) break;
    sigma = p + 1;
  }
  for (int i = 0; i < n; i++) r[sa[i]] = i;
  int id = 0;
  hi[0] = 0;
  for (int i = 0; i < n; i++) {
    if (!r[i]) {
      id = 0;
      continue;
    }
    while (i + id < n &&
      s[i + id] == s[sa[r[i] - 1] + id])
      id++;
    hi[r[i]] = id ? id-- : 0;
  }
}

void Init() {
	memset(sa, 0, sizeof(sa));
	memset(tmp, 0, sizeof(tmp));
	memset(cnt, 0, sizeof(cnt));
	memset(hi, 0, sizeof(hi));
	memset(r, 0, sizeof(r));
}
int main() {
	freopen("blackboard.in", "r", stdin);
	freopen("blackboard.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	string s, t;
	cin >> s >> t;
	int n = int(s.size());
	int ans = n;
	int N = n + n + 1;
	for(int _ = 0; _ < 2; _++) {
		Init();
		string ss = s + '#' + t;
		build(ss);
		vector<int> rr(N - 1);
		for(int i = 0; i < N - 1; i++) rr[i] = i + 1;

		vector<int> com(N);
		for(int i = 0; i < N; i++) com[i] = i;
		function<int(int)> Find = [&](int x) {return com[x] == x ? x : com[x] = Find(com[x]);};

		vector<int> L(N, kInf), R(N, -kInf);
		for(int i = 0; i < N; i++) {
			if(sa[i] < n) L[i] = sa[i];
			else if(sa[i] > n) R[i] = sa[i] - n - 1;
		}
		auto Merge = [&](int i, int j, int len) {
			//printf("i = %d, j = %d, len = %d\n", sa[i], sa[j], len);
			//printf("(%d, %d), (%d, %d)\n", L[i], R[i], L[j], R[j]);
			i = Find(i), j = Find(j);
			//if((sa[i] < n && sa[j] > n) || (sa[i] > n && sa[j] < n)) { 
				ans = min(ans, N - 1 - 2 * len + L[i] - R[j]);
				ans = min(ans, N - 1 - 2 * len + L[j] - R[i]);
				//printf("mn = %d\n", N - 1 - 2 * len + min(L[i] - R[j], L[j] - R[i]));
			//}
			L[j] = min(L[j], L[i]), R[j] = max(R[j], R[i]);
			com[i] = j;
		};

		sort(rr.begin(), rr.end(), [&](int i, int j) {return hi[i] > hi[j];});
		for(int id : rr) {
			//if((sa[id - 1] < n && sa[id] < n) || (sa[id - 1] > n && sa[id] > n)) continue;
			Merge(id - 1, id, hi[id]);
		}
		reverse(s.begin(), s.end());
		reverse(t.begin(), t.end());
		//reverse(ss.begin(), ss.end());
	}
	cout << ans << '\n';
	return 0;
} 
