void failure(char *c, int *f) {//c is 0-base and f is 1-base
	int n = strlen(c);
	f[0] = f[1] = 0;
	for(int i = 1; i < n; i++) {
		int k = f[i];
		while(k && c[i] != c[k]) k = f[k];
		f[i + 1] = (c[i] == c[k]) ? k + 1 : 0;
	}
}
int match(char *c, int *f, char *t) {
	int res = 0;
	int j = 0;
	int m = strlen(t), n = strlen(c);
	for(int i = 0; i < m; i++) {
		while(j && c[j] != t[i]) j = f[j];
		if(c[j] == t[i]) j++;
		if(j == n) res++;
	}
	return res;
}
