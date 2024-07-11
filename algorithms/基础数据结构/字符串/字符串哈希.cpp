#include<iostream>
#include<cstdio>
using namespace std;
typedef unsigned long long ull;
const int N=100010,P=131;
char str[N];
ull a[N],p[N];
int n;
ull get(int l,int r){return a[r]-a[l-1]*p[r-l+1];}
int main(){
    int m;
    scanf("%d%d%s",&n,&m,str+1);
    p[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*P;
        a[i]=a[i-1]*P+str[i];
    }
    int l1,r1,l2,r2;
    while(m--){
        cin>>l1>>r1>>l2>>r2;
        if(get(l1,r1)==get(l2,r2)) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}


/*
REµÄstring
#include<iostream>
#include<string>
using namespace std;
int main(){
    string str;
    int n,m;
    cin>>n>>m>>str;
    int l1,r1,l2,r2;
    while(m--){
        cin>>l1>>r1>>l2>>r2;
        if(str.substr(l1-1,r1-l1)==str.substr(l2-1,r2-l2)) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}
*/
