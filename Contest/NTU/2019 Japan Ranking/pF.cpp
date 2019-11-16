#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
#define F first
#define S second
#define PB push_back
const int N=1e5+10;
vector<int> graph[N];
int p[N],dep[N],fa[N];
int find(int n){return p[n]==n?n:p[n]=find(p[n]);}
void dfs(int pos){
    for(int i:graph[pos])if(i!=fa[pos]){
        dep[i]=dep[pos]+1;
        dfs(i);
    }
    return ;
}
int main(){
    string s;
    vector<pair<int,int>> query;
    vector<int> ans;
    long long int tot=0;
    int l,r,n,q,k,marked[N];
    cin>>n>>q;
    fa[1]=0;
    for(int i=2;i<=n;i++){
        cin>>fa[i];
        graph[fa[i]].PB(i);
        graph[i].PB(fa[i]);
    }
    for(int i=1;i<=n;i++)p[i]=i;
    dep[1]=0;
    dfs(1);
    for(int i=1;i<=n;i++)marked[i]=0;
    marked[1] = 1;
    for(int i=0;i<q;i++){
        cin>>s>>k;
        if(s[0]=='Q')query.PB({0,k});
        else {
            query.PB({1,k});
            marked[k]++;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j:graph[i]){
            l=find(i);
            r=find(j);
            if(dep[l]<dep[r]){
                if(!marked[r])p[r]=l;
            }
            else if(!marked[l])p[l]=r;
        }
    }
    reverse(query.begin(),query.end());
    for(pair<int,int> i:query){
        if(i.F==0)tot+=find(i.S);
        else{
            marked[i.S]--;
            for(int j:graph[i.S]){
                l=find(i.S);
                r=find(j);
                if(dep[l]<dep[r]){
                    if(!marked[r])p[r]=l;
                }
                else if(!marked[l])p[l]=r;
            }
        }
    }
    for(int i:ans)tot+=i;
    cout<<tot<<endl;
}
