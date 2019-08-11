#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    int n; cin >> n;
    queue<int> q;
    multiset<int> st;
    while (n--) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x;
            q.push(x);
            st.insert(x);
        } else {
            auto it = st.find(q.front());
            st.erase(it);
            q.pop();
        }
        cout << (st.size() ? *st.rbegin() : 0) << '\n';
    }
}
