# Codebook #

## C++11 Regex ##
```cpp
std::string s = "Some people, when confronted with a problem, think";
std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::ECMAScript | std::regex_constants::icase);
if (std::regex_search(s, self_regex)) std::cout << "Text contains 'regular expressions'\n";
std::regex word_regex("(\\S+)");
auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
auto words_end = std::sregex_iterator();
std::cout << "Found " << std::distance(words_begin, words_end) << " words\n";
const int N = 6;
std::cout << "Words longer than " << N << " characters:\n";
for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
  std::smatch match = *i;
  std::string match_str = match.str();
  if (match_str.size() > N) std::cout << "  " << match_str << '\n';
}
std::regex long_word_regex("(\\w{7,})");
std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
```

## PBDS Tree ##
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
tree<pair<int64_t, int>, null_type, less<pair<int64_t, int> >, rb_tree_tag, tree_order_statistics_node_update> st;
st.order_of_key(...), st.find_by_order(...);
```

## PBDS Paring Heap ##
```cpp
#include<ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<int, cmp, pairing_heap_tag> heap;
hp.join(...), hp.modify(it, ...), hp.erase(it);
```

## Rope ##
```cpp
#include <ext/rope>
using namespace __gnu_cxx;
rope<char> *r[MAXN];
r[t] = new rope<char>(*r[t - 1]);
r[t]->insert(p, ch), r[t]->erase(p, cnt), r[v]->at(i);
```

## Anti Stack Overflow ##
```cpp
int size = 256 << 20; // 256MB
register long rsp asm("rsp");
char *_p = (char*)malloc(size) + size, *_bak = (char*)rsp;
__asm__("movq %0, %%rsp\n" :: "r"(_p));
__asm__("movq %0, %%rsp\n" :: "r"(_bak));
```

## Pragma Optimization ##
```cpp
#pragma GCC optimize("Ofast","no-stack-protector","no-math-errno")
#pragma GCC target("avx2","tune=native", "arch=core-avx2")
#pragma GCC ivdep
```

## Input Optimization ##
```cpp
static inline char getRawChar() {
  static char buf[1 << 16], *p = buf, *end = buf;
  if (p == end) {
    if ((end = buf + fread_unlocked(buf, 1, 1 << 16, stdin)) == buf) return '\0';
    p = buf;
  }
  return *p++;
}
while (c = getRawChar() && (unsigned)(c - '0') > 10U) n = n * 10 + (c - '0');
```

## Computational Geometry Misc. ##
```cpp
#define DB double
const DB PI = acos(-1);
const DB eps = 1e-10;
int dcmp(DB x) {
  if (fabs(x) < eps) { return 0; }
  return x < 0 ? -1 : 1;
}
struct Point {
  DB x, y;
  Point(DB x = 0, DB y = 0): x(x), y(y) {}
};
typedef Point Vector;
Vector operator + (Vector A, Vector B) {return Vector(A.x + B.x, A.y + B.y);}
Vector operator - (Vector A, Vector B) {return Vector(A.x - B.x, A.y - B.y);}
Vector operator * (Vector A, DB p) {return Vector(A.x * p, A.y * p);}
Vector operator / (Vector A, DB p) {return Vector(A.x / p, A.y / p);}
bool operator < (const Point &a, const Point &b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool operator ==(const Point &a, const Point &b) {
  return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
/// 內積 : 長度 夾角
DB Dot(Vector A, Vector B) {return A.x * B.x + A.y * B.y;}
DB Length(Vector A) {return sqrt(Dot(A, A));}
DB Angle(Vector A, Vector B) {return acos(Dot(A, B) / (Length(A) * Length(B)));}
/// 外積 : 面積
DB Cross(Vector A, Vector B) {return A.x * B.y - B.x * A.y;}
DB Area2(Point A, Point B, Point C) {return Cross(B - A, C - A);}
/// 繞起點逆時針旋轉a度
/// x'=xcosa-ysina , y'=xsina+ycosa
Vector Rotate(Vector A, DB rad) {
  return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
/// 左轉90度->單位法向量
Vector Normal(Vector A) {DB L = Length(A); return Vector(-A.y / L, A.x / L);}
/// 直線交點
/// set two lines are P+tv & Q+tw and Vector u=P-Q ,
/// the parameter of intersection on line 1 is t1 and t2 as on line 2
/// we can solve for t1=Cross(w,u)/Cross(v,w) t2=Cross(v,u)/Cross(v,w)
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
  Vector u = P - Q;
  DB t = Cross(w, u) / Cross(v, w);
  return P + v * t;
}
/// 點P到直線AB距離
DB DistanceToLine(Point P, Point A, Point B) {
  Vector v1 = B - A, v2 = P - A;
  return fabs(Cross(v1, v2) / Length(v1));
}
/// 點P到線段AB距離
/// set Q the projection point on line AB
/// consider 1.Q on Segment AB 2.Q on ray AB 3.Q on ray BA
DB DistanceToSegment(Point P, Point A, Point B) {
  if (A == B) { return Length(P - A); }
  Vector v1 = B - A, v2 = P - A, v3 = P - B;
  if (dcmp(Dot(v1, v2)) < 0) { return Length(v2); }
  else if (dcmp(Dot(v1, v3)) < 0) { return Length(v3); }
  else { return fabs(Cross(v1, v2) / Length(v1)); }
}
/// 點P在直線AB上投影
/// set Q=A+t0*v v=B-A, we have Dot(AB,QP)=0
/// so Dot(v,P-(A+t0*v)=0 solve for Dot(v,AP)-t0*Dot(v,v)=0
/// so t0=Dot(v,AP)/Dot(v,v)
Point GetLineProjection(Point P, Point A, Point B) {
  Vector v = B - A;
  return A + v * (Dot(v, P - A) / Dot(v, v));
}
/// 線段相交判斷
/// define "Proper intersection" only one intersection point and is not the Endpoints
/// of both Segments
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
  DB c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
  DB c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
/// 點在線段上判斷
bool OnSegment(Point p, Point a1, Point a2) {
  return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}
/// 多邊形面積(凹凸皆可)
DB PolygonArea(Point *p, int n) {
  DB area = 0;
  for (int i = 1; i < n - 1; i++) { area += Cross(p[i] - p[0], p[i + 1] - p[0]); }
  return area / 2;
}
///!!!!!Another way to implement Vector!!!!!///
///  #include<complex>
///  using namespace std;
///  typedef complex<DB> Point;
///  typedef Point Vector;
///  real(p)->x imag(p)->y conj(a+bi)-> a-bi
///  double Dot(Vector A,Vector B) {return real(conj(A)*B);}
///  double Cross(Vector A,Vector B) {return imag(conj(A)*B);}
///  Vector Rotate(Vector A, DB rad) {return A*exp(Point(0,rad));}
struct Circle {
  Point c;
  DB r;
  Circle(Point c, double r): c(c), r(r) {}
  Point point(DB a) {
    return Point(c.x + cos(a) * r, c.y + sin(a) * r);
  }
};
/// 這邊不知道有沒有寫對QAQ
/*
struct Line
{
  Point A;
  Vector v;
  Line(Point a,Vector v):A(a),v(v) {}
};
/// 直線與圓交點
int getLineCircleIntersection(Line L,Circle C,DB &t1,DB &t2,vector<Point> &sol)
{
  Point p=GetLineProjection(C.c,L.A,L.A+L.v);
  DB l=sqrt(C.r*C.r-DistanceToLine(C.c,L.A,L.A+L.v));
  int ret=0;
  Point a=p+(L.v)*l;
  if(dcmp(Length(C.c-a)-C.r)==0) {sol.push_back(a);ret++;}
  a=p-(L.v)*l;
  if(dcmp(Length(C.c-a)-C.r)==0) {sol.push_back(a);ret++;}
  return ret;
}
*/
///向量極角
DB angle(Vector v) {return atan2(v.y, v.x);}
/// 兩圓相交
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point> &sol) {
  DB d = Length(C1.c - C2.c);
  if (dcmp(d) == 0) { ///同心圓
    if (dcmp(C1.r - C2.r) == 0) { return -1; } ///兩圓重合交點無限
    return 0; ///內離
  }
  if (dcmp(C1.r + C2.r - d) < 0) { return 0; } ///外離
  if (dcmp(fabs(C1.r - C2.r) - d) > 0) { return 0; } ///內離
  DB a = angle(C2.c - C1.c); /// 向量C1C2的極角
  DB da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
  Point p1 = C1.point(a - da), p2 = C1.point(a + da);
  sol.push_back(p1);
  if (p1 == p2) { return 1; }
  sol.push_back(p2);
  return 2;
}
/// 過定點作圓切線
int getTangents(Point p, Circle C, Vector *v) {
  Vector u = C.c - p;
  DB dist = Length(u);
  if (dist < C.r) { return 0; } /// 點在圓內
  else if (dcmp(dist - C.r) == 0) { /// p在圓上
    v[0] = Rotate(u, PI / 2);
    return 1;
  } else {
    DB ang = asin(C.r / dist);
    v[0] = Rotate(u, -ang);
    v[1] = Rotate(u, ang);
    return 2;
  }
}
/// 兩圓的公切線
int getTangents(Circle A, Circle B, Point *a, Point *b) {
  int cnt = 0;
  if (A.r < B.r) {swap(A, B); swap(a, b);}
  int d2 = (A.c.x - B.c.x) * (A.c.x - B.c.x) + (A.c.y - B.c.y) * (A.c.y - B.c.y);
  int rdiff = A.r - B.r;
  int rsum = A.r + B.r;
  if (d2 < rdiff * rdiff) { return 0; } /// 兩圓內離
  DB base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
  if (d2 == 0 && A.r == B.r) { return -1; } /// 兩圓重合，無限多條切線
  if (d2 == rdiff * rdiff) { /// 兩圓內切，1條切線
    a[cnt] = A.point(base);
    b[cnt] = B.point(base);
    cnt++;
    return 1;
  }
  /// 有外公切線
  DB ang = acos((A.r - B.r) / sqrt(d2));
  a[cnt] = A.point(base + ang);
  b[cnt] = B.point(base + ang);
  cnt++;
  a[cnt] = A.point(base - ang);
  b[cnt] = B.point(base - ang);
  cnt++;
  if (d2 == rsum * rsum) { ///兩圓外切，1條內公切線
    a[cnt] = A.point(base);
    b[cnt] = B.point(PI + base);
    cnt++;
  } else if (d2 > rsum * rsum) { /// 兩圓外離，兩條內公切線
    DB ang = acos((A.r + B.r) / sqrt(d2));
    a[cnt] = A.point(base + ang);
    b[cnt] = B.point(PI + base + ang);
    cnt++;
    a[cnt] = A.point(base - ang);
    b[cnt] = B.point(PI + base - ang);
    cnt++;
  }
  return cnt;
}
///球面座標相關
///x=rcos(theta)cos(phi)
///y=rcos(theta)sin(phi)
///z=rsin(theta)
///deg->rad
DB torad(DB deg) {
  return deg / 180 * acos(-1);
}
/// 球面座標->直角坐標
/// latitude->緯度 longitude->經度
void get_coord(DB R, DB lat, DB lng, DB &x, DB &y, DB &z) {
  lat = torad(lat);
  lng = torad(lng);
  x = R * cos(lat) * cos(lng);
  y = R * cos(lat) * sin(lng);
  z = R * sin(lat);
}
typedef vector<Point> Polygon;
/// 點在多邊形內判定
/// Winding number
int isPointInPolygon(Point p, Polygon poly) {
  int wn = 0;
  int n = poly.size();
  for (int i = 0; i < n; i++) {
    if (OnSegment(p, poly[i], poly[(i + 1) % n])) { return -1; } /// 在邊界上
    int k = dcmp(Cross(poly[i] - p, poly[(i + 1) % n] - p));
    int d1 = dcmp(poly[i].y - p.y);
    int d2 = dcmp(poly[(i + 1) % n].y - p.y);
    if (k > 0 && d1 <= 0 && d2 > 0) { wn++; }
    if (k < 0 && d2 <= 0 && d1 > 0) { wn--; }
  }
  if (wn != 0) { return 1; }
  return 0;
}
/// 凸包(Andrew's algorithm)
/// 點陣列p 個數n 輸出點陣列ch 回傳凸包頂點數
/// 輸入不可有重複點
int ConvexHull(Point *p, int n, Point *ch) {
  sort(p, p + n);
  int m = 0;
  for (int i = 0; i < n; i++) {
    while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) { m--; }
    ch[m++] = p[i];
  }
  int k = m;
  for (int i = n - 2; i >= 0; i--) {
    while (m > k && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) { m--; }
    ch[m++] = p[i];
  }
  if (n > 1) { m--; }
  return m;
}
/// 定義有向直線
struct Line {
  Point P;
  Vector v;
  DB ang;
  Line() {}
  Line(Point P, Vector v): P(P), v(v) {ang = atan2(v.y, v.x);}
  bool operator < (const Line &rhs) const {
    return ang < rhs.ang;
  }
};
/// 半平面交
/// 運用排序、掃描、deque，時間複雜度為O(nlogn)
bool OnLeft(Line L, Point p) {
  return Cross(L.v, p - L.P) > 0;
}
Point GetIntersection(Line a, Line b) {
  Vector u = a.P - b.P;
  DB t = Cross(b.v, u) / Cross(a.v, b.v);
  return a.P + a.v * t;
}
int HalfplaneIntersection(Line *L, int n, Point *poly) {
  sort(L, L + n); /// sort by angle
  int first, last; /// deque pointer
  Point *p = new Point[n]; /// p[i]:intersection of q[i]&q[i+1]
  Line *q = new Line[n]; /// deque
  q[first = last = 0] = L[0]; /// start with L[0]
  for (int i = 1; i < n; i++) {
    while (first < last && !OnLeft(L[i], p[last - 1])) { last--; }
    while (first < last && !OnLeft(L[i], p[first])) { first++; }
    q[++last] = L[i];
    if (dcmp(Cross(q[last].v,
          q[last - 1].v)) == 0) { /// Parallel and in the same direction
      last--;
      if (OnLeft(q[last], L[i].P)) { q[last] = L[i]; }
    }
    if (first < last) { p[last - 1] = GetIntersection(q[last - 1], q[last]); }
  }
  while (first < last && !OnLeft(q[first], p[last - 1])) { last--; } /// delete unwanted plane
  if (last - first <= 1) { return 0; } /// empty set
  p[last] = GetIntersection(q[last], q[first]);
  ///deque->output
  int m = 0;
  for (int i = first; i <= last; i++) { poly[m++] = p[i]; }
  return m;
}
```

## Rotating Caliper ##
```cpp
for (int i = 0; i < n; i++) { cin >> p[i].x >> p[i].y; }
n = convex(n);
int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
for (int i = 1; i < n; i++) {
  if (cmp(hull[i].y - hull[p1].y) < 0) { p1 = i; }
  if (cmp(hull[i].y - hull[p2].y) > 0) { p2 = i; }
  if (cmp(hull[i].x - hull[p3].x) < 0) { p3 = i; }
  if (cmp(hull[i].x - hull[p4].x) > 0) { p4 = i; }
}
Vect orig = { 1, 0 }, v1 = { 1, 0 }, v2 = { 0, 1 };
double ansArea = 1E30, ansLen = 1E30;
while (cmp(cross(orig, v1)) >= 0) {
  double d1 = distToLine(hull[p1], hull[p2], hull[p2] + v1),
         d2 = distToLine(hull[p3], hull[p4], hull[p4] + v2);
  ansArea = min(ansArea, d1 * d2);
  ansLen = min(ansLen, 2 * (d1 + d2));
  double minAng = turnAngle(v1, hull[p1 + 1] - hull[p1]);
  minAng = min(minAng, turnAngle(ZERO - v1, hull[p2 + 1] - hull[p2]));
  minAng = min(minAng, turnAngle(ZERO - v2, hull[p3 + 1] - hull[p3]));
  minAng = min(minAng, turnAngle(v2, hull[p4 + 1] - hull[p4]));
  v1 = rotate(v1, minAng), v2 = rotate(v2, minAng);
  if (cmp(angle(v1, hull[p1 + 1] - hull[p1])) == 0) { p1 = (p1 + 1) % n; }
  if (cmp(angle(ZERO - v1, hull[p2 + 1] - hull[p2])) == 0) { p2 = (p2 + 1) % n; }
  if (cmp(angle(ZERO - v2, hull[p3 + 1] - hull[p3])) == 0) { p3 = (p3 + 1) % n; }
  if (cmp(angle(v2, hull[p4 + 1] - hull[p4])) == 0) { p4 = (p4 + 1) % n; }
}
```

## Smallest Enclosing Circle ##
```cpp
Circle getCircle(const Point &a, const Point &b, const Point &c) {
  double a1, a2, b1, b2, c1, c2;
  Circle ret;
  a1 = 2 * (a.x - b.x); a2 = 2 * (a.x - c.x);
  b1 = 2 * (a.y - b.y); b2 = 2 * (a.y - c.y);
  c1 = a.x * a.x - b.x * b.x + a.y * a.y - b.y * b.y;
  c2 = a.x * a.x - c.x * c.x + a.y * a.y - c.y * c.y;
  ret.c.x = Point(c1, b1).xMul(Point(c2, b2)) / Point(a1, b1).xMul(Point(a2, b2));
  ret.c.y = Point(a1, c1).xMul(Point(a2, c2)) / Point(a1, b1).xMul(Point(a2, b2));
  ret.r = dis(ret.c, a);
  return ret;
}
Circle update(int k) {
  int i, j;
  Circle ret;
  ret.c = Point((p[k - 1].x + p[k].x) / 2, (p[k - 1].y + p[k].y) / 2);
  ret.r = dis(p[k - 1], p[k]) / 2;
  for (i = k - 2; ~i; --i) {
    if (!inCircle(p[i], ret)) {
      ret.c = Point((p[i].x + p[k].x) / 2, (p[i].y + p[k].y) / 2);
      ret.r = dis(p[i], p[k]) / 2;
      for (j = i + 1; j < k; ++j) {
        if (!inLine(p[j], p[i], p[k]) && !inCircle(p[j], ret)) ret = getCircle(p[i], p[j], p[k]);
      }
    }
  }
  return ret;
}
Circle solve(int n) {
  int i;
  Circle ret;
  if (n == 1) {
    ret.c = p[0]; ret.r = 0;
    return ret;
  }
  random_shuffle(p, p + n);
  ret.c = Point((p[0].x + p[1].x) / 2, (p[0].y + p[1].y) / 2);
  ret.r = dis(p[0], p[1]) / 2;
  for (i = 2; i < n; ++i) {
    if (!inCircle(p[i], ret)) ret = update(i);
  }
  return ret;
}
```

## Sparse Table ##
```cpp
for (int j = 1; j <= n; j++) { sparse[0][j] = x[j] + y[j]; }
for (int i = 1, d = 1; d <= n; i++, d <<= 1) {
  for (int j = 1; j + d <= n; j++) sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + d]);
}
uint32_t sparseMin = min(sparse[t][l], sparse[t][r - (1 << t) + 1]);
```

## Link Cut Tree ##
```cpp
struct SplayNode {
  static SplayNode HOLE;
  SplayNode *ch[2], *par;
  bool rev;
  SplayNode(): par(&HOLE), rev(false) { ch[0] = ch[1] = &HOLE; }
  bool isRoot() {
    return (par->ch[0] != this && par->ch[1] != this);
  }
  void push() {
    if (rev) {
      if (ch[0]) ch[0]->rev ^= 1;
      if (ch[1]) ch[1]->rev ^= 1;
      swap(ch[0], ch[1]);
      rev ^= 1;
    }
  }
  void pushFromRoot() {
    if (!isRoot()) par->pushFromRoot();
    push();
  }
  void pull() {
    if (ch[0]) ch[0]->d = d + ch[0]->parLen;
    if (ch[1]) ch[1]->d = d + ch[1]->parLen;
  }
  void rotate() {
    SplayNode *p = par, *gp = p->par;
    bool dir = (p->ch[1] == this);
    par = gp;
    if (!p->isRoot()) gp->ch[gp->ch[1] == p] = this;
    p->ch[dir] = ch[dir ^ 1];
    p->ch[dir]->par = p;
    p->par = this;
    ch[dir ^ 1] = p;
    p->pull(), pull();
  }
  void splay() {
    pushFromRoot();
    while (!isRoot()) {
      if (!par->isRoot()) {
        SplayNode *gp = par->par;
        if ((gp->ch[0] == par) == (par->ch[0] == this)) rotate();
        else par->rotate();
      }
      rotate();
    }
  }
} SplayNode::HOLE;
namespace LCT {
  SplayNode *access(SplayNode *x) {
    SplayNode *last = &SplayNode::HOLE;
    while (x != &SplayNode::HOLE) {
      x->splay();
      x->ch[1] = last;
      x->pull();
      last = x;
      x = x->par;
    }
    return last;
  }
  void makeRoot(SplayNode *x) {
    access(x);
    x->splay();
    x->rev ^= 1;
  }
  void link(SplayNode *x, SplayNode *y) {
    makeRoot(x);
    x->par = y;
  }
  void cut(SplayNode *x, SplayNode *y) {
    makeRoot(x);
    access(y);
    y->splay();
    y->ch[0] = &SplayNode::HOLE;
    x->par = &SplayNode::HOLE;
  }
  void cutParent(SplayNode *x) {
    access(x);
    x->splay();
    x->ch[0]->par = &SplayNode::HOLE;
    x->ch[0] = &SplayNode::HOLE;
  }
  SplayNode *findRoot(SplayNode *x) {
    x = access(x);
    while (x->ch[0] != &SplayNode::HOLE) x = x->ch[0];
    x->splay();
    return x;
  }
  SplayNode *query(SplayNode *x, SplayNode *y) {
    makeRoot(x);
    return access(y);
  }
  SplayNode *queryLca(SplayNode *x, SplayNode *y) {
    access(x);
    auto lca = access(y);
    x->splay();
    return lca->data + lca->ch[1]->sum + (x == lca ? 0 : x->sum);
  }
  void modify(SplayNode *x, int data) {
    x->splay();
    x->data = data;
    x->pull();
  }
}
```

## Leftist Tree ##
```cpp
int merge(int x, int y) {
  if (T[x].v > T[y].v || (T[x].v == T[y].v && x > y)) swap(x, y);
  if (!x) return y;
  int &l = T[x].l, &r = T[x].r;
  r = merge(r, y);
  if (T[l].dis < T[r].dis) swap(l, r);
  T[x].dis = T[r].dis + 1;
  return x;
}
```

## Bridge Connected Component ##
```cpp
struct Edge { int u, v; };
int pre[maxn], iscut[maxn], bccno[maxn], dfs_clock, bcc_cnt;
vector<int> G[maxn], bcc[maxn];
stack<Edge> S;
int dfs(int u, int fa) {
  int lowu = pre[u] = ++dfs_clock, child = 0;
  for (int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    Edge e = (Edge) {u, v};
    if (!pre[v]) {
      S.push(e);
      child++;
      int lowv = dfs(v, u);
      lowu = min(lowu, lowv);
      if (lowv >= pre[u]) { /// is cut vertex --> sons and grandsons are one bcc
        iscut[u] = 1;
        bcc_cnt++;
        bcc[bcc_cnt].clear();
        for (;;) {
          Edge x = S.top();
          S.pop();
          if (bccno[x.u] != bcc_cnt) {bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt;}
          if (bccno[x.v] != bcc_cnt) {bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt;}
          if (x.u == u && x.v == v) { break; }
        }
      }
    } else if (pre[v] < pre[u] && v != fa) { S.push(e); lowu = min(lowu, pre[v]); }
  }
  if (fa < 0 && child == 1) iscut[u] = 0;
  return lowu;
}
void find_bcc(int n) {
  memset(pre, 0, sizeof(pre)), memset(iscut, 0, sizeof(iscut)), memset(bccno, 0, sizeof(bccno));
  dfs_clock = bcc_cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!pre[i]) dfs(i, -1);
  }
  for (int i = 1; i <= bcc_cnt; i++) {
    for (int j = 0; j < bcc[i].size(); j++) printf("%d\n", bcc[i][j]);
  }
}
```

## KM ##
```cpp
int N, now_time;
__int128 slack[MAX_N];
ll X[MAX_N] , Y[MAX_N];
__int128 W[MAX_N][MAX_N];
int mx[MAX_N] , my[MAX_N];
int vx[MAX_N] , vy[MAX_N];
__int128 lx[MAX_N] , ly[MAX_N];
bool dfs(int x) {
 vx[x] = now_time;
 REP1(y , 1 , N) {
  if(vy[y] == now_time) continue;
  __int128 t = lx[x] + ly[y] - W[x][y];
  if(t == 0) {
   vy[y] = now_time;
   if(!my[y] || dfs(my[y])) {
    mx[x] = y;
    my[y] = x;
    return 1;
   }
  }
  else slack[y] = min(slack[y] , t);
 }
 return 0;
}
inline void modify() {
 __int128 t = INF128;
 REP1(y , 1 , N) if(vy[y] != now_time) t = min(t , slack[y]);
 REP1(x , 1 ,N) if(vx[x] == now_time) lx[x] -= t;
 REP1(y , 1 , N) if(vy[y] == now_time) ly[y] += t; 
}
inline pair<bool,__int128> km() {
 REP1(x , 1 , N) {
  lx[x] = -INF128;
  REP1(y , 1 , N) lx[x] = max(lx[x] , W[x][y]);
 }
 REP1(y , 1 , N) ly[y] = 0;
 now_time = 0;
 REP1(x , 1 , N) vx[x] = 0 , mx[x] = 0;
 REP1(y , 1 , N) vy[y] = 0 , my[y] = 0;
 REP1(x , 1 , N) {
  while(1) {
   now_time++;
   REP1(y , 1 , N) slack[y] = INF128;
   if(dfs(x)) break;
   else modify();
  }
 }
 __int128 ans = 0;
 REP1(x , 1 , N) {
  if(W[x][mx[x]] == -INF128) return MP(0 , __int128(0));
  else ans -= W[x][mx[x]];
 }
 return MP(1 , ans);
}
```

## Hopcroft-Karp ##
```cpp
void addEdge(int a, int b) {
  edge[nEdge].ed = b;
  edge[nEdge].next = head[a];
  head[a] = nEdge++;
}
bool bfs(int v) {
  int i, x, y;
  front = tail = 0;
  dis = INF;
  memset(disx, -1, sizeof(disx));
  memset(disy, -1, sizeof(disy));
  for (i = 0; i < v; ++i) {
    if (matchx[i] < 0) { disx[que[tail++] = i] = 0; }
  }
  while (front < tail) {
    if (disx[x = que[front++]] > dis) { break; }
    for (i = head[x]; ~i; i = edge[i].next) {
      if (disy[y = edge[i].ed] < 0) {
        disy[y] = disx[x] + 1;
        if (matchy[y] < 0) { dis = disy[y]; }
        else { disx[que[tail++] = matchy[y]] = disy[y] + 1; }
      }
    }
  }
  return dis < INF;
}
bool dfs(int x) {
  int i, y;
  for (i = head[x]; ~i; i = edge[i].next) {
    if (!vis[y = edge[i].ed] && disy[y] == disx[x] + 1) {
      vis[y] = true;
      if ((~matchy[y]) && disy[y] == dis) { continue; }
      if (matchy[y] < 0 || dfs(matchy[y])) {
        matchx[x] = y;
        matchy[y] = x;
        return true;
      }
    }
  }
  return false;
}
int maxMatch(int v) {
  int ret = 0, i;
  memset(matchx, -1, sizeof(matchx));
  memset(matchy, -1, sizeof(matchy));
  while (bfs(v)) {
    memset(vis, 0, sizeof(vis));
    for (i = 0; i < v; ++i) {
      if (matchx[i] < 0 && dfs(i)) { ++ret; }
    }
  }
  return ret;
}
```

## Graph Matching ##
```cpp
struct Graph {
  int n, match[maxn];
  bool adj[maxn][maxn];
  void clear() {
    memset(adj, 0, sizeof(adj));
    n = 0;
  }
  int max(int a, int b) {
    if (a > b) { return a; }
    return b;
  }
  void get_max(int &n, int k) {
    if (k > n) { n = k; }
    return;
  }
  void insert(const int &u, const int &v) {
    get_max(n, max(u, v) + 1);
    adj[u][v] = adj[v][u] = 1;
  }
  int max_match() {
    memset(match, -1, sizeof(match));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (match[i] == -1) {
        ans += bfs(i);
      }
    }
    return ans;
  }
  int Q[maxn], pre[maxn], base[maxn];
  bool hash[maxn];
  bool in_blossom[maxn];
  int bfs(int p) {
    memset(pre, -1, sizeof(pre));
    memset(hash, 0, sizeof(hash));
    for (int i = 0; i < n; ++i) {
      base[i] = i;
    }
    Q[0] = p;
    hash[p] = 1;
    for (int s = 0, t = 1; s < t; ++s) {
      int u = Q[s];
      for (int v = 0; v < n; ++v) {
        if (adj[u][v] && base[u] != base[v] && v != match[u]) {
          if (v == p || (match[v] != -1 && pre[match[v]] != -1)) {
            int b = contract(u, v);
            for (int i = 0; i < n; ++i) {
              if (in_blossom[base[i]]) {
                base[i] = b;
                if (hash[i] == 0) {
                  hash[i] = 1;
                  Q[t++] = i;
                }
              }
            }
          } else if (pre[v] == -1) {
            pre[v] = u;
            if (match[v] == -1) {
              argument(v);
              return 1;
            } else {
              Q[t++] = match[v];
              hash[match[v]] = 1;
            }
          }
        }
      }
    }
    return 0;
  }
  void argument(int u) {
    while (u != -1) {
      int v = pre[u];
      int k = match[v];
      match[u] = v;
      match[v] = u;
      u = k;
    }
  }
  void change_blossom(int b, int u) {
    while (base[u] != b) {
      int v = match[u];
      in_blossom[base[v]] = in_blossom[base[u]] = true;
      u = pre[v];
      if (base[u] != b) {
        pre[u] = v;
      }
    }
  }
  int contract(int u, int v) {
    memset(in_blossom, 0, sizeof(in_blossom));
    int b = find_base(base[u], base[v]);
    change_blossom(b, u);
    change_blossom(b, v);
    if (base[u] != b) {
      pre[u] = v;
    }
    if (base[v] != b) {
      pre[v] = u;
    }
    return b;
  }
  int find_base(int u, int v) {
    bool in_path[maxn] = {};
    while (true) {
      in_path[u] = true;
      if (match[u] == -1) {
        break;
      }
      u = base[pre[match[u]]];
    }
    while (!in_path[v]) {
      v = base[pre[match[v]]];
    }
    return v;
  }
};
```

## Graph Matching (tutte) ##
```cpp
// 使用 tutte 矩阵求一般图最大匹配数
// 时间复杂度 O(n^3logn)，正确率 exp(-2/n^2)
#define MAX 400
#define P 1000000007
typedef long long i64;
int mat[MAX][MAX];
i64 tutte[MAX][MAX];
inline int randInt(int n) {
  return ((rand() << 15) ^ rand()) % n;
}
int matRank(i64 a[MAX][MAX], int n, i64 p) {
  int i, j, k, cnt = 0, cur;
  i64 t;
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      while (a[j][i]) {
        for (t = a[i][i] / a[j][i], k = 0; k < n; ++k) {
          a[i][k] = (a[i][k] - a[j][k] * t) % p;
          swap(a[i][k], a[j][k]);
        }
      }
    }
    for (cur = 0, j = i; j < n; ++j) {
      if (a[i][j]) { cur = 1; }
    }
    cnt += cur;
  }
  return cnt;
}
int maxMatch(const int mat[MAX][MAX], int n) {
  int i, j;
  memset(tutte, 0, sizeof(tutte));
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      if (mat[i][j]) { tutte[j][i] = -(tutte[i][j] = randInt(P)); }
    }
  }
  return matRank(tutte, n, P) >> 1;
}
```

## Graph Maximum Weight Matching ##
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long s64;

const int INF = 2147483647;

const int MaxN = 400;
const int MaxM = 79800;

template <class T>
inline void tension(T &a, const T &b)
{
	if (b < a)
		a = b;
}
template <class T>
inline void relax(T &a, const T &b)
{
	if (b > a)
		a = b;
}
template <class T>
inline int size(const T &a)
{
	return (int)a.size();
}

inline int getint()
{
	char c;
	while (c = getchar(), '0' > c || c > '9');

	int res = c - '0';
	while (c = getchar(), '0' <= c && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

const int MaxNX = MaxN + MaxN;

struct edge
{
	int v, u, w;

	edge(){}
	edge(const int &_v, const int &_u, const int &_w)
		: v(_v), u(_u), w(_w){}
};

int n, m;
edge mat[MaxNX + 1][MaxNX + 1];

int n_matches;
s64 tot_weight;
int mate[MaxNX + 1];
int lab[MaxNX + 1];

int q_n, q[MaxN];
int fa[MaxNX + 1], col[MaxNX + 1];
int slackv[MaxNX + 1];

int n_x;
int bel[MaxNX + 1], blofrom[MaxNX + 1][MaxN + 1];
vector<int> bloch[MaxNX + 1];

inline int e_delta(const edge &e) // does not work inside blossoms
{
	return lab[e.v] + lab[e.u] - mat[e.v][e.u].w * 2;
}
inline void update_slackv(int v, int x)
{
	if (!slackv[x] || e_delta(mat[v][x]) < e_delta(mat[slackv[x]][x]))
		slackv[x] = v;
}
inline void calc_slackv(int x)
{
	slackv[x] = 0;
	for (int v = 1; v <= n; v++)
		if (mat[v][x].w > 0 && bel[v] != x && col[bel[v]] == 0)
			update_slackv(v, x);
}

inline void q_push(int x)
{
	if (x <= n)
		q[q_n++] = x;
	else
	{
		for (int i = 0; i < size(bloch[x]); i++)
			q_push(bloch[x][i]);
	}
}
inline void set_mate(int xv, int xu)
{
	mate[xv] = mat[xv][xu].u;
	if (xv > n)
	{
		edge e = mat[xv][xu];
		int xr = blofrom[xv][e.v];
		int pr = find(bloch[xv].begin(), bloch[xv].end(), xr) - bloch[xv].begin();
		if (pr % 2 == 1)
		{
			reverse(bloch[xv].begin() + 1, bloch[xv].end());
			pr = size(bloch[xv]) - pr;
		}

		for (int i = 0; i < pr; i++)
			set_mate(bloch[xv][i], bloch[xv][i ^ 1]);
		set_mate(xr, xu);

		rotate(bloch[xv].begin(), bloch[xv].begin() + pr, bloch[xv].end());
	}
}
inline void set_bel(int x, int b)
{
	bel[x] = b;
	if (x > n)
	{
		for (int i = 0; i < size(bloch[x]); i++)
			set_bel(bloch[x][i], b);
	}
}

inline void augment(int xv, int xu)
{
	while (true)
	{
		int xnu = bel[mate[xv]];
		set_mate(xv, xu);
		if (!xnu)
			return;
		set_mate(xnu, bel[fa[xnu]]);
		xv = bel[fa[xnu]], xu = xnu;
	}
}
inline int get_lca(int xv, int xu)
{
	static bool book[MaxNX + 1];
	for (int x = 1; x <= n_x; x++)
		book[x] = false;
	while (xv || xu)
	{
		if (xv)
		{
			if (book[xv])
				return xv;
			book[xv] = true;
			xv = bel[mate[xv]];
			if (xv)
				xv = bel[fa[xv]];
		}
		swap(xv, xu);
	}
	return 0;
}

inline void add_blossom(int xv, int xa, int xu)
{
	int b = n + 1;
	while (b <= n_x && bel[b])
		b++;
	if (b > n_x)
		n_x++;

	lab[b] = 0;
	col[b] = 0;

	mate[b] = mate[xa];

	bloch[b].clear();
	bloch[b].push_back(xa);
	for (int x = xv; x != xa; x = bel[fa[bel[mate[x]]]])
		bloch[b].push_back(x), bloch[b].push_back(bel[mate[x]]), q_push(bel[mate[x]]);
	reverse(bloch[b].begin() + 1, bloch[b].end());
	for (int x = xu; x != xa; x = bel[fa[bel[mate[x]]]])
		bloch[b].push_back(x), bloch[b].push_back(bel[mate[x]]), q_push(bel[mate[x]]);

	set_bel(b, b);

	for (int x = 1; x <= n_x; x++)
	{
		mat[b][x].w = mat[x][b].w = 0;
		blofrom[b][x] = 0;
	}
	for (int i = 0; i < size(bloch[b]); i++)
	{
		int xs = bloch[b][i];
		for (int x = 1; x <= n_x; x++)
			if (mat[b][x].w == 0 || e_delta(mat[xs][x]) < e_delta(mat[b][x]))
				mat[b][x] = mat[xs][x], mat[x][b] = mat[x][xs];
		for (int x = 1; x <= n_x; x++)
			if (blofrom[xs][x])
				blofrom[b][x] = xs;
	}
	calc_slackv(b);
}
inline void expand_blossom1(int b) // lab[b] == 1
{
	for (int i = 0; i < size(bloch[b]); i++)
		set_bel(bloch[b][i], bloch[b][i]);

	int xr = blofrom[b][mat[b][fa[b]].v];
	int pr = find(bloch[b].begin(), bloch[b].end(), xr) - bloch[b].begin();
	if (pr % 2 == 1)
	{
		reverse(bloch[b].begin() + 1, bloch[b].end());
		pr = size(bloch[b]) - pr;
	}

	for (int i = 0; i < pr; i += 2)
	{
		int xs = bloch[b][i], xns = bloch[b][i + 1];
		fa[xs] = mat[xns][xs].v;
		col[xs] = 1, col[xns] = 0;
		slackv[xs] = 0, calc_slackv(xns);
		q_push(xns);
	}
	col[xr] = 1;
	fa[xr] = fa[b];
	for (int i = pr + 1; i < size(bloch[b]); i++)
	{
		int xs = bloch[b][i];
		col[xs] = -1;
		calc_slackv(xs);
	}

	bel[b] = 0;
}
inline void expand_blossom_final(int b) // at the final stage
{
	for (int i = 0; i < size(bloch[b]); i++)
	{
		if (bloch[b][i] > n && lab[bloch[b][i]] == 0)
			expand_blossom_final(bloch[b][i]);
		else
			set_bel(bloch[b][i], bloch[b][i]);
	}
	bel[b] = 0;
}

inline bool on_found_edge(const edge &e)
{
	int xv = bel[e.v], xu = bel[e.u];
	if (col[xu] == -1)
	{
		int nv = bel[mate[xu]];
		fa[xu] = e.v;
		col[xu] = 1, col[nv] = 0;
		slackv[xu] = slackv[nv] = 0;
		q_push(nv);
	}
	else if (col[xu] == 0)
	{
		int xa = get_lca(xv, xu);
		if (!xa)
		{
			augment(xv, xu), augment(xu, xv);
			for (int b = n + 1; b <= n_x; b++)
				if (bel[b] == b && lab[b] == 0)
					expand_blossom_final(b);
			return true;
		}
		else
			add_blossom(xv, xa, xu);
	}
	return false;
}

bool match()
{
	for (int x = 1; x <= n_x; x++)
		col[x] = -1, slackv[x] = 0;

	q_n = 0;
	for (int x = 1; x <= n_x; x++)
		if (bel[x] == x && !mate[x])
			fa[x] = 0, col[x] = 0, slackv[x] = 0, q_push(x);
	if (q_n == 0)
		return false;

	while (true)
	{
		for (int i = 0; i < q_n; i++)
		{
			int v = q[i];
			for (int u = 1; u <= n; u++)
				if (mat[v][u].w > 0 && bel[v] != bel[u])
				{
					int d = e_delta(mat[v][u]);
					if (d == 0)
					{
						if (on_found_edge(mat[v][u]))
							return true;
					}
					else if (col[bel[u]] == -1 || col[bel[u]] == 0)
						update_slackv(v, bel[u]);
				}
		}

		int d = INF;
		for (int v = 1; v <= n; v++)
			if (col[bel[v]] == 0)
				tension(d, lab[v]);
		for (int b = n + 1; b <= n_x; b++)
			if (bel[b] == b && col[b] == 1)
				tension(d, lab[b] / 2);
		for (int x = 1; x <= n_x; x++)
			if (bel[x] == x && slackv[x])
			{
				if (col[x] == -1)
					tension(d, e_delta(mat[slackv[x]][x]));
				else if (col[x] == 0)
					tension(d, e_delta(mat[slackv[x]][x]) / 2);
			}

		for (int v = 1; v <= n; v++)
		{
			if (col[bel[v]] == 0)
				lab[v] -= d;
			else if (col[bel[v]] == 1)
				lab[v] += d;
		}
		for (int b = n + 1; b <= n_x; b++)
			if (bel[b] == b)
			{
				if (col[bel[b]] == 0)
					lab[b] += d * 2;
				else if (col[bel[b]] == 1)
					lab[b] -= d * 2;
			}

		q_n = 0;
		for (int v = 1; v <= n; v++)
			if (lab[v] == 0) // all unmatched vertices' labels are zero! cheers!
				return false;
		for (int x = 1; x <= n_x; x++)
			if (bel[x] == x && slackv[x] && bel[slackv[x]] != x && e_delta(mat[slackv[x]][x]) == 0)
			{
				if (on_found_edge(mat[slackv[x]][x]))
					return true;
			}
		for (int b = n + 1; b <= n_x; b++)
			if (bel[b] == b && col[b] == 1 && lab[b] == 0)
				expand_blossom1(b);
	}
	return false;
}

void calc_max_weight_match()
{
	for (int v = 1; v <= n; v++)
		mate[v] = 0;

	n_x = n;
	n_matches = 0;
	tot_weight = 0;

	bel[0] = 0;
	for (int v = 1; v <= n; v++)
		bel[v] = v, bloch[v].clear();
	for (int v = 1; v <= n; v++)
		for (int u = 1; u <= n; u++)
			blofrom[v][u] = v == u ? v : 0;

	int w_max = 0;
	for (int v = 1; v <= n; v++)
		for (int u = 1; u <= n; u++)
			relax(w_max, mat[v][u].w);
	for (int v = 1; v <= n; v++)
		lab[v] = w_max;

	while (match())
		n_matches++;

	for (int v = 1; v <= n; v++)
		if (mate[v] && mate[v] < v)
			tot_weight += mat[v][mate[v]].w;
}

int main()
{
	n = getint(), m = getint();

	for (int v = 1; v <= n; v++)
		for (int u = 1; u <= n; u++)
			mat[v][u] = edge(v, u, 0);

	for (int i = 0; i < m; i++)
	{
		int v = getint(), u = getint(), w = getint();
		mat[v][u].w = mat[u][v].w = w;
	}

	calc_max_weight_match();

	printf("%lld\n", tot_weight);
	for (int v = 1; v <= n; v++)
		printf("%d ", mate[v]);
	printf("\n");

	return 0;
}
```

## Marriage ##
```cpp
void engage(int man, int woman) {
  int m = future_husband[woman];
  if (m) {
    future_wife[m] = 0;
    q.push(m);
  }
  future_wife[man] = woman;
  future_husband[woman] = man;
}
while (!q.empty()) {
  int man = q.front();
  q.pop();
  int woman = pref[man][next[man]++];
  if (!future_husband[woman]) {
    engage(man, woman);
  } else if (order[woman][man] < order[woman][future_husband[woman]]) {
    engage(man, woman);
  } else { q.push(man); }
}
```

## Maximum Clique ##
```cpp
void dfs(BS r, BS p, BS x) {
  if ((double)clock() / CLOCKS_PER_SEC >= 1) {
    cout << ans << '\n';
    exit(0);
  }
  if (p.none() && x.none()) {
    ans = max(ans, (int)r.count());
  } else {
    if ((int)p.count() + r.count() < ans) { return; }
    int pivot = 0;
    for (; !p[pivot] && !x[pivot] && pivot < n; pivot++);
    for (int i = 0; i < n; i++) {
      if (!neighbor[pivot][i] && p[i]) {
        r[i] = true;
        dfs(r, p & neighbor[i], x & neighbor[i]);
        r[i] = false;
        p[i] = false;
        x[i] = true;
      }
    }
  }
}
```

## FFT ##
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2*262144;
typedef long double ld;
#define ld double
typedef complex<ld> cplx;
const ld PI = acos(-1);
const cplx I(0,1);
cplx omega[MAXN+1];
void pre_fft() {
	for (int i=0;i<=MAXN;i++) {
		omega[i] = exp(i*2*PI/MAXN*I);
	}
}

void fft(int n,cplx a[],bool inv=false) {
	int basic=MAXN/n;
	int theta=basic;
	for (int m=n;m>=2;m>>=1) {
		int mh=m>>1;
		for (int i=0;i<mh;i++) {
			cplx w=omega[inv?MAXN-(i*theta%MAXN):i*theta%MAXN];
			for (int j=i;j<n;j+=m) {
				int k=j+mh;
				cplx x=a[j]-a[k];
				a[j] += a[k];
				a[k] = w*x;
			}
		}
		theta = (theta*2)%MAXN;
	}
	int i=0;
	for (int j=1;j<n-1;j++) {
		for (int k=n>>1;k>(i^=k);k>>=1) ;
		if (j<i) swap(a[i],a[j]);
	}
	if (inv) {
		for (int i=0;i<n;i++) a[i]/=n;
	}
}

cplx a[MAXN],b[MAXN],c[MAXN];

//how to use : 
/*
pre_fft();


fft(n,a);
fft(n,b);
for (int i=0;n>i;i++) {
	c[i] = a[i]*b[i];
}
fft(n,c,1);
*/
```

## Gauss Elimination ##
```cpp
typedef double Matrix[maxn][maxn];
void gauss_elimination(Matrix A, int n) {
  int i, j, k, r;
  for (i = 0; i < n; i++) {
    r = i;
    for (j = i + 1; j < n; j++)
      if (fabs(A[j][i]) > fabs(A[r][i])) { r = j; }
    if (r != i) for (j = 0; j <= n; j++) { swap(A[r][j], A[i][j]); }
#define High_precision
#ifndef High_precision
    for (k = i + 1; k < n; k++) {
      DB f = A[k][i] / A[i][i];
      for (j = i; j <= n; j++) { A[k][j] -= f * A[i][j]; }
    }
#else
    for (j = n; j >= i; j--)
      for (k = i + 1; k < n; k++) {
        A[k][j] -= A[k][i] / A[i][i] * A[i][j];
      }
#endif
  }
  for (i = n - 1; i >= 0; i--) {
    for (j = i + 1; j < n; j++) { A[i][n] -= A[j][n] * A[i][j]; }
    A[i][n] /= A[i][j];
  }
}
```

## ExtGcd ##
```cpp
int extGcd(int a, int b, int *x, int *y) {
  if (!b) {
    *x = 1, *y = 0;
    return a;
  } else {
    int g = extGcd(b, a % b, x, y);
    int t = *x;
    *x = *y;
    *y = t - (a / b) * *y;
    return g;
  }
}
```

## Chinese Remainer Theorm ##
```cpp
LL china(int n) {
  LL M = 1, d, y, x = 0;
  for (int i = 0; i < n; i++) { M *= m[i]; }
  for (int i = 0; i < n; i++) {
    LL w = M / m[i];
    egcd(m[i], w, d, d, y);
    x = (x + y * w * a[i]) % M;
  }
  return (x + M) % M;
}
```

## Discrete Logarithm ##
```cpp
int log_mod(int a, int b, int n) {
  int m, v, e = 1, i;
  m = (int)sqrt(n + 0.5);
  v = inv(pow_mod(a, m, n), n);
  map<int, int> x;
  x[1] = 0;
  for (i = 1; i < m; i++) {
    e = mul_mod(e, a, n);
    if (!x.count(e)) { x[e] = i; }
  }
  for (i = 0; i < m; i++) {
    if (x.count(b)) { return i * m + x[b]; }
    b = mul_mod(b, v, n);
  }
  return -1;
}
```

## Miller-Rabin ##
2,7,61 / 2,325,9375,28178,450775,9780504,1795265022

## Pollard-Rho ##
```cpp
uint64_t pollardRho(uint64_t x) {
  int64_t a = rand() % (x - 2) + 2, b = a;
  uint64_t c = rand() % (x - 1) + 1, d = 1;
  while (d == 1) {
    a = ((__int128)a * a + c) % x;
    b = ((__int128)b * b + c) % x;
    b = ((__int128)b * b + c) % x;
    d = __gcd((uint64_t)abs(a - b), x);
    if (d == x) { return pollardRho(x); }
  }
  return d;
}
```

## Dancing Links ##
```cpp
const int maxc = 1000 + 5;
const int maxr = 10000 + 5;
const int maxnode = 10000 * 2 + 5;
struct DLX {
  int ansd, ans[maxr], n, sz, S[maxc];
  int row[maxnode], col[maxnode];
  int L[maxnode], R[maxnode], U[maxnode], D[maxnode];
  void init(int n, int m) {
    this->n = n;
    for (int i = 1; i <= m; i++) { column[i].clear(); }
    for (int i = 0; i <= n; i++) { U[i] = i, D[i] = i, L[i] = i - 1, R[i] = i + 1; }
    L[0] = n, R[n] = 0;
    sz = n + 1;
    for (int i = 0; i <= n; i++) { S[i] = 0; }
  }
  void addRow(int r, vector<int> &column) {
    int first = sz;
    for (int i = 0; i < column.size(); i++) {
      int c = column[i];
      L[sz] = sz - 1, R[sz] = sz + 1;
      D[sz] = c, U[sz] = U[c];
      D[U[c]] = sz, U[c] = sz;
      row[sz] = r, col[sz] = c;
      S[c]++;
      sz++;
    }
    L[first] = sz - 1, R[sz - 1] = first;
  }
#define FOR(i,A,st) for(int i=A[st];i!=st;i=A[i])
  void remove(int c) {
    L[R[c]] = L[c];
    R[L[c]] = R[c];
    FOR(i, D, c) FOR(j, R, i) {U[D[j]] = U[j]; D[U[j]] = D[j]; --S[col[j]];}
  }
  void restore(int c) {
    FOR(i, U, c) FOR(j, L, i) {U[D[j]] = j; D[U[j]] = j; ++S[col[j]];}
    L[R[c]] = c;
    R[L[c]] = c;
  }
  bool dfs(int d) {
    if (R[0] == 0) {
      ansd = d;
      return 1;
    }
    int c = R[0];
    FOR(i, R, 0) if (S[i] < S[c]) { c = i; }
    remove(c);
    FOR(i, D, c) {
      ans[d] = row[i];
      FOR(j, R, i) remove(col[j]);
      if (dfs(d + 1)) { return 1; }
      FOR(j, L, i) restore(col[j]);
    }
    restore(c);
    return 0;
  }
  bool solve() {
    if (!dfs(0)) { return 0; }
    return 1;
  }
} solver;
```

## Aho-Corasick Automation ##
```cpp
const int SIGMA_SIZE = 26;
int fail[1000010], last[1000010];
int ch[1000010][26];
int val[1000010];
int idx(char c) {return c - 'a';}
void getfail() {
  queue<int> q;
  fail[0] = 0;
  for (int c = 0; c < SIGMA_SIZE; c++) {
    int u = ch[0][c];
    if (u) {fail[u] = 0; q.push(u); last[u] = 0;}
  }
  while (!q.empty()) {
    int r = q.front();
    q.pop();
    for (int c = 0; c < SIGMA_SIZE; c++) {
      int u = ch[r][c];
      if (!u) { continue; }
      q.push(u);
      int v = fail[r];
      while (v && !ch[v][c]) { v = fail[v]; }
      fail[u] = ch[v][c];
      last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
    }
  }
}
void print(int j) {
  if (j) {
    printf("%d: %d\n", j, val[j]);
    print(last[j]);
  }
}
void find(char *T) {
  int n = strlen(T);
  int j = 0;
  for (int i = 0; i < n; i++) {
    int c = idx(T[i]);
    while (j && !ch[j][c]) { j = fail[j]; }
    j = ch[j][c];
    if (val[j]) { print(j); }
    else if (last[j]) { print(last[j]); }
  }
}
```

## Z Algorithm ##
```cpp
void zalg(char *str, int len) {
  int l = 0, r = 0;
  for (int i = 0; i < len; i++) {
    if (i > r) {
      l = r = i;
      while (r < len && str[r] == str[r - l]) { r++; }
      z[i] = r - l;
      r--;
    } else {
      if (z[i - l] < r - i + 1) {
        z[i] = z[i - l];
      } else {
        l = i;
        while (r < len && str[r] == str[r - l]) { r++; }
        z[i] = r - l;
        r--;
      }
    }
  }
}
```

## KMP ##
```cpp
void getfail(char *P, int *f) {
  int m = strlen(P);
  f[0] = 0, f[1] = 0;
  for (int i = 1; i < m; i++) {
    debugf("processing %d\n", i);
    int j = f[i];
    debugf("  f[%d]=%d\n", i, f[i]);
    while (j && P[i] != P[j]) {debugf("    P[%d]!=P[%d]! back to %d\n", i, j, f[j]); j = f[j];}
    f[i + 1] = (P[i] == P[j] ? j + 1 : 0);
    debugf("  finally we have f[%d]=%d\n", i + 1, f[i + 1]);
  }
}
void find(char *T, char *P, int *f) {
  int n = strlen(T), m = strlen(P);
  getfail(P, f);
  int j = 0;
  for (int i = 0; i < n; i++) {
    while (j && P[j] != T[i]) { j = f[j]; }
    if (P[j] == T[i]) { j++; }
    if (j == m) { printf("%d\n", i - m + 1); }
  }
}
```

## Suffix Array ##
```cpp
struct SuffixArray {
  char s[maxn];
  int sa[maxn], rank[maxn], pri[maxn], c[maxn], n;
  void build_sa(int m) {
    n = strlen(s);
    s[n++] = 0;
    memset(c, 0, sizeof(c));
    for (int i = 0; i < n; i++) { c[rank[i] = s[i]]++; }
    for (int i = 1; i < m; i++) { c[i] += c[i - 1]; }
    for (int i = n - 1; i >= 0; i--) { sa[--c[rank[i]]] = i; }
    for (int k = 1; k <= n; k <<= 1) {
      int p = 0;
      for (int i = n - k; i < n; i++) { pri[p++] = i; }
      for (int i = 0; i < n; i++) if (sa[i] >= k) { pri[p++] = sa[i] - k; }
      memset(c, 0, sizeof(c));
      for (int i = 0; i < n; i++) { c[rank[pri[i]]]++; }
      for (int i = 1; i < m; i++) { c[i] += c[i - 1]; }
      for (int i = n - 1; i >= 0; i--) { sa[--c[rank[pri[i]]]] = pri[i]; }
      swap(pri, rank);
      p = 1;
      rank[sa[0]] = 0;
      for (int i = 1; i < n; i++) {
        rank[sa[i]] = pri[sa[i - 1]] == pri[sa[i]] &&
          pri[sa[i - 1] + k] == pri[sa[i] + k] ? p - 1 : p++;
      }
      if (p >= n) { break; }
      m = p;
    }
  }
  int m;
  int cmp_suffix(char *pattern, int p) {
    return strncmp(pattern, s + sa[p], m);
  }
  int find(char *p) {
    m = strlen(p);
    if (cmp_suffix(p, 0) < 0) { return -1; }
    if (cmp_suffix(p, n - 1) > 0) { return -1; }
    int l = 0, r = n - 1;
    while (r >= l) {
      int mid = l + (r - l) / 2;
      int res = cmp_suffix(p, mid);
      if (!res) { return mid; }
      if (res < 0) { r = mid - 1; }
      else { l = mid + 1; }
    }
    return -1;
  }
  int height[maxn];
  void getheight() {
    int k = 0;
    for (int i = 1; i < n; i++) { rank[sa[i]] = i; }
    for (int i = 0; i < n - 1; i++) {
      if (k) { k--; }
      int j = sa[rank[i] - 1];
      while (s[i + k] == s[j + k]) { k++; }
      height[rank[i]] = k;
    }
  }
} SA;
```

## Suffix Automation ##
```cpp
const int maxnode = 1000000 + 5;
const int SIGMA_SIZE = 26;
struct Node {
  Node *fail, *ch[SIGMA_SIZE];
  int Max;
  Node() {Max = 0, fail = 0; memset(ch, 0, sizeof ch);}
} node[maxnode], *root, *last;
struct SuffixAutomaton {
  int size;
  inline int idx(char c) {return c - 'a';}
  inline void init() {size = 0; last = root = &node[0];}
  inline void add(char c) {
    c = idx(c);
    Node *p = last;
    Node *np = &node[++size];
    np->Max = p->Max + 1;
    while (p && !p->ch[c]) { p->ch[c] = np, p = p->fail; }
    if (!p) { np->fail = root; }
    else {
      Node *q = p->ch[c];
      if (q->Max == p->Max + 1) { np->fail = q; }
      else {
        Node *nq = &node[++size];
        nq->Max = p->Max + 1;
        memcpy(nq->ch, q->ch, sizeof(q->ch));
        nq->fail = q->fail;
        q->fail = np->fail = nq;
        while (p && p->ch[c] == q) { p->ch[c] = nq, p = p->fail; }
      }
    }
    last = np;
  }
} SAM;
```

## Java BigInteger ##
```java
import java.util.*;
import java.math.*;
class Main {
  public static void main (String[] args) throws java.lang.Exception {
    Scanner cin = new Scanner(System.in);
    int t = cin.nextInt();
    BigInteger b = BigInteger.valueOf(n * 10 - 1);
    /* b.{add,and,andNot,subtract,multiply,divide,divideAndRemainder,mod,remainder,modInverse,modPow,pow,gcd,max,min,or,xor}(...);
       b.{flipBit,clearBit,isProbablePrime,pow,setBit,shiftLeft,shiftRight,testBit}(...);
       b.{abs,doubleValue,toString,bitLength,bitCount,getLowestSetBit,negate,nextProbablePrime,not,signum...}();
       b.toString(radix);
       BigInteger.probablePrime(bitLength, new Random()); */
  }
}
```

## Meissel-Lehmer ##
```cpp
#define MEM1(a) memset( (a) , 0 , sizeof( (a) ) );
const int N = 320000 + 6;
const int C = 10005;
const int D = 306;
LL pi_form[N];
LL phi_form[C][D];
LL p2_form[C][D];
LL p[N];
bool prime[N];
void init() {
  MEM1(phi_form);
  MEM1(p2_form);
  prime[0] = prime[1] = 1;
  int id=1;
  for (int i=2;N>i;i++) {
    if (!prime[i]) {
      for (LL j=i*1LL*i;N>j;j+=i) prime[j] = 1;
      p[id++] = i;
    }
    pi_form[i] = pi_form[i-1] + (!prime[i]);
  }
}
LL pi(LL m);
LL p2(LL m,LL n) {
  //cout<<"p2 = "<<p2_form[m][n]<<endl;
  if (m<C && n<D && p2_form[m][n] != -1) return p2_form[m][n];
  if (p[n] == 0) return 0;
  LL ret = 0, tmp=sqrt(m);
  for (LL i=n+1;p[i] <= tmp;i++) ret += pi(m/p[i]) - pi(p[i]) + 1;
  if (m < C && n < D) p2_form[m][n] = ret;
  return ret;
}
LL phi2(LL m,LL n) {
  if (m < C && n < D && phi_form[m][n] != -1) return phi_form[m][n];
  if (!n) return m;
  if (p[n] >= m) return 1;
  if (m<C && n<D) return phi_form[m][n] =  phi2(m,n-1) - phi2(m/p[n],n-1);
  return phi2(m,n-1) - phi2(m/p[n],n-1);
}
LL pi(LL m) {
  //cout<<"pi = "<<m<<endl;
  if (m < N) return pi_form[m];
  else {
    LL n=ceil(cbrt(m));
    return phi2(m,n) + n - 1 - p2(m,n);
  }
}
//init(); cin >> n; cout << pi(n); (n <= 10^11)
```

## 2D BIT ##
``` cpp
#include <iostream>
#include <cstring>
using namespace std;

struct BIT_2D {
    static const int MAX_N = 2506;
    int bit[MAX_N][MAX_N];
    int n,m;
    void init(int n,int m) {
        this->n = n;
        this->m = m;
        memset(bit,0,sizeof(bit));
    }
    void add(int x,int y,int w) {
        for (int i=1;x>=i;i+=i&(-i)) {
            for (int j=1;y>=j;j+=(j&(-j))) {
                bit[i][j] += w;
            }
        }
    }
    int qry(int x,int y) {
        int ret=0;
        for (int i=x;i>=1;i-=i&(-i)) {
            for (int j=y;j>=1;j-=j&(-j)) {
                ret += bit[i][j];
            }
        }
        return ret;
    }
};
```

##  Circle Intersection ##
``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef double D;  //maybe long double
typedef pair<D,D> pdd;
const D eps = 1e-9;

struct Circle
{
    D x,y,r;
    pdd cen;
    Circle(){}
    Circle(D _x,D _y,D _r) : x(_x),y(_y),r(_r),cen(make_pair(_x,_y)){}
};

struct Cir_inter_type
{
    int type;
    vector<pdd> pts;
    Cir_inter_type(){}
    Cir_inter_type(int _type,vector<pdd> _pts) : type(_type),pts(_pts){}
};

#define F first
#define S second

D get_dis(pdd a,pdd b)
{
    return sqrt(pow(a.F-b.F,2) + pow(a.S-b.S,2));
}

bool eq(D a,D b)
{
    return fabs(a-b) <= eps;
}

bool les(D a,D b)
{
    return !eq(a,b) && a<b;
}

bool leq(D a,D b)
{
    return les(a,b) || eq(a,b);
}

Cir_inter_type circle_inter(Circle a, Circle b)
{
    Cir_inter_type ret;
    D dis=get_dis(a.cen,b.cen);
    if (eq(a.r+b.r,dis)) {
        //outside cut --> type 1
        D x=a.x + (b.x-a.x)*(a.r)/(a.r + b.r);
        D y=a.y + (b.y-a.y)*(a.r)/(a.r + b.r);
        vector<pdd> pts;
        pts.push_back(make_pair(x,y));
        ret = Cir_inter_type(1,pts);
    }
    else if (eq( max(a.r,b.r),min(a.r,b.r) + dis )) {
        //inside cut --> type 2
        if (a.r < b.r) swap(a,b);
        D x=a.x + (b.x - a.x)*a.r/(a.r - b.r);
        D y=a.y + (b.y - a.y)*a.r/(a.r - b.r);
        vector<pdd> pts;
        pts.push_back(make_pair(x,y));
        ret = Cir_inter_type(2,pts);
    }
    else if (les(a.r+b.r,dis)) {
        //no intersection --> type 3
        vector<pdd> pts;
        ret = Cir_inter_type(3,pts);
    }
    else if (les(min(a.r,b.r)+dis,max(a.r,b.r))) {
        //fully inside
        //if a is fully contain b, return type 4
        //if b is fully contain a, return type 5
        vector<pdd> pts;
        if (les(b.r,a.r))
        {
            ret = Cir_inter_type(4,pts);
        }
        else if (les(a.r,b.r))
        {
            ret = Cir_inter_type(5,pts);
        }
    }
    else if (les(dis,a.r + b.r)) {
        //two intersections --> type 6
        D c1=2*(b.x-a.x)*b.r;
        D c2=2*(b.y-a.y)*b.r;
        D c3=a.r*a.r-b.r*b.r-(b.x-a.x)*(b.x-a.x)-(b.y-a.y)*(b.y-a.y);
        D aa = c1*c1 + c2*c2;
        D bb = -2*c2*c3;
        D cc = c3*c3 - c1*c1;
        D sin1 = (-bb + sqrtl(bb*bb-4*aa*cc))/(2*aa);
        D sin2 = (-bb - sqrtl(bb*bb-4*aa*cc))/(2*aa);
        D aaa = c1*c1 + c2*c2;
        D bbb = -2*c1*c3;
        D ccc = c3*c3 - c2*c2;
        D cos1=(-bbb+sqrtl(bbb*bbb-4*aaa*ccc))/(aaa*2);
        D cos2=(-bbb-sqrtl(bbb*bbb-4*aaa*ccc))/(aaa*2);
        vector<pdd> pts;
        if (eq(sin1*sin1 + cos1*cos1,1.))
        {
            pts.push_back(make_pair(b.x + b.r*cos1,b.y + b.r*(sin1)));
            pts.push_back(make_pair(b.x + b.r*cos2,b.y + b.r*(sin2)));
        }
        else {
            pts.push_back(make_pair(b.x + b.r*cos1,b.y + b.r*(sin2)));
            pts.push_back(make_pair(b.x + b.r*cos2,b.y + b.r*(sin1)));
        }
        ret = Cir_inter_type(6,pts);
    }
    return ret;
}
```

## 最小平均值環 ##
``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1002;
const LL INF = (1LL<<41);
const LL INF2 = (1LL<<30);

LL adj[N][N];
LL dp[N][N];  //dp[i][j] --> from point 0 to point j threw i roads

int main()
{
    int n;
    scanf("%d",&n);
    for (int i=0;n+1>=i;i++)
    {
        for (int j=0;n+1>=j;j++)
        {
            dp[i][j] = INF;
        }
    }
    for (int i=1;n>=i;i++)
    {
        for (int j=1;n>=j;j++)
        {
            scanf("%lld",&adj[i][j]);
            if (!adj[i][j]) adj[i][j] = INF;
        }
    }
    for (int i=0;n>=i;i++)
    {
        adj[0][i] = 0;
        adj[i][0] = INF;
        if (i) dp[1][i] = 0;
    }
    for (int i=2;n+1>=i;i++)
    {
        //dp[i][j] --> i roads from 0 to j
        for (int j=0;n>=j;j++)
        {
            for (int k=0;n>=k;k++)
            {
                dp[i][j] = min(dp[i][j],dp[i-1][k] + adj[k][j]);
            }
        }
    }
    LL ansup = INF2, ansdown = 1;
    for (int i=1;n>=i;i++)
    {
        //go threw all possible i's
        LL tmpup = 0,tmpdown = 1;
        if (dp[n+1][i] == INF) continue;
        for (int j=1;n>=j;j++)
        {
            if (dp[j][i] == INF) continue;
            LL up = dp[n+1][i] - dp[j][i];
            LL down = n - j + 1;
            //up/down > tmpup/tmpdown
            if (up >= 0)
            {
                if (up * tmpdown > down * tmpup)
                {
                    tmpup = up;
                    tmpdown = down;
                }
            }
        }
        if (tmpup == 0) continue;
        //ansup/ansdown > tmpup / tmpdown
        if (ansup * tmpdown > ansdown * tmpup)
        {
            ansup = tmpup;
            ansdown = tmpdown;
        }
    }
    LL gcd = __gcd(ansup,ansdown);
    ansup /= gcd;
    ansdown /= gcd;
    if (ansup == INF2) puts("-1 -1");
    else printf("%lld %lld\n",ansup,ansdown);
}

//adj[i][j] --> cost from i to j

```

## DP 優化們 ##
``` cpp
//decision point monotone

void solve(int L,int R,int decision_L,int decision_R)
{
    if (L > R) return;
    int mid = (L+R)>>1;
    get decision_mid by looping from decision_L to decision_R
    solve(L,mid-1,decision_L,decision_mid);
    solve(mid+1,R,decision_mid,decision_R);
}

//2D/1D optimization
void solve()
{
    //K[a][b] --> decision point
    for (int len=1;n>=len;len++)
    {
        for (int i=1;n>=i;i++)
        {
            int j=i+len-1;
            if (j > n) break;
            update dp[i][j] from K[i][j-1] to K[i+1][j]
        }
    }
}
```

## Disjoint Set ##
``` cpp
struct DJS{
  int p[N], sz, rk[N];
  vector<pair<int*,int>> memo;
  vector<size_t> stk;
  void save(){
    stk.push_back(memo.size());
  }
  void undo(){
    while(memo.size() > stk.back()){
      *memo.back().first = memo.back().second;
      memo.pop_back();
    }
    stk.pop_back();
  }
  void assign(int *x, int v){
    memo.push_back({x, *x});
    *x=v;
  }
  void init(int n){
    for(int i=1; i<=n; i++){
      p[i]=i;
      rk[i]=0;
    }
    sz=n;
    memo.clear();
    stk.clear();
  }
  int f(int x){
    return x == p[x] ? x : f(p[x]);
  }
  void uni(int a, int b){
    int aa=f(a);
    int bb=f(b);
    if(aa == bb) return;
    assign(&sz, sz-1);
    if(rk[aa] > rk[bb]) swap(aa, bb);
    assign(&p[aa], bb);
    assign(&rk[bb], max(rk[bb], rk[aa]+1));
  }
} djs;

```

## longest_palindromic_substring ##
``` cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

void longest_palindromic_substring(int *z,char *s) {  //remember z = 4*size
	//s has already put something like '$'
	int n=strlen(s);
	int L=0,R=0;
	z[0]=1;
	for (int i=1;n>i;i++) {
		z[i] = (R>i) ? min(z[2*L-i],R-i) : 1;
		while (i-z[i] >= 0 && i+z[i]<n && s[i-z[i]]==s[i+z[i]]) z[i]++;
		if (i+z[i] > R) L=i,R=i+z[i];
	}
}
```

## Burnside Lemma ##
ans =  (所有置換群答案一樣的數量)/(置換群的數量)

## 樹練剖分 ##
``` cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 50006;

#define F first
#define S second

vector<int> G[N];
int pin[N],pout[N],stamp,sz[N],head[N],p[N];

int prego(int now,int par)
{
    head[now] = now;
    p[now] = par;
    sz[now] = 0;
    for (int son:G[now])
    {
        if (son == par) continue;
        sz[now] += prego(son,now);
    }
    return ++sz[now];
}

void go(int now,int par)
{
    pin[now] = ++stamp;
    sort(G[now].begin(),G[now].end(),
     [&](const int &a,const int &b)
     {
         return sz[a] > sz[b];
     });
    bool first = true;
    for (int son:G[now])
    {
        if (son == par) continue;
        go(son,now);
        if (first) head[son] = head[now];
        first = false;
    }
    pout[now] = ++stamp;
}

void HLD(int root)
{
    prego(root,root);
    go(root,root);
}

typedef pair<int,int> pii;

vector<pii> get_path(int u,int v)
{
    //u must be an ancestor of v
    //cout << "u = " << u << " , v = " << v << endl;
    vector<pii> ret;
    while (pin[u] < pin[ head[v] ])
    {
        ret.push_back(make_pair(pin[ head[v] ] , pin[v]));
        v = p[ head[v] ];
    }
    ret.push_back(make_pair( pin[u],pin[v] ));
    return ret;
}

const int P = 19;

int lca[P][N];

void build_lca_form(int n)
{
    for (int i=1;n>=i;i++)
    {
        lca[0][i] = p[i];
    }
    for (int i=1;P>i;i++)
    {
        for (int j=1;n>=j;j++)
        {
            lca[i][j] = lca[i-1][ lca[i-1][j] ];
        }
    }
}

bool is_anc(int par,int son)
{
    return pin[par] <= pin[son] && pout[son] <= pout[par];
}

int get_lca(int x,int y)
{
    if (is_anc(x,y)) return x;
    if (is_anc(y,x)) return y;
    for (int i=P-1;i>=0;i--)
    {
        if (!is_anc(lca[i][y],x))
        {
            y = lca[i][y];
        }
    }
    return p[y];
}

int cha[2*N],a[2*N];

void solve()
{
    stamp = 0;
    HLD(1);
    build_lca_form(n);
}
```

## Mo's algorithm with modification ##
``` cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int MAX_N = 5e4 + 6;
const int MAX_M = 1e6 + 6;

int cnt[MAX_M];
int s[MAX_N];

struct Query {
    int L,R,Lid,Rid,T,id;
    void give_val(int _L,int _R,int _Lid,int _Rid,int _T,int _id) {
        L = _L;
        R = _R;
        Lid = _Lid;
        Rid = _Rid;
        T = _T;
        id = _id;
    }
    bool operator<(const Query &q2) {
        if (Lid != q2.Lid) return Lid < q2.Lid;
        if (Rid != q2.Rid) return Rid < q2.Rid;
        return T < q2.T;
    }
} query[MAX_N];

struct Modify {
    int pos,ori_val,after_val;
    void give_val(int _pos,int _ori_val,int _after_val) {
        pos = _pos;
        ori_val = _ori_val;
        after_val = _after_val;
    }
} modify[MAX_N];
int ans[MAX_N];
int cur_ans;
void add(int x) {
    if (cnt[x] == 0) cur_ans++;
    cnt[x]++;
}
void sub(int x) {
    if (cnt[x] == 1) cur_ans--;
    cnt[x]--;
}
void addTime(int T,int L,int R) {
    if (L <= modify[T].pos && modify[T].pos <= R) {
        sub(s[modify[T].pos]);
        add(modify[T].after_val);
    }
    s[modify[T].pos] = modify[T].after_val;
}
void subTime(int T,int L,int R) {
    if (L <= modify[T].pos && modify[T].pos <= R) {
        sub(s[modify[T].pos]);
        add(modify[T].ori_val);
    }
    s[modify[T].pos] = modify[T].ori_val;
}
int main () {
    int n,m;
    while (scanf("%d %d",&n,&m) != EOF) {
        memset(cnt,0,sizeof(cnt));
        memset(ans,-1,sizeof(ans));
        for (int i=1;n>=i;i++) {
            scanf("%d",&s[i]);
        }
        int T=-1;
        int qid=0;
        int B = pow(max(n,m),2.0/3.0);
        if (B<=0) B=1;
        for (int i=1;m>=i;i++) {
            getchar();
            char c;
            int x,y;
            scanf("%c %d %d",&c,&x,&y);
            if (c=='Q') {
                x++;
                query[++qid].give_val(x,y,x/B,y/B,T,i);
            }
            else {
                x++;
                modify[++T].give_val(x,s[x],y);
                s[x] = y;
            }
        }
        sort(query+1,query+qid+1);
        int L=1,R=0;
        for (int i=1;qid >= i;i++) {
            if (query[i].L > query[i].R) {
                ans[query[i].id] = 0;
                continue;
            }
            while (query[i].R > R) add(s[++R]);
            while (query[i].L < L) add(s[--L]);
            while (query[i].R < R) sub(s[R--]);
            while (query[i].L > L) sub(s[L++]);
            while (query[i].T > T) addTime(++T,L,R);
            while (query[i].T < T) subTime(T--,L,R);
            ans[query[i].id] = cur_ans;
        }
        for (int i=1;m>=i;i++) {
            if (ans[i] != -1) printf("%d\n",ans[i]);
        }
    }
}
```

## Persistent Treap ##
```cpp
struct Treap {
	shared_ptr<Treap> ch[2];
	int val, pri;
	Treap(int _val): ch{NULL, NULL}, val(_val), pri(rand()) { }
	Treap(shared_ptr<Treap> a, shared_ptr<Treap> b, int _val, int _pri, bool i): val(_val), pri(_pri) {
		ch[i] = a, ch[!i] = b;
	}
	shared_ptr<Treap> insert(int v) {
		bool i = (v > val);
		auto t = ch[i] ? ch[i]->insert(v) : make_shared<Treap>(v);
		if (t->pri < pri) {
			Treap tt = *t;
			t->ch[i] = t->ch[!i], t->ch[!i] = ch[!i], t->val = val, t->pri = pri;
			return make_shared<Treap>(tt.ch[i], t, tt.val, tt.pri, i);
		} else {
			return make_shared<Treap>(t, ch[!i], val, pri, i);
		}
	}
	Treap *query(int v) {
		if (v == val) return this;
		bool i = (v > val);
		return ch[i] ? ch[i]->query(v) : nullptr;
	}
};
```
