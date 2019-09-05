#include <iostream>
using namespace std;
int main(){
    int cnt[2];
    string s;
    cin>>s;
    cnt[0]=cnt[1]=0;
    for(char i:s)cnt[i-'0']++;
    if(cnt[0]==cnt[1]){
        if(s.back()=='0'){
            for(int i=1;i<s.size();i++)cout<<'0';
            cout<<'1';
        }
        else{
            for(int i=1;i<s.size();i++)cout<<'1';
            cout<<'0';
        }
    }
    else if(cnt[0]>cnt[1])for(char i:s)cout<<'1';
    else for(char i:s)cout<<'0';
    cout<<endl;
}
