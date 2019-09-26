bool debug=false;
#include <stdio.h>
#include <vector>
#include <bitset>
using namespace std;
#define PB push_back
const int N=(1<<20) + 5;
vector<long long int> prime;
void pre(){
    bitset<N> b;
    b.reset();
    prime.PB(2);
    for(long long int i=3;i<N;i++)if(!b[i]){
        prime.PB(i);
        for(long long int j=i*i;j<N;j+=i<<1)b[j]=true;
    }
    return ;
}
void solve(){
    long long int r,ans=0,now;
    int temp;
    vector<int> v;
    scanf("%lld",&r);
    for(long long int i:prime){
        if(r<i)break;
        if(r%i==0){
            temp=0;
            while(r%i==0){
                temp++;
                r/=i;
            }
            v.PB(temp);
        }
    }
    if(r>1)v.PB(1);
    if(debug){
        for(int i:v)printf("%d ",i);
        printf("\n");
    }
    for(int i=0;i<v.size();i++){
        now=v[i];
        for(int j=0;j<v.size();j++)if(i!=j)now*=v[j]+1;
        ans+=now;
    }
    printf("%lld\n",ans);
    return ;
}
int main(){
    int t;
    pre();
    scanf("%d",&t);
    while(t--)solve();
}
