bool debug=false;
#include <iostream>
#include <map>
using namespace std;
string s;
map<char, int> isop;
bool solve(int l,int r){
  if(debug)printf("dfs(%d,%d)\n",l,r);
  if (r - l + 1 == 0) return false;
  if(l>r)return true;
  if(r-l+1==3){
    if(isalpha(s[l]) && isop[s[l + 1]] && isalpha(s[r]))return false;
  }
  else if (r-l+1==2) return true;
  else if (l==r) return true;
  int first=l,last=r,cnt=0,pos=0;
  for(int i=l;i<=r;i++){
    if(s[i]=='(')cnt++;
    else if(s[i]==')')cnt--;
    else if(cnt==0)pos++;
  }
  if(debug)printf("pos=%d\n",pos);
  if(pos==2){
    if(s[l]=='('){
      if(isalpha(s[r])&&isop[s[r - 1]]) return solve(l+1,r-3);
      else return true;
    }
    else if(s[r]==')'){
      if(isalpha(s[l])&&isop[s[l + 1]]) return solve(l+3,r-1);
      else return true;
    }
    else return true;
  }
  else if(pos==1){
    if(s[l]=='('&&s[r]==')'){
      cnt=0;
      for(int i=l;i<=r;i++){
        if(s[i]=='(')cnt++;
        else if(s[i]==')')cnt--;
                else if(cnt==0)pos=i;
      }
      return solve(l+1,pos-2)|solve(pos+2,r-1);
    }
    else return true;
  }
  return true;
}
bool ce(int l,int r){
  int cnt=0;
  for(int i=l;i<=r;i++)if(s[i]!=' '){
    if(s[i]=='(') {
      cnt++;
      if (i && (!isop[s[i - 1]] && s[i - 1] != '(')) return true;
    } else if(s[i]==')') {
      cnt--;
      if (i && (!isalpha(s[i - 1]) && s[i - 1] != ')')) return true;
    }
    else if('a'<=s[i]&&s[i]<='z'){
      if(i!=0&&(('a'<=s[i-1]&&s[i-1]<='z')||s[i-1]==')'))return true;
    }
    else{
      if(i!=0&&('a'<=s[i-1]&&s[i-1]<='z'||s[i-1]==')')){}   
      else return true;
    }
    if(cnt<0)return true;
  }
  return cnt!=0 || !(isalpha(s[r]) || s[r] == ')');
}
int main(){
  isop['+'] = isop['-'] = isop['*'] = isop['/'] = isop['%'] = true;
  string c;
  while(cin>>c)s+=c;
if (debug) cout << s << '\n';
  if(ce(0,(int)s.size()-1))cout<<"error"<<endl;
  else if(solve(0,(int)s.size()-1))cout<<"improper"<<endl;
  else cout<<"proper"<<endl;
}
