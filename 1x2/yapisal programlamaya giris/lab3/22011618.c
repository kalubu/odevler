#include <stdio.h>

#define MAX 100

void getMatrix(int matrix[MAX][MAX], int n){
	int i,j;
	for(i = 0; i<n; i++){
		for(j=0;j<n;j++){
			scanf("%d", &matrix[i][j]);
		}
	}
}

void printMatrix(int matrix[MAX][MAX], int n){
	int i,j;
	for(i = 0; i<n; i++){
		for(j=0;j<n;j++){
			printf("%d", matrix[i][j]);
		}
		printf("\n");
	}
}

int path(int matrix[MAX][MAX], int x,int y,int n, int *count){
	if (x == n-1 && y == n-1){
		*count = *count + 1;
		return 1;
	}
	else{
		if(matrix[x][y+1] == 1){
		 	path(matrix,x,y+1,n,count);
		}
		if(matrix[x+1][y] == 1){
			path(matrix,x+1,y,n,count);
		}
	}
}

int main(){
	int i,j,n,count=0;
	int road[MAX][MAX] = {0};
	scanf("%d",&n);
	getMatrix(road, n);
	path(road,0,0,n,&count);
	printMatrix(road, n);
	printf("%d", count);
	return 0;
}
