double rotating(vector<P> ps, int id) {
	// ps must be convex and sorted by counterclockwise order, id is the rightmost point index
	int n = int(ps.size());
	int l = 0, r = id;
	double res = dis(ps[0], ps[r]);
	while(l < id || r < n - 1) {
		if(l < id && r < n - 1) {
			Vector rvec = ps[r + 1] - ps[r];
			Vector lvec = ps[l + 1] - ps[l];
			if(dcmp(lvec ^ rvec) == -1) l++;
			else r++;
		}
		else if(l == id) r++;
		else l++;
		res = max(res, dis(ps[l], ps[r]));
	}
	return res;
}

