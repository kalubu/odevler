#include <stdio.h>
#include <stdlib.h>

void printMatrix(char **m, int n){
	int i;
	for(i=0;i<n;i++){
		printf("%s\n", m[i]);
	}
}

int getMatrix(char** m, int n){
	int i,max=0;
	for(i=0;i<n;i++){
		printf("Kelime %d :", i+1);
		scanf("%49s", m[i]);
		if(strlen(m[i]) > max){
			max = strlen(m[i]);
		}
	}
	return max;
}

void freeMatrix(char **m, int n){
	int i;
	for(i=0;i<n;i++){
		free(m[i]);
	}
	free(m);
}
void copyMatrix(char** m, char** matris, int n, int max){
	int i,j,len;
	for(i=0;i<n;i++){
		matris[i] = (char*)malloc(max+1*sizeof(char));
	}
	for(i=0;i<n;i++){
		for(j=0;j<max;j++){
			len = strlen(m[i]);
			if(j<len){
				matris[i][j] = m[i][j];
			}
			else{
				matris[i][j] = '*';
			}
		}
		matris[i][max] = '\0';
	}
}

int main(){
	int n, max = 0,i;
	char **m, **matris;
	printf("Kelime sayisini girin: ");
	scanf("%d", &n);
	m = (char**)malloc(n*sizeof(char*));
	matris = (char**)malloc(n*sizeof(char*));
	for(i=0;i<n;i++){
		m[i] = (char*)malloc(50*sizeof(char));
	}
	max = getMatrix(m, n);
	copyMatrix(m,matris,n,max);
	printMatrix(matris,n);
	freeMatrix(m,n);
	freeMatrix(matris,n);
	return 0;
}
