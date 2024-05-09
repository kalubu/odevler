#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int i,j,f = 0,n,m,len = 1,y, yemN, yemM,pN,pM;
    printf("Satir sayisini giriniz:");
    scanf("%d", &n);
    printf("Sutun sayisini giriniz:");
    scanf("%d", &m);
    char T[n][m];
    for (i=0;i<n;i++)
        for(j=0;j<m;j++)
            T[i][j] = ' ';
    printf("Yemek sayisini sayisini giriniz:");
    scanf("%d", &y);
    while (n*m - 1 < y){
        printf("Yemek sayisi oyun alanina sigmiyor. Yemek sayisi en fazla %d olabilir. Lutfen tekrar giriniz:", m*n-1);
        scanf("%d", &y);
    }
    pN = rand() % n;
    pM = rand() % m;
    T[pM][pM] = 1;
    for (i = 0; i < y; y++){
    	yemN = rand() % n;
    	yemM = rand() % m;
    	while (T[yemN][yemM] != ' '){
    		yemN = rand() % n;
    		yemM = rand() % m;
		}
		T[yemN][yemM] = 0;
	}
	
    while (f == 0){
		for (i = 0; i < n; i++){
			for (j=0;j<m;j++){
				printf("%d", T[i][j]);
			}
			printf("\n");
		}

    }
	

}