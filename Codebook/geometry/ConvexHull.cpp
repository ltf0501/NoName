vector<Point> convexhull(Vector<Point> ps) {
	sort(ps.begin(), ps.end());
	vector<Point> res;
	int m;
	for(int i = 0; i < (int)ps.size(); i++) {
		while((m = (int)res.size() > 1) && (res[m - 1] - res[m - 2]) ^ (ps[i] - res[m - 2]) <= 0) res.pop_back();
		res.push_back(ps[i]);
	}
	int k = (int)res.size();
	for(int i = (int)ps.size() - 2; i >= 0; i--) {
		while((m = (int)res.size()))
	}
}
