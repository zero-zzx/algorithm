//Å·À­É¸ 
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1000010;
int ps[N],cnt;
bool st[N];
void init(int n){
    for(int i=2;i<=n;i++){
        if(!st[i]) ps[cnt++]=i;
        for(int j=0;ps[j]<=n/i;j++){
            st[ps[j]*i]=1;
            if(i%ps[j]==0) break;
        }
    }
}
int main(){
    int n;
    cin>>n;
    init(n);
    cout<<cnt<<endl;
    return 0;
}


//°£ÊÏÉ¸ 
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1000010;
int ps[N],cnt;
bool st[N];
void init(int n){
    for(int i=2;i<=n;i++){
        if(st[i]==0) ps[cnt++]=i;
        for(int j=2;j*i<=n;j++){
            st[j*i]=1;
        }
    }
}
int main(){
    int n;
    cin>>n;
    init(n);
    cout<<cnt<<endl;
    return 0;
}
