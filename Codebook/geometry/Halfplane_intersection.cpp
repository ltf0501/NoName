bool cmp(Line a, Line b) {
	return same(a.o, b.o) ? dcmp((b.pb - b.pa) ^ (a.pb - b.pa)) == 1 : a.o < b.o;
} 
bool check(Line l1, Line l2, Line l) {
	if(is_parallel(l1, l2)) return 0;
	P p = line_intersection(l1, l2);
	return dcmp((l.pb - l.pa) ^ (p - l.pa)) != -1;
}
vector<P> HPI(vector<Line> ls) {
	sort(ls.begin(), ls.end(), cmp);
	vector<Line> vec;
	for(int i = 0; i < int(ls.size()); i++) {
		if(!vec.empty() && dcmp(ls[i].o - vec.back().o) == 0) continue;
		vec.push_back(ls[i]);
	}
	deque<Line> dq;
	for(int i = 0; i < int(vec.size()); i++) {
		while(dq.size() >= 2 && !check(dq[dq.size() - 2], dq[dq.size() - 1], vec[i])) dq.pop_back();
		while(dq.size() >= 2 && !check(dq[0], dq[1], vec[i])) dq.pop_front();
		dq.push_back(vec[i]); 
	}
	while(dq.size() >= 2 && !check(dq[dq.size() - 2], dq[dq.size() - 1], dq[0])) dq.pop_back();
	while(dq.size() >= 2 && !check(dq[0], dq[1], dq[dq.size() - 1])) dq.pop_front();
	vector<P> res;
	for(int i = 0; i < dq.size(); i++) res.push_back(line_intersection(dq[i], dq[(i + 1) % dq.size()]));
	return res;
}

