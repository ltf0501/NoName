#include <iostream>
#include <set>
using namespace std;
int main(){
	int t,a,b,c,type,x,y,ans,z,tot,now;
	set<int> se;
	string s;
	bool f,no,temp;
	cin>>t;
	while(t--){
		cin>>s;
		se.clear();
		tot=s.length();
		no=false;
		a=b=c=x=y=z=now=0;
		if(s[now]=='-'){
			f=true;
			now++;
		}
		else f=false;
		if(s[now]=='?')temp=true;
		else temp=false;
		while(now<tot){
			if(s[now]=='+'){
				type=1;
				now++;
				break;
			}
			else if(s[now]=='-'){
				type=2;
				now++;
				break;
			}
			else if(s[now]=='*'){
				type=3;
				now++;
				break;
			}
			x*=10;
			a*=10;
			if(s[now]=='?')x++;
			else {
				a+=s[now]-'0';
				se.insert(s[now]-'0');
			}
			now++;
		}
		if(temp&&(a!=0||x!=1))no=true;
		if(f){
			a*=-1;
			x*=-1;
		}
		if(s[now]=='-'){
			f=true;
			now++;
		}
		else f=false;
		if(s[now]=='?')temp=true;
		else temp=false;
		while(now<tot){
			if(s[now]=='='){
				now++;
				break;
			}
			y*=10;
			b*=10;
			if(s[now]=='?')y++;
			else {
				se.insert(s[now]-'0');
				b+=s[now]-'0';
			}
			now++;
		}
		if(temp&&(b!=0||y!=1))no=true;
		if(f){
			b*=-1;
			y*=-1;
		}
		if(s[now]=='-'){
			f=true;
			now++;
		}
		else f=false;
		if(s[now]=='?')temp=true;
		else temp=false;
		while(now<tot){
			c*=10;
			z*=10;
			if(s[now]=='?')z++;
			else {
				se.insert(s[now]-'0');
				c+=s[now]-'0';
			}
			now++;
		}
		if(temp&&(c!=0||z!=1))no=true;
		if(f){
			c*=-1;
			z*=-1;
		}
		ans=-1;
		//type 1=+ type 2=- type 3=*
		if(type==1){
			for(int i=no?1:0;i<10;i++)if(se.find(i)==se.end()&&a+i*x+b+i*y==c+i*z){
				ans=i;
				break;
			}
		}
		else if(type==2){
			for(int i=no?1:0;i<10;i++)if(se.find(i)==se.end()&&a+i*x-(b+i*y)==c+i*z){
				ans=i;
				break;
			}
		}
		else{
			for(int i=no?1:0;i<10;i++)if(se.find(i)==se.end()&&(a+i*x)*(b+i*y)==c+i*z){
				ans=i;
				break;
			}
		}
		//cout<<"a = "<<a<<" x = "<<x<<endl;
		//cout<<"b = "<<b<<" y = "<<y<<endl;
		//cout<<"c = "<<c<<" z = "<<z<<endl;
		cout<<ans<<endl;
	}
}
