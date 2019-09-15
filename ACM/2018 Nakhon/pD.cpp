#include <stdio.h>
const int N=2e6+10;
int a[N];
void solve(){
    int n,ans=1,last,now=1;
    scanf("%d",&n);
    if(n==0){
        printf("0\n");
        return ;
    }
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    last=a[0]+20;
    while(now<n){
        if(a[now]>last){
            last=a[now]+20;
            ans++;
        }
        now++;
    }
    printf("%d\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
}
