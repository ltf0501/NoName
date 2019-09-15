#include <stdio.h>
void solve(){
    long long int n[3],a[3],ans=0;
    bool f;
    for(int i=0;i<3;i++)scanf("%lld",&n[i]);
    for(int i=0;i<3;i++)scanf("%lld",&a[i]);
    while(true){
        f=true;
        for(int i=0;i<3;i++)if(ans*ans*ans%n[i]!=a[i]){
            f=false;
            break;
        }
        if(f)break;
        else ans++;
    }
    printf("%lld\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
}
