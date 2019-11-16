#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
map<string,int> color;
map<string,int> m;
int main(){
    int now=0;
    string s;
    vector<int> a(8);
    for(int i=0;i<8;i++){
        cin>>s;
        if(m.find(s)==m.end())m[s]=now++;
        a[i]=m[s];
    }
    unordered_set<int64_t> st;
    do {
        vector<int64_t> vec;
        auto bkup_a = a;
        for (int i = 0; i < 4; i++) {
            vector<int> b = {a[7], a[6], a[1], a[0], a[3], a[2], a[5], a[4]};
            a = b;
            for (int k = 0; k < 4; k++) {
                vector<int> b = {a[3], a[0], a[1], a[2], a[5], a[6], a[7], a[4]};
                a = b;
                int64_t xx = 0;
                for (int j = 0; j < 8; j++) xx = xx * 8 + a[j];
                vec.push_back(xx);
            }
            int64_t xx = 0;
            for (int j = 0; j < 8; j++) xx = xx * 8 + a[j];
            vec.push_back(xx);
        }
        for (int i = 0; i < 4; i++) {
            vector<int> b = {a[7], a[0], a[3], a[4], a[5], a[2], a[1], a[6]};
            a = b;
            for (int k = 0; k < 4; k++) {
                vector<int> b = {a[3], a[0], a[1], a[2], a[5], a[6], a[7], a[4]};
                a = b;
                int64_t xx = 0;
                for (int j = 0; j < 8; j++) xx = xx * 8 + a[j];
                vec.push_back(xx);
            }
            int64_t xx = 0;
            for (int j = 0; j < 8; j++) xx = xx * 8 + a[j];
            vec.push_back(xx);
        }
        for (int i = 0; i < 4; i++) {
            vector<int> b = {a[3], a[0], a[1], a[2], a[5], a[6], a[7], a[4]};
            a = b;
            int64_t xx = 0;
            for (int j = 0; j < 8; j++) xx = xx * 8 + a[j];
            vec.push_back(xx);
        }
        st.insert(*min_element(vec.begin(), vec.end()));
        a = bkup_a;
    } while (next_permutation(a.begin(), a.end()));
    cout << st.size() << '\n';
}
