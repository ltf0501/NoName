struct MaxClique{//0-base
	ll nb[100],n,ans,one=1;
	ll lowbit(ll x){
		if(x&((one<<60)-1)) return __builtin_ffsll(x&((one<<60)-1))-1;
		return __builtin_ffsll(x>>60)+59;
	}
	ll count_bit(ll x){
		return __builtin_popcountll(x>>60)+__builtin_popcountll(x&((one<<60)-1));
	}
	void B(ll r,ll p,ll x,ll cnt,ll res){
		if(cnt+res<ans) return;
		if(p==0&&x==0){
			if(cnt>ans) ans=cnt;
			return;
		}
		ll q=p&(~nb[lowbit(p|x)]);
		while(q){
			ll i=lowbit(q),j=q&-q;
			B(r|j,p&nb[i],x&nb[i],cnt+one,count_bit(p&nb[i]));
			q&=~j,p&=~j,x|=j;
		}
	}
	int solve(){
		ll _set=0;
		ans=0,_set=(one<<n)-1;
		B(0,_set,0,0,n);
		return ans;
	}
	void add_edge(ll _u,ll _v){
		nb[_u]|=(one<<_v),nb[_v]|=(one<<_u);
	}
	void init(ll _n){n=_n;
		for(int i=0;i<n;++i) nb[i]=0;
	}
}mc;
