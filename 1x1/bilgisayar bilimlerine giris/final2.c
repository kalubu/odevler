#include <stdio.h>

int main(){
	int A[100][100], n,m,i,j,tmp;
	scanf("%d", &n);
	scanf("%d", &m);
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			scanf("%d", &A[i][j]);
	for(i=0;i<n;i++){
		for(j=0;j<m/2;j++){
			tmp = A[i][j];
			A[i][j] = A[i][m-j-1];
			A[i][m-j-1] = tmp;
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%d", A[i][j]);
		}
		printf("\n");
	}
	return 0;
}
