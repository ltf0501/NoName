#include <bits/stdc++.h>
using namespace std;

struct Pt {
	int64_t x, y;
	Pt operator -(const Pt &rhs) const {
		return Pt { rhs.x - x, rhs.y - y };
	}
} trea, person[1010], dir[1010];
pair<Pt, Pt> wall[1010];

int64_t dist(Pt a, Pt b) {
	return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

int64_t dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}

int64_t cross(Pt a, Pt b) {
	return a.x * b.y - b.x * a.y;
}

bool between(Pt a, Pt b, Pt c) {
	return (dist(a, b) > dist(a, c) && cross(c - a, b - a) == 0 && dot(c - a, b - a) >= 0);
}

int64_t toAbs(int64_t x) {
	if (!x) return 0;
	return x / abs(x);
}

bool intersect(Pt a1, Pt a2, Pt b1, Pt b2) {
	int64_t c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1), c3 = cross(b2 - b1, a1 - b1), c4 = cross(b2 - b1, a2 - b1);
	c1 = toAbs(c1), c2 = toAbs(c2), c3 = toAbs(c3), c4 = toAbs(c4);
	return c1 * c2 <= 0 && c3 * c4 <= 0;
}

int main() {
	int w, p; cin >> w >> p;
	cin >> trea.x >> trea.y;
	for (int i = 0; i < w; i++) {
		cin >> wall[i].first.x >> wall[i].first.y >> wall[i].second.x >> wall[i].second.y;
	}
	for (int i = 0; i < p; i++) {
		cin >> person[i].x >> person[i].y;
		cin >> dir[i].x >> dir[i].y;
	}
	for (int i = 0; i < p; i++) {
		bool fail = false;
		if (dist(trea, person[i]) > dist(person[i], dir[i])) {
			//cerr << "dist\n";
			fail = true;
		}
		if (dot(dir[i] - person[i], trea - person[i]) < 0) {
			//cerr << "dir\n";
			fail = true;
		}
		for (int j = 0; j < w; j++) {
			if (intersect(person[i], trea, wall[j].first, wall[j].second)) {
				//cerr << "wall\n";
				fail = true;
				break;
			}
		}
		for (int j = 0; j < p; j++) {
			if (i == j) continue;
			if (between(person[i], trea, person[j])) {
				//cerr << "per\n";
				fail = true;
				break;
			}
		}
		cout << (fail ? "not visible\n" : "visible\n");
	}
}
