#include <iostream>
using namespace std;
const int N=5e2+10;
int main(){
    int n,m,ans=0;
    bool f=false;
    string s[N];
    cin>>n>>m;
    for(int i=0;i<n;i++)cin>>s[i];
    for(int i=1;i<n-1;i++)for(int j=1;j<m-1;j++)if(s[i][j]=='.')ans++;
    if(n==1){
        ans=0;
        for(int i=1;i<m-1;i++)if(s[0][i]=='.')ans++;
        cout<<ans<<endl;
    }
    else if(m==1){
        ans=0;
        for(int i=1;i<n-1;i++)if(s[i][0]=='.')ans++;
        cout<<ans<<endl;
    }
    else if(m==2){
        ans=0;
        for(int i=1;i<n-1;i++)if(s[i][0]=='.'&&s[i][1]=='.')ans++;
        cout<<ans<<endl;
    }
    else if(n==2){
        ans=0;
        for(int i=1;i<m-1;i++)if(s[0][i]=='.'&&s[1][i]=='.')ans++;
        cout<<ans<<endl;
    }
    else{
        for(int i=1;i<n-1;i++)if(s[i][0]=='#'||s[0][i]=='#')f=true;
        if(!f)ans++;
        cout<<ans<<endl;
    }
}
