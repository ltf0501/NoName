inline long long mod_mul(long long a,long long b,long long m){
	a%=m,b%=m;
	long long y=(long long)((double)a*b/m+0.5);/* fast for m < 2^58 */
	long long r=(a*b-y*m)%m;
	return r<0?r+m:r;
}
template<typename T>
inline T pow(T a,T b,T mod){//a^b%mod
	T ans=1;
	for(;b;a=mod_mul(a,a,mod),b>>=1)
		if(b&1)ans=mod_mul(ans,a,mod);
	return ans;
}
int sprp[3]={2,7,61};//int½d³ò¥i¸Ñ
int llsprp[7]={2,325,9375,28178,450775,9780504,1795265022};//¦Ü¤Öunsigned long long½d³ò
template<typename T>
inline bool isprime(T n,int *sprp,int num){
	if(n==2)return 1;
	if(n<2||n%2==0)return 0;
	int t=0;
	T u=n-1;
	for(;u%2==0;++t)u>>=1;
	for(int i=0;i<num;++i){
		T a=sprp[i]%n;
		if(a==0||a==1||a==n-1)continue;
		T x=pow(a,u,n);
		if(x==1||x==n-1)continue;
		for(int j=1;j<t;++j){
			x=mod_mul(x,x,n);
			if(x==1)return 0;
			if(x==n-1)break;
		}
		if(x==n-1)continue;
		return 0;
	}
	return 1;
}
