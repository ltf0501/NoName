bool debug=false;
#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define F first
#define S second
const int N=2e2+10;
static inline char getRawChar() {
    static char buf[1 << 16], *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, 1 << 16, stdin)) == buf) 
            return '\0';
        p = buf;
    }
    return *p++;
}
char getChar() {
    char c;
    while (!isdigit(c = getRawChar()));
    return c;
}
int readInt() {
    char c;
    int n = 0;
    while (!isdigit(c = getRawChar()));
    do {
        n = n * 10 + (c - '0');
    } while ((c = getRawChar()) && isdigit(c));
    return n;
}
inline int max(int a,int b){return a>b?a:b;}
int a[N],dp[N][3][2];
void solve(){
    int n,ans=0;
    bool f=false;
    n=readInt();
    for(int i=0;i<N;i++)for(int j=0;j<3;j++)dp[i][j][0]=dp[i][j][1]=0;
    for(int i=0;i<n;i++)a[i]=readInt();
    for(int i=0;i<n;i++)a[i]+=5;
    sort(a,a+n);
    for(int i=0;i<n;i++){
        for(int j=-2;j<=2;j++)for(int k=0;k<3;k++)dp[a[i]+j][k][f]=dp[a[i]+j][k][!f];
        for(int j=0;j<3;j++)dp[a[i]][j][f]=max(dp[a[i]][j][f],max(max(dp[a[i]][j][!f],dp[a[i]-1][j][!f]),dp[a[i]-2][j][!f])+1);
        for(int j=0;j<2;j++){
            dp[a[i]+1][j+1][f]=max(dp[a[i]+1][j][f],1+max(dp[a[i]+1][j][!f],max(dp[a[i]][j][!f],dp[a[i]-1][j][!f])));
            dp[a[i]-1][j+1][f]=max(dp[a[i]-1][j+1][f],max(dp[a[i]-1][j][!f],max(dp[a[i]-2][j][!f],dp[a[i]-3][j][!f]))+1);
        }
        f=!f;
    }
    for(int i=0;i<N;i++)for(int j=0;j<3;j++)ans=max(ans,max(dp[i][j][0],dp[i][j][1]));
    printf("%d\n",ans);
}
int main(){
    int t;
    t=readInt();
    for(int i=1;i<=t;i++){
        printf("Case %d: ",i);
        solve();
    }
}
