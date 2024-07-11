#include<iostream>
#include<cstring>
using namespace std;
int dis[210][210],n;
int main(){
    int m,p;
    cin>>n>>m>>p;
    memset(dis,0x3f,sizeof dis);
    // for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=0;i<m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        dis[x][y]=min(dis[x][y],z);
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
                
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<dis[i][j]<<' ';
        }
        cout<<endl;
    }            
    
    
    // while(p--){
    //     int x,y;
    //     cin>>x>>y;
    //     if(x==y){
    //         cout<<0<<endl;
    //         continue;
    //     }
    //     if(dis[x][y]>0x3f3f3f3f/2) cout<<"impossible"<<endl;
    //     else cout<<dis[x][y]<<endl;
    // }     
    
    return 0;
}
