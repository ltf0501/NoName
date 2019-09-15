#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define F first
#define S second
#define PB push_back
void tov(string &s,vector<pair<string,int>> &v){
	v.clear();
	string st;
	for(int i=0;i<s.size();i++){
		st.clear();
		if('0'<=s[i]&&s[i]<='9'){
			while(i<s.size()&&'0'<=s[i]&&s[i]<='9')st+=s[i++];
			i--;
			v.PB({st,1});
		}
		else {
			st+=s[i];
			v.PB({st,-1});
		}
	}
}
int min(int a,int b){return a>b?b:a;}
bool cmp(vector<pair<string,int>> &s,vector<pair<string,int>> &a){
	int tot,left,right,temp,l=(int)s.size(),r=(int)a.size();
	tot=min(l,r);
	for(int i=0;i<tot;i++){
		if(s[i].S==a[i].S){
			if(s[i].S==-1){
				if(s[i].F==a[i].F)continue;
				else return s[i].F>a[i].F;
			}
			else{
				left=(int)s[i].F.size();
				right=(int)a[i].F.size();
				temp=min(left,right);
				if(left!=right)return left>right;
				for(int j=0;j<temp;j++)if(a[i].F[j]!=s[i].F[j])return s[i].F[j]>a[i].F[j];
			}
		}
		else return s[i].S<a[i].S;
	}
	return l>r;
}
int main(){
	string s,a;
	vector<pair<string,int>> l,r;
	int n;
	cin>>n>>s;
	tov(s,l);
	while(n--){
		cin>>a;
		tov(a,r);
		if(cmp(l,r))cout<<"-"<<endl;
		else cout<<"+"<<endl;
	}
}
