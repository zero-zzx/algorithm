```cpp
#include<stdio.h>
void dicarer_love(void){
	for(double y=1.5;y>-1.5;y-=0.1){
		for(double x=-1.5;x<1.5;x+=0.05){
			double a=x*x+y*y-1;
			putchar(a*a*a-x*x*y*y*y<0?42:32);
		}
		putchar(10);
	}
}
void dicarer_love2(void){
	double f,x,y,z;
	for(y=1.5;y>-1.5;y-=0.1){
		for(x=-1.5;x<1.5;x+=0.05){
			z=x*x+y*y-1;
			f=z*z*z-x*x*y*y*y;
			if(f<0) 
			printf("%c",".:-=+*#&%@"[(int)(f*-9)]);//[-1,0)
			else putchar(32);
		}
		printf("\n");
	}
}
int main(){
	dicarer_love2();
	return 0;
}
```
