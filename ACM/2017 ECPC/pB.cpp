// badry O (N log N)
#include <bits/stdc++.h>
#include <tr1/unordered_map>
typedef long long ll;
#define T pair<pair<int,int>,int>
#define mk make_pair
#define in(i) scanf("%d",&i)
#define in2(i,j) scanf("%d%d",&i,&j)
#define sc(s) scanf("%s",s)
#define fi(ss) freopen (ss,"r",stdin)
#define fo(ss) freopen (ss,"w",stdout)
using namespace std;
const int MAXLEN = 100000+5;
struct state {
    int len, link;
    map<char,int>next;
};
struct SA {
    state st[MAXLEN * 2];
    int sz, last;

    void sa_init() {
        sz = last = 0;
        st[0].len = 0;
        st[0].link = -1;
        st[0].next.clear();
        ++sz;
    }

    void sa_extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        st[cur].next.clear();
        int p;
        for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
            st[p].next[c] = cur;
        if (p == -1)
            st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                for (; p != -1 && st[p].next[c] == q; p = st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};
SA sa;
char s1 [MAXLEN];
char s2 [MAXLEN];
int cnt [MAXLEN];
int maxL [MAXLEN];
long long res[MAXLEN];
vector<T> q;
ll tree [4*MAXLEN];
ll lazy [4*MAXLEN];
// normal RSQ segTree with lazy propagation

#define SZ(x,y) ((y)-(x)+1)
void push(int i,int s,int e){
	int mid=(s+e)>>1;
	tree[i<<1]+=lazy[i]*SZ(s,mid);
	tree[i<<1|1]+=lazy[i]*SZ(mid+1,e);
	lazy[i<<1]+=lazy[i];
	lazy[i<<1|1]+=lazy[i];
	lazy[i]=0;
}
void build (int i,int s,int e){
	if (s==e){
		tree[i]=maxL[s];
		return ;
	}
	int mid=(s+e)>>1;
	build(i<<1,s,mid);
	build(i<<1|1,mid+1,e);
	tree[i]=tree[i<<1]+tree[i<<1|1];
}

void upd (int i,int s,int e,int s1,int e1){ // decrement range [s1,e1] by 1
	if (s>e1 || e<s1) return ;
	if (s>=s1 && e<=e1){
		tree[i]-=SZ(s,e);
		lazy[i]--;
		return ;
	}
	push(i,s,e);
	int mid=(s+e)>>1;
	upd(i<<1,s,mid,s1,e1);
	upd(i<<1|1,mid+1,e,s1,e1);
	tree[i]=tree[i<<1]+tree[i<<1|1];

}

ll qur (int i,int s,int e,int s1,int e1){
	if (s>e1 || e<s1) return 0;
	if (s>=s1 && e<=e1){
		return tree[i];
	}
	push(i,s,e);
	int mid=(s+e)>>1;
	return qur (i<<1,s,mid,s1,e1) + qur(i<<1|1,mid+1,e,s1,e1);

}
void clean(int n){
	for (int i=0; i <=n;i++)cnt[i]=maxL[i]=0;
	for (int i=0; i <=4*n;i++)tree[i]=lazy[i]=0;
	q.clear();
}

int main (){
    freopen("curse.in", "r", stdin);
    	int cases;
	assert(in(cases)>0);
	assert(cases > 0);
	for (int c =1;c<=cases;c++){
	assert(sc(s1)>0);
	assert(sc(s2)>0);
	int n=strlen(s1),m=strlen(s2);
	assert(n>0 && n<=100000 && m>0 && m<=100000);
	clean(n);
	int Q;
	in(Q);
	assert(Q<=100000);
	int x,y;
	for (int i=0;i<Q;i++){
		in2(x,y);
		assert(x>=1 && x<=n && y>=x && y<=n);
		x--;y--; // I consider the input  1-based
		q.push_back(mk(mk(x,y),i));
	}
	sort(q.begin(),q.end());
	// build suffix automaton for the second string
	sa.sa_init();
	for (int i=0;i<m;i++)sa.sa_extend(s2[i]);
	// for each position pos in s1  find the longest substring that end at pos and is substring of s2
	int l=0,v=0;
	for (int i=0;i<n;i++){
		while (l>0 && !sa.st[v].next.count(s1[i])){
			v=sa.st[v].link;
			l=sa.st[v].len;
		}
		if (sa.st[v].next.count(s1[i])){
			l++;
			v=sa.st[v].next[s1[i]];
		}
		maxL[i]=l;
		cnt[i-l+1]++;
		cnt[i+1]--;
	}
	for (int i=1;i<n;i++)cnt[i]+=cnt[i-1]; // now for each position in s1 we know how many substring contains it and is substring in s2
	build(1,0,n-1);
    int last=0;
    for (auto it : q){
    	x=it.first.first;
    	y=it.first.second;
    	while (last<x){
    		if (cnt[last]>0) upd(1,0,n-1,last,last+cnt[last]-1);
    		last++;
    	}
    	res[it.second]=qur(1,0,n-1,x,y);
    }
    printf("Case %d:\n",c);
    for (int i=0;i<Q;i++)printf("%I64d\n",res[i]);

	}

}
