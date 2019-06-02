#include<iostream>
using namespace std;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	string s;
	cin>>n;
	while(n--){
		cin>>s;
		if(s.back()=='o'||s.back()=='s'||s.back()=='x')cout<<s<<"es"<<endl;
		else if(s.size()>1&&s.back()=='h'&&s[s.size()-2]=='c')cout<<s<<"es"<<endl;
		else if(s.back()=='f'){
			s.back()='v';
			cout<<s<<"es"<<endl;
		}
		else if(s.size()>1&&s[s.size()-2]=='f'&&s.back()=='e'){
			s[s.size()-2]='v';
			cout<<s<<"s"<<endl;
		}
		else if(s.back()=='y'){
			s.back()='i';
			cout<<s<<"es"<<endl;
		}
		else{
			cout<<s<<"s"<<endl;
		}
		
	}
}
