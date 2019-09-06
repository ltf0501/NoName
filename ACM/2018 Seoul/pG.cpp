bool debug=true;
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
int64_t f(int64_t s, int64_t wa, int64_t wb, int64_t wc) {
        int64_t waa = wa * wa, wbb = wb * wb, wcc = wc * wc;
        return (2 * s * (wa * wb + wb * wc + wc * wa) - (waa * wb + wa * wbb + waa * wc + wa * wcc + wbb * wc + wb * wcc));
}
using tt = tuple<int64_t, int64_t, int64_t>;
bool cmp(tt l, tt r) {
        if (get<0>(l) * get<1>(r) == get<0>(r) * get<1>(l)) return get<2>(l) < get<2>(r);
        else return get<0>(l) * get<1>(r) < get<0>(r) * get<1>(l);
};

int main(){
        int n;
        vector<tt> v;
        cin >> n;
        for(int i=1;i<=n;i++){
                int64_t s, a[3]; cin >> s >> a[0] >> a[1] >> a[2];
                auto prob = f(s, a[0], a[1], a[2]);
                v.emplace_back(prob, s * s * s, i);
        }
        sort(v.begin(),v.end(), cmp);
        cout << get<2>(v[0]);
        for(int i=1;i<v.size();i++)cout << ' ' << get<2>(v[i]);
        cout << '\n';
}
