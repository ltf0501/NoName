#include <algorithm>
#include <stdio.h>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
void acc(pair<long long int,long long int> a,long long int &speed,long long int &dist){
	dist+=(speed*2+(a.F*a.S))*a.S;
	speed+=a.F*a.S;
	return ;
}
int main(){
	int n;
	long long int nspeed=0,ndist=0,speed=0,dist=0;
	vector<pair<long long int,long long int>> v;
	pair<long long int,long long int> temp;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&temp.F,&temp.S);
		v.PB(temp);
	}
	for(pair<long long int,long long int> i:v)acc(i,nspeed,ndist);
	sort(v.begin(),v.end());
	reverse(v.begin(),v.end());
	for(pair<long long int,long long int> i:v)acc(i,speed,dist);
	dist-=ndist;
	if(dist&1)printf("%lld.5\n",dist/2);
	else printf("%lld.0\n",dist/2);
}
