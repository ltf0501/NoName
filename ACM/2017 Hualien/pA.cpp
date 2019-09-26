#include <stdio.h>
const int N=1e3+10;
int ABS(int n){return n>0?n:-n;}
void solve(int n,int d){
    int a[N],b[N];
    bool f;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    f=true;
    for(int i=2;i<=n;i++)if(ABS(a[i]-a[i-1])>d){
        f=false;
        break;
    }
    if(f){
        printf("Y\n");
        return ;
    }
    else{
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)b[j]=a[j];
            if(i==1)b[i]=a[i+1];
            else if(i==n)b[i]=a[i-1];
            else b[i]=(a[i-1]+a[i+1])>>1;
            f=true;
            for(int j=2;j<=n;j++)if(ABS(b[j]-b[j-1])>d){
                f=false;
                break;
            }
            if(f){
                printf("Y\n");
                return ;
            }
        }
    }
    printf("N\n");
}
int main(){
    int n,d;
    while(true){
        scanf("%d",&n);
        if(n==0)break;
        scanf("%d",&d);
        solve(n,d);
    }
}
