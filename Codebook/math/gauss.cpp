void gauss(vector<vector<double>>& v) {
	if(v.empty()) return;
	int n = (int)v.size(), m = (int)v[0].size();
	for(int i = 0; i < m; i++) {
		int p = -1;
		for(int j = i; j < n; j++) {
			if(fabs(v[j][i]) < eps) continue;
			if(p == -1 || fabs(v[j][i]) > fabs(v[p][i])) p = j;
		}
		if(p == -1) continue;
		for(int j = 0; j < m; j++) swap(v[p][j], v[i][j]);
		for(int j = 0; j < n; j++) {
			if(i == j) continue;
			double tmp = v[j][i] / v[i][i];
			for(int k = 0; k < m; k++) v[j][k] -= tmp * v[i][k];
		}
	}
}
