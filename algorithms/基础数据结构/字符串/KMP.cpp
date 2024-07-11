#include<iostream>
#include<cstdio>
using namespace std;
const int N=100010,M=1000010;
int ne[N],m;
char s[M],ss[N];

int main(){
    int n;
    cin>>m>>ss+1>>n>>s+1;
    
    for(int i=2,j=0;i<=m;i++){
        while(j&&ss[i]!=ss[j+1]) j=ne[j];
        if(ss[i]==ss[j+1]) j++;
        ne[i]=j;
    }

    
    for(int i=1,j=0;i<=n;i++){
        while(j&&s[i]!=ss[j+1]) j=ne[j];
        if(s[i]==ss[j+1]) j++;
        if(j==m){
            cout<<i-m<<' ';
            j=ne[j];
        }
    }
    
    
    return 0;
} 
