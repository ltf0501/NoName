int point_in_polygon(vector<P> ps, P p) {
	int cnt = 0;
	int wn = 0;
	for(int i = 0; i < (int)ps.size(); i++) {
		int ii = (i + 1) % (int)ps.size();
		if(onsegment(p, ps[i], ps[ii])) return -1;
		int k = dcmp((ps[ii] - ps[i]) ^ (p - ps[i]));
		int d1 = dcmp(ps[i].y - p.y);
		int d2 = dcmp(ps[ii].y - p.y);
		if(k > 0 && d1 <= 0 && d2 > 0) wn++;
		if(k < 0 && d2 <= 0 && d1 > 0) wn--;
	}
	if(wn != 0) return 1; // inside
	return 0; // outside
}
