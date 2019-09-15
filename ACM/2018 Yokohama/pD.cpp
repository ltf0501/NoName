bool debug=false;
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#define PB push_back
#define F first
#define S second
const short N=4e3+10;
pair<short,short> v[N][N][2];
short d[N][N];
short min(short a,short b){return a>b?b:a;}
short dis(short n,short m){
	if(d[n][m]>=0)return d[n][m];
	d[n][m]=N+10;
	for(pair<short,short> i:v[n][m])d[n][m]=min(d[n][m],dis(i.F,i.S)+1);
	return d[n][m];
}
int main(){
	string l,r,ans;
	short tx,ty,x=0,y=0,n,m,rnxt[N][2],lnxt[N][2];
	cin>>l>>r;
	l+=l.back();
	r+=r.back();
	n=(short)l.size();
	m=(short)r.size();
	for(short i=0;i<n;i++){
		lnxt[i][0]=lnxt[i][1]=i+1;
		while(lnxt[i][0]<n&&l[lnxt[i][0]-1]=='1')lnxt[i][0]++;
		while(lnxt[i][1]<n&&l[lnxt[i][1]-1]=='0')lnxt[i][1]++;
	}
	for(short i=0;i<m;i++){
		rnxt[i][0]=rnxt[i][1]=i+1;
		while(rnxt[i][0]<m&&r[rnxt[i][0]-1]=='1')rnxt[i][0]++;
		while(rnxt[i][1]<m&&r[rnxt[i][1]-1]=='0')rnxt[i][1]++;
	}
	for(short i=0;i<n;i++)for(short j=0;j<m;j++){
		v[i][j][0]={lnxt[i][0],rnxt[j][0]};
		v[i][j][1]={lnxt[i][1],rnxt[j][1]};
	}
	for(short i=0;i<=n;i++)for(short j=0;j<=m;j++)d[i][j]=-1;
	for(short i=0;i<n;i++){
		v[i][m][0]={lnxt[i][0],m};
		v[i][m][1]={lnxt[i][1],m};
	}
	for(short i=0;i<m;i++){
		v[n][i][0]={n,rnxt[i][0]};
		v[n][i][1]={n,rnxt[i][1]};
	}
	d[n][m]=0;
	if(debug){
	//	for(short i=0;i<n;i++)for(short j=0;j<m;j++)prshortf("dis(%d,%d)=%d\n",i,j,dis(i,j));
	}
	while(x<n||y<m){
		if(dis(v[x][y][0].F,v[x][y][0].S)<=dis(v[x][y][1].F,v[x][y][1].S)){
			tx=v[x][y][0].F,ty=v[x][y][0].S;
			x=tx;
			y=ty;
			ans+="0";
		}
		else{
			tx=v[x][y][1].F,ty=v[x][y][1].S;
			x=tx,y=ty;
			ans+="1";
		}
	}
	cout<<ans<<endl;
}
