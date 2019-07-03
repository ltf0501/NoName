//g=3,3,3
//mod=998244353,1004535809,469762049
const int g=3;
const int mod=998244353;
ll pw(ll a,int n,ll mod)
{
	ll res=1;
	while(n)
	{
		if(n&1)res=res*a%mod;
		a=a*a%mod,n>>=1;
	}
	return res;
}
ll INV(ll a,ll mod){return pw(a,mod-2,mod);}
ll mul(ll a,ll b,int mod)//O(1) 
{
	a%=mod,b%=mod;
	return (a*b-(ll)((long double)a*b/mod)*mod+mod)%mod;
}
int find_root(int p)//find primitive root
{
	int tmp=x-1;
	vector<int> v;
	for(int i=2;i<=(int)sqrt(tmp);i++)
	{
		if(tmp%i==0)v.push_back(i);
		while(tmp%i==0)tmp/=i;
	}
	for(int g=2;g<x;g++)
	{
		bool flag=1;
		for(int t : v)
			if(pw(g,(x-1)/t)==1){flag=0;break ;}
		if(flag)return g;
	}
}
struct NTT
{
	int n,rev[maxn];
	int g,mod;
	ll omega[maxn],iomega[maxn];
	void init(int n,int g,int mod)
	{
		this->n=n;
		this->g=g;
		this->mod=mod;
		int x=pw(g,(mod-1)/n);
		omega[0]=1;
		for(int i=1;i<n;i++)omega[i]=omega[i-1]*x%mod;
		iomega[n-1]=INV(omega[n-1]);
		for(int i=n-2;i>=0;i--)iomega[i]=iomega[i+1]*x%mod;
		int k=log2(n);
		for(int i=0;i<n;i++)
		{
			int t=0;
			for(int j=0;j<k;j++)if(i&(1<<j))t|=(1<<(k-j-1));
		}
	}
	void transform(vector<ll>& a,ll* omega)
	{
		for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int len=2;len<=n;len<<=1)
		{
			int mid=len>>1;
			for(int j=0;j<len;j+=len)for(int i=0;i<mid;i++)
			{
				ll t=omega[n/len*i]*a[j+mid+i]%mod;
				a[j+mid+i]=(a[j+i]-t+mod)%mod;
				a[j+i]=(a[j+i]+t)%mod;
			}
		}
	}
	void dft(vector<ll>& a)
	{
		transform(a,omega);
	}
	void idft(vector<ll>& a)
	{
		transform(a,iomega);
		ll x=INV(n,mod);
		for(inti =0;i<n;i++)a[i]=a[i]*x%mod;
	}
};
vector<ll> mul(vector<ll> a,vector<ll> b,int mod)
{
	int N=1;
	int n1=(int)a.size(),n2=(int)b.size();
	while(N<n1+n2)N<<=1;
	NTT solver;
	solver.init(N);
	solver.dft(a),solver.dft(b);
	for(int i=0;i<n;i++)a[i]=a[i]*b[i]%mod;
	idft(a);
	vector<ll> ans(n);
	for(int i=0;i<n;i++)ans[i]=a[i];
	return ans;
}
