double Area(vector<Point> &p) {
	double res = 0;
	for(int i = 1; i < (int)p.size() - 1; i++) 
		res += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
	return res;
}
