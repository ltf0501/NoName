bool check(int x, int p) {
	return pw(x, (p - 1) >> 1, p) == 1;
}
int cal_quadratic_residue(int a, int p) {
	a %= p; if(a < 0) a += p;
	if(!check(a, p)) return -1;
	int b = -1;
	for(b = 2; ; b++)
		if(!check(b, p)) break;
	assert(b != -1);
	int inva = inv(a, p);
	int t = 0;
	while((p - 1) % (1 << t) == 0) t++;
	t--;
	printf("t = %d\n", t);
	int s = (p - 1) / (1 << t);
	int x = pw(a, (s + 1) >> 1, p);
	int w = pw(a, s, p);
	int k = 1;
	while(k < t) {
		if(pw(w, 1 << (t - k - 1), p) != 1) {
			x = 1LL * x * pw(b, ((1 << (k - 1)) * s), p) % p;
			w = 1LL * inva * pw(x, 2, p) % p; 
		}
		k++;
	}
	return x;
}

