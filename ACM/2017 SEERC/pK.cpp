#include <vector>
#include <stdio.h>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=1e5+10;
const int INF=1e9+10;
struct seg_tree{
	vector<pair<int,int>> v;
	vector<int> flag;
	pair<int,int> min(pair<int,int> a,pair<int,int> b){
		if(a.F<b.F)return a;
		else if(b.F<a.F)return b;
		else if(a.S<b.S)return a;
		else return b;
	}
	void pull(int n){
		v[n]=min(v[n*2+1],v[n*2+2]);
		return ;
	}
	void addtag(int n,int x){
		v[n].F+=x;
		flag[n]+=x;
		return ;
	}
	void push(int n){
		if(flag[n]!=0){
			addtag(n*2+1,flag[n]);
			addtag(n*2+2,flag[n]);
			flag[n]=0;
		}
		return ;
	}
	void init(int n,int l,int r,int a[]){
		if(v.size()<=n){
			v.resize(n+1);
			flag.resize(n+1);
		}
		flag[n]=0;
		if(l==r)v[n]={a[l],l};
		else{
			int mid=(l+r)>>1;
			init(n*2+1,l,mid,a);
			init(n*2+2,mid+1,r,a);
			pull(n);
		}
		return ;
	}
	void fix(int n,int l,int r,int L,int R,int x){
		if(L<=l&&r<=R)addtag(n,x);
		else if(!(L>r||l>R)){
			int mid=(l+r)>>1;
			push(n);
			fix(n*2+1,l,mid,L,R,x);
			fix(n*2+2,mid+1,r,L,R,x);
			pull(n);
		}
		return ;
	}
};
int main(){
	seg_tree sg;
	int n,a[N],ans[N],pos;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sg.init(0,1,n,a);
	for(int i=n;i>=1;i--){
		pos=sg.v[0].S;
		ans[pos]=i;
		sg.fix(0,1,n,pos,pos,INF);
	}
	printf("%d",ans[1]);
	for(int i=2;i<=n;i++)printf(" %d",ans[i]);
	printf("\n");
}
