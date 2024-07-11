#include<iostream>
#include<cstdio>
#define EPS 1e-8
using namespace std;
int main(){
	double x,l,r;
	scanf("%lf",&x);
	l=-100,r=100;
	while(r-l>EPS){
		double mid=(l+r)/2;
		if(mid*mid*mid<x) l=mid;
		 else r=mid;
	}
	printf("%lf",l);
	return 0;
} 
