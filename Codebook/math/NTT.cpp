/* p=a*2^k+1
   p                     a      k      root
   998244353             119    23     3
   2013265921            15     27     31
   2061584302081         15     37     7
   2748779069441         5      39     3
   1945555039024054273	 27     56     5 */
struct NTT {
	int n, invn, rev[kN];
	int g;
	int omega[kN], iomega[kN];
	void init(int n, int g) {
		this->n = n, this->g = g;
		invn = Inv(n);
		int k = log2(n);
		int x = pw(g, (kMod - 1) / n);
		omega[0] = 1;
		for(int i = 1; i < n; i++) omega[i] = 1LL * omega[i - 1] * x % kMod;
		iomega[n - 1] = Inv(omega[n - 1]);
		for(int i = n - 2; i >= 0; i--) iomega[i] = 1LL * iomega[i + 1] * x % kMod;

		for(int i = 0; i < n; i++) {
			int t = 0;
			for(int j = 0; j < k; j++) 
				if(i & (1 << j)) t |= (1 << (k - j - 1));
			rev[i] = t;
		}
	}
	void transform(vector<int> &a, int *omega) {
		for(int i = 0; i < n; i++) 
			if(i < rev[i]) swap(a[i], a[rev[i]]);

		for(int len = 2; len <= n; len <<= 1) {
			int mid = len >> 1;
			int r = n / len;
			for(int j = 0; j < n; j += len) {
				for(int i = 0; i < mid; i++) {
					int t = 1LL * omega[r * i] * a[j + mid + i] % kMod;
					a[j + mid + i] = a[j + i] - t;
					if(a[j + mid + i] < 0) a[j + mid + i] += kMod;
					a[j + i] += t;
					if(a[j + i] >= kMod) a[j + i] -= kMod;
				}
			}
		}
	}
	void dft(vector<int> &a) {
		transform(a, omega);
	}
	void idft(vector<int> &a) {
		transform(a, iomega);
		for(int i = 0; i < n; i++) a[i] = 1LL * a[i] * invn % kMod;
	} 
};
vector<int> mul(vector<int> a, vector<int> b) {
	int n = 1;
	int n1 = int(a.size()), n2 = int(b.size());
	while(n < n1 + n2 - 1) n <<= 1;
	a.resize(n), b.resize(n);
	solver.init(n, 3); // 3 is primitive root for 998244353
	solver.dft(a), solver.dft(b);
	for(int i = 0; i < n; i++) a[i] = 1LL * a[i] * b[i] % kMod;
	solver.idft(a);
	while(!a.empty() && a.back() == 0) a.pop_back();
	return a;
}
