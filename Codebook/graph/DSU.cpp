struct dsu {
        int p[maxn], sz[maxn], com;
        vector<pair<int*, int>> v_sz, v_par;
        void init(int n) {
                v_sz.clear(), v_par.clear();
                for(int i = 0; i <= n; i++) p[i] = i, sz[i] = 1;
                com = n;
        }
        int find(int x) {
                while(x != p[x]) x = p[x];
                return x;
        }
        bool merge(int x, int y) {
                x = find(x), y = find(y);
                if(x == y) return 0;

                if(sz[x] < sz[y]) swap(x, y);
                v_sz.push_back(make_pair(&sz[x], sz[x]));
                v_par.push_back(make_pair(&p[y], p[y]));

                com--;
                sz[x] += sz[y], p[y] = x;
                return 1;
        }
        void undo() {
                pair<int*, int> p_par = v_par.back();
                pair<int*, int> p_sz = v_sz.back();
                assert(v_par.size() >= 1);
                assert(v_sz.size() >= 1);
                v_par.pop_back(), v_sz.pop_back();
                *p_par.first = p_par.second;
                *p_sz.first = p_sz.second;
                com++;
        }
} dsu;
