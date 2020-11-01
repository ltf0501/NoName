#include <bits/stdc++.h>
using namespace std;

#define PB push_back

int count(string s) {
    int n = int(s.size());
    if (n == 6) {
        for (int i = 1; i < n; i++) if (s[i] == 'g' && s[i - 1] == 'n') return 2;
        for (int i = 1; i < n; i++) if (s[i] == 'y' && s[i - 1] == 'n') return 2;
    }
    else if (n == 3) {
        if (s[0] == 'a' || s[0] == 'e' || s[0] == 'i' || s[0] == 'o' || s[0] == 'u') return 2;
    }

    if (n >= 6) return 3;
    else if (n >= 4) return 2;
    else return 1;
}

struct Verse {
    vector<string> v;
    Verse() {}
    Verse (string s) {
        stringstream ss(s);
        string word;
        while (ss >> word) {
            if (word.back() == '.') word.pop_back(); // HACK
            if (!word.empty()) v.PB(word);
        }
    }
    int syllable() {
        int ans = 0;
        for (string i : v) ans += count(i);
        return ans;
    }
    string rythm() {
        string s, tmp;
        tmp = v.back();
        s += tmp[tmp.size() - 2];
        s += tmp.back();
        return s;
    }
    void out() {
        for (string i : v) cerr << i << " ";
        cerr << '\n';
    }
};

void solve() {
    int a = 0, b = 0, c = 0, d = 0, n, tt;
    string s, tmp;
    vector<Verse> v;
    bool finish = false;
    while (!finish) {
        getline(cin, tmp);
        s += " " + tmp;
        if (s.back() == '.') finish = true;
    }
    for (char &c : s) {
        if (isalpha(c)) c = tolower(c);
    }
    //cerr << s << '\n';
    stringstream ss(s);
    string line;
    while (getline(ss, line, ',')) {
        v.emplace_back(line);
        //v.back().out();
    }

    for (int i = 0; i < min(4, int(v.size())); i++) {
        tt = v[i].syllable();
        if (8 <= tt && tt <= 12) a += 10;
    }

    

    if (v.size() > 2) {
        if (v[0].syllable() == v[2].syllable()) c += 10;
        if (v[0].rythm() == v[2].rythm()) b += 20;
    }
    if (v.size() > 3) {
        if (v[1].syllable() == v[3].syllable()) c += 10;
        if (v[1].rythm() == v[3].rythm()) b += 20;
    }

    if (v.size() >= 4) d = (int(v.size()) - 4) * 10;

    cout << " " << a << " " << b << " " << c << " " << d << " " << a + b + c - d << '\n';
}

int main() {
    int t;
    string s;
    cin >> t;
    getline(cin, s);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ":";
        solve();
    }
}
