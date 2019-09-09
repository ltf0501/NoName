#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-7;
const int N = 150;
#define F first
#define S second
double myabs(double x){return x>=0?x:-x;}
double point_to_line(pair<double,double> p,double A,double B,double C){
    return myabs((A*p.F+B*p.S-C)/sqrt(A*A+B*B));
}
pair<double,double> intersect(double A1,double B1,double C1,double A2,double B2,double C2){
    double x,y,det;
    x=(C1*B2-C2*B1);
    y=(A1*C2-A2*C1);
    det=(A1*B2-A2*B1);
    return {x/det,y/det};
}
bool parr(double A1,double B1,double C1,double A2,double B2,double C2){
    return fabs(A1*B2 - B1*A2) < eps;
}
double dis(pair<double, double> x, pair<double, double> y) {
    return sqrt((x.F - y.F) * (x.F - y.F) + (x.S - y.S) * (x.S - y.S));
}
double aa[3], bb[3], cc[3];
int cnt;
int main(){
    int n;
    pair<double,double> q[N][2];
    double A[N],B[N],C[N];
    scanf("%d",&n);
    if(n <= 2) return 0 * puts("Many");
    for(int i=0;i<n;i++)scanf("%lf%lf%lf%lf",&q[i][0].F,&q[i][0].S,&q[i][1].F,&q[i][1].S);
    for(int i=0;i<n;i++){
        A[i]=q[i][0].S-q[i][1].S;
        B[i]=q[i][1].F-q[i][0].F;
        C[i]=A[i]*q[i][0].F+B[i]*q[i][0].S;
    }
    if(n == 3) {
        if(parr(A[0], B[0], C[0], A[1], B[1], C[1]) && parr(A[1], B[1], C[1], A[2], B[2], C[2])) return 0 * puts("None");
        else {
            if(parr(A[0], B[0], C[0], A[1], B[1], C[1])) return 0 * puts("Many");   
            pair<double, double> p[3];
            p[0] = intersect(A[0], B[0], C[0], A[1], B[1], C[1]);
            p[1] = intersect(A[1], B[1], C[1], A[2], B[2], C[2]);
            p[2] = intersect(A[2], B[2], C[2], A[0], B[0], C[0]);
            double a = dis(p[1], p[2]), b = dis(p[2], p[0]), c = dis(p[0], p[1]);
            if(fabs(a) < eps && fabs(b) < eps && fabs(c) < eps) printf("%.9f %.9f\n", p[0].F, p[0].S);
            else puts("Many");
            return 0;
        }
    }
    for(int i = 0; i < n; i++) {
        bool flag = 1;
        for(int j = 0; j < cnt; j++) if(parr(aa[j], bb[j], cc[j], A[i], B[i], C[i])) flag = 0;
        if(flag) {
            aa[cnt] = A[i], bb[cnt] = B[i], cc[cnt] = C[i];
            cnt++;
        }
        if(cnt == 3) break;
    }
    if(cnt == 1) return 0 * puts("None");
    if(cnt == 2) {
        if(n >= 5) return 0 * puts("None");
        double Aa[2][5], Bb[2][5], Cc[2][5];
        int cnt0 = 0, cnt1 = 0;
        for(int i = 0; i < n; i++) {
            if(parr(aa[0], bb[0], cc[0], A[i], B[i], C[i])) {
                Aa[0][cnt0] = A[i], Bb[0][cnt0] = B[i], Cc[0][cnt0] = C[i];
                cnt0++;
            }
            else {
                Aa[1][cnt1] = A[i], Bb[1][cnt1] = B[i], Cc[1][cnt1] = C[i];
                cnt1++;
            }
        }
        if(cnt0 <= 1 || cnt1 <= 1) return 0 * puts("None");
        pair<double, double> p0 = intersect(Aa[0][0], Bb[0][0], Cc[0][0], Aa[1][0], Bb[1][0],Cc[1][0]); 
        pair<double, double> p1 = intersect(Aa[0][1], Bb[0][1], Cc[0][1], Aa[1][1], Bb[1][1],Cc[1][1]); 
        pair<double, double> tmp = make_pair((p0.F + p1.F) / 2, (p0.S + p1.S) / 2);
        double d = point_to_line(tmp, A[0], B[0], C[0]);
        bool flag = 1;
        for(int i = 0; i < n; i++) 
            if(fabs(d - point_to_line(tmp, A[i], B[i], C[i])) >= eps) flag = 0;
        if(flag) printf("%.9f %.9f\n", tmp.F, tmp.S);
        else puts("None");
        return 0;
    }
    pair<double, double> p[3];
    p[0] = intersect(aa[0], bb[0], cc[0], aa[1], bb[1], cc[1]);
    p[1] = intersect(aa[1], bb[1], cc[1], aa[2], bb[2], cc[2]);
    p[2] = intersect(aa[2], bb[2], cc[2], aa[0], bb[0], cc[0]);
    double a = dis(p[1], p[2]), b = dis(p[2], p[0]), c = dis(p[0], p[1]);
    vector<pair<double, double>> candidate, ans;
    if(fabs(a) < eps && fabs(b) < eps && fabs(c) < eps) candidate.push_back(p[0]);
    else {
    candidate.push_back(make_pair((a * p[0].F + b * p[1].F + c * p[2].F) / (a + b + c), (a * p[0].S + b * p[1].S + c * p[2].S) / (a + b + c)));
    candidate.push_back(make_pair((-a * p[0].F + b * p[1].F + c * p[2].F) / (-a + b + c), (-a * p[0].S + b * p[1].S + c * p[2].S) / (-a + b + c)));
    candidate.push_back(make_pair((a * p[0].F - b * p[1].F + c * p[2].F) / (a - b + c), (a * p[0].S - b * p[1].S + c * p[2].S) / (a - b + c)));
    candidate.push_back(make_pair((a * p[0].F + b * p[1].F - c * p[2].F) / (a + b - c), (a * p[0].S + b * p[1].S - c * p[2].S) / (a + b - c)));
    }
    for(auto p : candidate) {
//      cout << p.F << ' ' << p.S << '\n';
        double d = point_to_line(p, aa[0], bb[0], cc[0]);
        bool flag = 1;
        for(int i = 0; i < n; i++)
            if(fabs(d - point_to_line(p, A[i], B[i], C[i])) >= eps) flag = 0;
        if(flag) ans.push_back(p);
    }
    if((int)ans.size() == 1) printf("%.9f %.9f\n", ans[0].F, ans[0].S);
    else if(ans.empty()) puts("None");
    else puts("Many");
}
