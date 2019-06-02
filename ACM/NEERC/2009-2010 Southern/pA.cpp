#include <iostream>
using namespace std;
const int N=1e2+10;
int min(int a,int b){return a>b?b:a;}
int max(int a,int b){return a>b?a:b;}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string s[N],w;
	int n,m,val[N][N],x=1,ans=0,nx,ny,y=1,pos=0,dirx[4]={0,1,0,-1},diry[4]={1,0,-1,0};
	bool went[N][N];
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>s[i];
	cin>>w;
	n++;m++;
	for(int i=0;i<=n;i++)for(int j=0;j<=m;j++)val[i][j]=0,went[i][j]=false;
	n--;m--;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)val[i][j]=s[i-1][j-1]-'0';
	for(char i:w){
		if(i=='L')pos--;
		else if(i=='R')pos++;
		else{
			pos%=4;
			if(pos<0)pos+=4;
			nx=x+dirx[pos];
			ny=y+diry[pos];
			if(x==nx){
				ans+=val[x][min(y,ny)];
				if(!went[x][min(y,ny)])went[x][min(y,ny)]=true,val[x][min(y,ny)]>>=1;
				ans+=val[x-1][min(y,ny)];
				if(!went[x-1][min(y,ny)])went[x-1][min(y,ny)]=true,val[x-1][min(y,ny)]>>=1;
			}
			else {
				ans+=val[min(x,nx)][y];
				if(!went[min(x,nx)][y])went[min(x,nx)][y]=true,val[min(x,nx)][y]>>=1;
				ans+=val[min(x,nx)][y-1];
				if(!went[min(x,nx)][y-1])went[min(x,nx)][y-1]=true,val[min(x,nx)][y-1]>>=1;
			}
			x=nx;y=ny;
		}
	}
	printf("%d\n",ans);
	
}
