#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	double coef;
	double exp;
}func;

double solve(func *f, double t, int n){
	int i;
	double sum=0;
	for(i=0;i<n;i++){
		sum += f[i].coef * pow(t,f[i].exp); 
	}
	return sum;
}

int main(){
	int i,n;
	double a,b,y,t,h,k1,k2,k3,k4,tn;
	
	printf("Ay' + By = f(t)\nA degerini giriniz: ");
	scanf("%lf",&a);
	printf("B degerini giriniz: ");
	scanf("%lf",&b);
	printf("Kac terim olacagini(n) giriniz:");
	scanf("%d",&n);
	func *f = (func *)calloc(n,sizeof(func));
	for(i=0;i<n;i++){
		printf("%d.terimin katsayisini giriniz: ",i+1);
		scanf("%lf", &f[i].coef);
		printf("%d.terimin derecesini giriniz: ",i+1);
		scanf("%lf", &f[i].exp);
	}
	printf("Baslangic t degeri: ");
	scanf("%lf",&t);
	printf("Baslangic y degeri: ");
	scanf("%lf", &y);
	printf("Hedeflenen deger: ");
	scanf("%lf", &tn);
	printf("Adim buyuklugu: ");
	scanf("%lf",&h);
	
	while(t<tn){
		k1 = h* ((solve(f,t,n)-b*y)/a);;
		k2 = h* ((solve(f,t+h/2,n)-b*(y+k1/2))/a);
		k3 = h* ((solve(f,t+h/2,n)-b*(y+k2/2))/a);
		k4 = h* ((solve(f,t+h,n)-b*(y+k3))/a);
		y = y + (k1+ 2*k2 + 2*k3+k4)/6;
		t +=h;
		printf("y(%lf):%lf k1:%lf k2:%lf k3:%lf k4:%lf\n",t,y,k1,k2,k3,k4);
	}
	return 0;
}
