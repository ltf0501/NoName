#include <stdio.h>
#include <vector>
using namespace std;
#define PB push_back
const int N=1e3+10; 
int main(){
	int n,pos=0,cnt,temp,last=0;
	long long int k;
	bool used[N];
	long long f[N];
	vector<int> ans;
	scanf("%d%lld",&n,&k);
	k--;
	f[0]=f[1]=1;
	used[0]=true;
	for(int i=1;i<=n;i++)used[i]=false;
	for(int i=2;i<=n;i++){
		f[i]=f[i-1]*i;
		if(f[i]>k){
			pos=i;
			for(int j=1;j<n-i;j++)ans.PB(1),last++,used[j]=true;
			break;
		}
	}
	for(int i=1;i<=pos;i++){
		temp=k/f[pos-i];
		k-=temp*f[pos-i];
		cnt=0;
	//	printf("temp=%d f[pos-i]=%lf last=%d k=%lld\n",temp,f[pos-i],last,k);
		for(int j=1;j<=n;j++){
			if(!used[(j+last)%n])cnt++;
			if(cnt>temp){
				ans.PB(j);
				last+=j;
				last%=n;
				used[last]=true;
				break;
			}
		}
	}
	printf("%d",ans[0]);
	for(int i=1;i<ans.size();i++)printf(" %d",ans[i]); 
	printf("\n");
}
