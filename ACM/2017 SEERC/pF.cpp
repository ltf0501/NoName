#include <iostream>
#include <utility>
#include <queue>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=5e3+10;
long long int min(long long int a,long long int b){return a>b?b:a;}
long long int solve(priority_queue<int> one,priority_queue<int,vector<int>,greater<int>> b,long long int ncost){
	long long int ans=0;
	int nxt;
	while(!one.empty()){
		nxt=one.top();
		one.pop();
		ncost-=nxt;
		ans+=ncost;
	}
	while(!b.empty()){
		nxt=b.top();
		b.pop();
		ncost+=nxt;
		ans+=ncost;
	}
	return ans;
}
int main(){
	string a,b;
	int n,nxt,c[N];
	long long int cost=0,ans=0;
	priority_queue<int> ones,onetoone;
	priority_queue<int,vector<int>,greater<int>> zero;
	cin>>n;
	for(int i=0;i<n;i++)cin>>c[i];
	cin>>a>>b;
	for(int i=0;i<n;i++)if(a[i]=='1'&&b[i]=='0'){
		cost+=c[i];
		ones.push(c[i]);
	}
	else if(a[i]=='1'&&b[i]=='1'){
		cost+=c[i];
		onetoone.push(c[i]);
	}
	else if(a[i]=='0'&&b[i]=='1')zero.push(c[i]);
	ans=solve(ones,zero,cost);
	while(!onetoone.empty()){
		nxt=onetoone.top();
		onetoone.pop();
		ones.push(nxt);
		zero.push(nxt);
		ans=min(ans,solve(ones,zero,cost));
	}
	cout<<ans<<endl;
}
