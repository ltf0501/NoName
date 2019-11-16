bool debug=false;
#include <assert.h>
#include <vector>
#include <stdio.h>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=2e3+10;
bool have[N];
vector<pair<int,int>> ans;
bool connect(int l,int r,int tot,bool v){
	if(debug)printf("connect(%d,%d)\n",l,r);
	bool nans=v;
	int val=(1<<l)|(1<<r);
	for(int i=tot-1;i>=0;i--)if(have[i]&&(i<(i^val)&&(i^val)<(i|val))){
		have[i]=false;
		have[i^val]=true;
		nans=true;
	}
	if(nans)ans.PB({l,r});
	if(debug&&nans)printf("now change(%d,%d)\n",l,r);
	return nans;
}
bool good(int val,int tot){
	if(val==0)return true;
	while(val%2==0)val>>=1,tot>>=1;
	if(val==(tot-1))return true;
	else return false;
}
bool canconnect(int l,int r,int tot,int to){
	if(good(to,tot)||have[to])return false;
	int val=(1<<l)|(1<<r);
	for(int i=tot-1;i>=0;i--)if(have[i]&&(i<(i^val)&&(i^val)<(i|val))&&((i^val)==to))return false;
	if(debug)printf("can %d %d\n",to,tot);
	return true;
}
bool check(int n,int now){
	int tot=1<<n,temp;
	for(int i=0;i<tot;i++)if(i!=now){
		temp=i;
		for(pair<int,int> j:ans){
			int val=(1<<j.F)|(1<<j.S);
			if(i<(i^val)&&(i^val)<(i|val))i^=val;
		}
		if(!good(i,tot))return false;
		i=temp;
	}
	return true;
}
void test(int n,int now){
int 	ori=now;
	int temp,tot=1<<n,a[N];
	bool ok,can=true;
	ans.clear();
	for(int i=0;i<tot;i++)have[i]=true;
	for(int i=0;i<n;i++)a[i]=(now&(1<<i))?1:0;
	if(good(now,tot)){
		printf("-1\n");
		return ;
	}
	have[now]=false;
	while(can){
		can=false;
		ok=true;
		while(ok){
			ok=false;
			for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(a[j]>=a[i]&&canconnect(i,j,tot,now))ok|=connect(i,j,tot,false);
		}
		for(int i=0;i<n;i++)if(a[i]==1){
			for(int j=i+1;j<n;j++)if(a[j]==0){
				//printf("now=%d i=%d j=%d\n",now,i,j);
				if(canconnect(i,j,tot,now^(1<<i)^(1<<j))){
				can=true;
				now^=(1<<i)^(1<<j);
				a[i]=0;
				a[j]=1;
				connect(i,j,tot,true);
				break;
			}
			//if(can)break;
			}
		}
	}
	ok=true;
	for(int i=0;i<tot;i++)if(have[i]&&(!good(i,tot))){
		ok=false;
		break;
	}
	if(ok){
		printf("OK\n");
		assert(check(n,ori));
	}
	else{
		if(debug){
		//	printf("%d\n",(int)ans.size());
		//	for(pair<int,int> i:ans)printf("%d %d\n",i.F+1,i.S+1);
		//	for(int i=0;i<tot;i++)printf("have[%d]=%d\n",i,have[i]?1:0);
		}
		printf("NO -1\n");
		printf("%d\n",n);
		for(int i=0;i<n;i++)printf("%d ",a[i]);
		printf("\n");
		int x;scanf("%d",&x);
	}
	return ;	
}
void solve(int n){
	int temp,now=0,ori,tot=1<<n,a[N];
	bool ok,can=true;
	ans.clear();
	for(int i=0;i<tot;i++)have[i]=true;
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	for(int i=0;i<n;i++)if(a[i]==1)now|=1<<i;
	if(good(now,tot)){
		printf("-1\n");
		return ;
	}
	ori=now;
	have[now]=false;
	while(can){
		can=false;
		ok=true;
		while(ok){
			ok=false;
			for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(a[j]>=a[i]&&canconnect(i,j,tot,now))ok|=connect(i,j,tot,false);
		}
		for(int i=0;i<n;i++)if(a[i]==1){
			for(int j=i+1;j<n;j++)if(a[j]==0){
				//printf("now=%d i=%d j=%d\n",now,i,j);
				if(canconnect(i,j,tot,now^(1<<i)^(1<<j))){
				can=true;
				now^=(1<<i)^(1<<j);
				a[i]=0;
				a[j]=1;
				connect(i,j,tot,true);
				break;
			}
			//if(can)break;
			}
		}
	}
	ok=true;
	for(int i=0;i<tot;i++)if(have[i]&&(!good(i,tot))){
		ok=false;
		break;
	}
	if(ok){
		printf("%d\n",(int)ans.size());
		for(pair<int,int> i:ans)printf("%d %d\n",i.F+1,i.S+1);
		//assert(check(n,ori));
	}
	else{
		if(debug){
			printf("%d\n",(int)ans.size());
			for(pair<int,int> i:ans)printf("%d %d\n",i.F+1,i.S+1);
			for(int i=0;i<tot;i++)printf("have[%d]=%d\n",i,have[i]?1:0);
		}
		printf("-1\n");
	}
	return ;
}
int main(){
	if(!debug){
		freopen("comparator.in","r",stdin);
		freopen("comparator.out","w",stdout);
	}
	
	if(debug)for(int i=2;i<=10;i++){
		int tot=1<<i;
		for(int j=0;j<tot;j++)test(i,j);
	}
	int n;
	while(true){
		scanf("%d",&n);
		if(n==0)break;
		else solve(n);
	}
}
