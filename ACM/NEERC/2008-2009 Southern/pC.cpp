#include <utility>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define PB push_back
#define F first
#define S second
const int N=3e5+10;
int a[N<<2],f[N<<2];
void init(int n,int l,int r){
	a[n]=f[n]=0;
	if(r>l){
		int mid=(l+r)>>1;
		init(n*2+1,l,mid);
		init(n*2+2,mid+1,r);
	}
	return ;
}
void fix(int n,int l,int r,int L,int R,int x){
	if(L<=l&&r<=R){
		a[n]+=x;
		f[n]+=x;
	}
	else if(!(l>R||L>r)){
		int mid=(l+r)>>1;
		if(f[n]!=0){
			a[n*2+1]+=f[n];
			a[n*2+2]+=f[n];
			f[n*2+1]+=f[n];
			f[n*2+2]+=f[n];
			f[n]=0;
		}
		fix(n*2+1,l,mid,L,R,x);
		fix(n*2+2,mid+1,r,L,R,x);
	}
	return ;
}
int query(int n,int l,int r,int pos){
	if(l==r)return a[n];
	else{
		int mid=(l+r)>>1;
		if(f[n]!=0){
			a[n*2+1]+=f[n];
			a[n*2+2]+=f[n];
			f[n*2+1]+=f[n];
			f[n*2+2]+=f[n];
			f[n]=0;
		}
		if(pos<=mid)return query(n*2+1,l,mid,pos);
		else return query(n*2+2,mid+1,r,pos);
	}
}
int main(){
	int n,k;
	long long int l,r,w,tl,tr;
	vector<long long int> x,y;
	vector<int>ans;
	vector<pair<pair<long long int,long long int>,long long int>>v;
	vector<pair<pair<int,int>,pair<int,int>>>q;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&tl,&tr,&w);
		l=tl+tr;
		r=tl-tr;
		v.PB({{l,r},w});
		x.PB(l);
		x.PB(l+w);
		x.PB(l-w);
		y.PB(r);
		y.PB(r-w);
		y.PB(r+w);
	}
	sort(x.begin(),x.end());
	sort(y.begin(),y.end());
	x.resize(unique(x.begin(),x.end())-x.begin());
	y.resize(unique(y.begin(),y.end())-y.begin());
	for(int i=0;i<n;i++){
		q.PB({{lower_bound(x.begin(),x.end(),v[i].F.F-v[i].S)-x.begin(),-1},{lower_bound(y.begin(),y.end(),v[i].F.S-v[i].S)-y.begin(),lower_bound(y.begin(),y.end(),v[i].F.S+v[i].S)-y.begin()}});
		q.PB({{lower_bound(x.begin(),x.end(),v[i].F.F+v[i].S)-x.begin(),1},q.back().S});
		q.PB({{lower_bound(x.begin(),x.end(),v[i].F.F)-x.begin(),0},{lower_bound(y.begin(),y.end(),v[i].F.S)-y.begin(),i+1}});
		//v[i].F={lower_bound(x.begin(),x.end(),v[i].F.F)-x.begin(),lower_bound(y.begin(),y.end(),v[i].F.S)-y.begin()};
	}
	sort(q.begin(),q.end());
	init(0,0,y.size());
	for(int i=0;i<q.size();i++){
		//printf("q[%d]=((%d,%d),(%d,%d))\n",i,q[i].F.F,q[i].F.S,q[i].S.F,q[i].S.S);
		if(q[i].F.S==0){
			if(query(0,0,y.size(),q[i].S.F)>=k+1)ans.PB(q[i].S.S);
			//printf("%d %d\n",q[i].S.S,query(0,0,y.size(),q[i].S.F));
		}
		else{
			fix(0,0,y.size(),q[i].S.F,q[i].S.S,-q[i].F.S);
		}
	}
	sort(ans.begin(),ans.end());
	if(ans.empty())printf("0\n");
	else{
		printf("%d\n%d",(int)ans.size(),ans[0]);
		for(int i=1;i<ans.size();i++)printf(" %d",ans[i]);
		printf("\n");
	}
}
