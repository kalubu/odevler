#include <stdio.h>

#define MAX 50

void bubbleSort(int arr[], int len){
	int i,j;
	int temp;
	for(i=0;i<len-1;i++){
		for(j=0;j<len-i-1;j++){
			if(arr[j] > arr[j+1]){
				temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}
	}
	
}

int main(){
	int notlar[MAX];
	int i,n,mins=0,maxs=0;
	
	printf("Ogrenci sayisini giriniz:");
	scanf("%d", &n);
	
	while(n<6){
		printf("Ogrenci sayisi 6'dan az olamaz");
		scanf("%d", &n);
	}
	
	for(i=0;i<n;i++){
		scanf("%d", &notlar[i]);
	}
	
	bubbleSort(notlar,n);
	
	for(i=0;i<3;i++){
		mins += notlar[i];
		maxs += notlar[n-i-1];
	}
	
	printf("En buyuk 3 elemanin toplami: %d\n", maxs);
	printf("En buyuk 3 eleman: %d, %d, %d\n", notlar[n-1],notlar[n-2], notlar[n-3]);
	printf("En kucuk 3 elemanin toplami: %d\n", mins);
	printf("En kucuk 3 eleman: %d, %d, %d", notlar[0],notlar[1], notlar[2]);
	
	return 0;
}
