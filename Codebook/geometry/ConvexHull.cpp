vector<P> convexhull(vector<P> ps) {
	vector<P> p;
	for(int i = 0; i < (int)ps.size(); i++) {
		while(p.size() >= 2 && ((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) > 0) p.pop_back();
		p.push_back(ps[i]);
	}
	int t = (int)p.size();
	for(int i = (int)ps.size() - 2; i >= 0; i--) {
		while(p.size() > t && ((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) > 0) p.pop_back();
		p.push_back(ps[i]);
	}
	p.pop_back();
	return p;
}
