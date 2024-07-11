//°ËÊıÂë 
#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<queue>
#include<string>
using namespace std;
typedef pair<int,string> PIS;
const string final="12345678x";
const char op[]="urdl";
const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
unordered_map<string,string> mp;
unordered_map<string,int> dis;
priority_queue<PIS,vector<PIS>,greater<PIS> >heap;
int f(string& s){
    int res=0;
    for(int i=0;i<9;i++)
        if(s[i]!='x'){
            int t=s[i]-49;
            res+=abs(i/3-t/3)+abs(i%3-t%3);
        }
    return res;    
}
string dfs(string& start){
    heap.push({f(start),start});
    mp[start]="";
    dis[start]=1;
    while(heap.size()){
        string s=heap.top().second;
        if(s==final) return mp[s];
        heap.pop();
        int k=s.find('x');
        int x=k/3,y=k%3;
        for(int i=0;i<4;i++){
            int xx=x+dx[i],yy=y+dy[i];
            if(xx<0||xx>2||yy<0||yy>2) continue;
            string ss=s;
            swap(ss[x*3+y],ss[xx*3+yy]);
            if(dis[ss]==0||dis[ss]>dis[s]+1){
                dis[ss]=dis[s]+1;
                mp[ss]=mp[s]+op[i];
                heap.push({f(ss)+dis[ss],ss});
            }
        }
    }
}
int main(){
    string s,ss;
    for(int i=0;i<9;i++){
        char ch;
        cin>>ch;
        s+=ch;
        if(ch!='x') ss+=ch;
    }
    int cnt=0;
    for(int i=0;i<8;i++)
        for(int j=i+1;j<8;j++)
            if(ss[i]>ss[j]) cnt++;
    if(cnt&1) cout<<"unsolvable"<<endl;
    else cout<<dfs(s)<<endl;
    return 0;
}
// lldrdruldluruldrrulddruldr
