#include <iostream>
using namespace std;
const int N=1e2+10;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string s[N];
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>s[i];
	for(int i=0;i<n;i++)for(int j=0;j<m;j++){
		if(s[i][j]>'0'){
			ans+=2;
			if(i==0)ans+=s[i][j]-'0';
			else if(s[i][j]>s[i-1][j])ans+=s[i][j]-s[i-1][j];
			if(j==0)ans+=s[i][j]-'0';
			else if(s[i][j]>s[i][j-1])ans+=s[i][j]-s[i][j-1];
			if(i==n-1)ans+=s[i][j]-'0';
			else if(s[i][j]>s[i+1][j])ans+=s[i][j]-s[i+1][j];
			if(j==m-1)ans+=s[i][j]-'0';
			else if(s[i][j]>s[i][j+1])ans+=s[i][j]-s[i][j+1];
		}
		else continue;
	}
	cout<<ans<<endl;
 
}
