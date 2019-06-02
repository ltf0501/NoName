#include <vector>
#include <algorithm>
#include <stdio.h>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=1e5+10;
const int C=1e6+10;
pair<int,int> p[C],m[3],temp;
int abs(int n){return n>0?n:-n;}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);	
	int n,a[N],from[N],now;
	vector<int> ans;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=0;i<C;i++)p[i]={-1,-1};
	m[0]=m[1]=m[2]={-1,-1};
	for(int i=1;i<=n;i++){
		if(m[0]==make_pair(-1,-1))p[i]={a[i],1},from[i]=0;
		else if(abs(a[m[0].F]-a[i])==1){
			if(m[1]==make_pair(-1,-1))p[i]={a[i],1},from[i]=0;
			else if(abs(a[m[1].F]-a[i])==1){
				if(m[2]==make_pair(-1,-1))p[i]={a[i],1},from[i]=0;
				else p[i]={a[i],m[2].S+1},from[i]=m[2].F;
			}
			else p[i]={a[i],m[1].S+1},from[i]=m[1].F;
		}
		else p[i]={a[i],m[0].S+1},from[i]=m[0].F;
		if(p[i].F==a[m[0].F]){
			if(p[i].S<=m[0].S)continue;
			m[0]={i,p[i].S};
		}
		else if(p[i].F==a[m[1].F]){
			if(p[i].S<=m[1].S)continue;
			m[1]={i,p[i].S};
			if(m[1].S>m[0].S){
				temp=m[1];
				m[1]=m[0];
				m[0]=temp;	
			}
		}
		else if(p[i].F==a[m[2].F]){
			if(p[i].S<=m[2].S)continue;
			m[2]={i,p[i].S};
			if(m[2].S>m[1].S){
				temp=m[2];
				m[2]=m[1];
				m[1]=temp;
			}
			if(m[1].S>m[0].S){
				temp=m[1];
				m[1]=m[0];
				m[0]=temp;
			}
		}
		else{
			if(p[i].S>m[0].S){
			m[2]=m[1];
			m[1]=m[0];
			m[0]={i,p[i].S};
			}
			else if(p[i].S>m[1].S){
				m[2]=m[1];
				m[1]={i,p[i].S};
			}
			else if(p[i].S>m[2].S){
				m[2]={i,p[i].S};
			}
		}
	}
	now=m[0].F;
	while(now>0){
		ans.PB(a[now]);
		now=from[now];
	}
	reverse(ans.begin(),ans.end());
	printf("%d\n%d",n-(int)ans.size(),ans[0]);
	for(int i=1;i<ans.size();i++)printf(" %d",ans[i]);
	printf("\n");
}
