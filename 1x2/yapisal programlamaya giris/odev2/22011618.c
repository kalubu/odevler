#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int main(){
	int i,j,t,M[MAX][MAX],n,betul,ayse,tmp;
	char reset;
	srand(time(NULL));
	do
	{
		betul = 0;
		ayse = 0;
		printf("Matrisin boyutunu giriniz:");
		scanf("%d", &n);
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				M[i][j] = (rand() % (n*n)) + 1;
			}
		}
		for(i = 0;i<n;i++){
			for(j=0;j<n;j++){
					printf("%d", M[i][j]);
				}
				printf("\n");
			}
		printf("\n");
		for(t = 0;t<3;t++){
			for(i = 0;i<n;i++){
				for(j=i;j<n;j++){
					tmp = M[i][j];
					M[i][j] = M[j][i];
					M[j][i] = tmp;
				}
			}
			for(i = 0;i<n;i++){
				for(j=0;j<n/2;j++){
					tmp = M[i][j];
					M[i][j] = M[i][n-j-1];
					M[i][n-j-1] = tmp;
				}
			}
			for(i = 0;i<n;i++){
				for(j=0;j<n;j++){
					printf("%d", M[i][j]);
				}
				printf("\n");
			}
			for(i = 0;i<n;i++){
				betul = betul + M[n-1][i];
			}
			printf("Betul: %d	Ayse: %d\n", betul,ayse);
			for(i = 0;i<n;i++){
				for(j=i;j<n;j++){
					tmp = M[i][j];
					M[i][j] = M[j][i];
					M[j][i] = tmp;
				}
			}
			for(i = 0;i<n;i++){
				for(j=0;j<n/2;j++){
					tmp = M[i][j];
					M[i][j] = M[i][n-j-1];
					M[i][n-j-1] = tmp;
				}
			}
			for(i = 0;i<n;i++){
				for(j=0;j<n;j++){
					printf("%d", M[i][j]);
				}
				printf("\n");
			}
			for(i = 0;i<n;i++){
				ayse = ayse + M[n-1][i];
			}
			printf("Betul: %d	Ayse: %d\n", betul,ayse);
		}
		if(betul > ayse){
			printf("Betul kazandi.");
		}
		else if(ayse > betul){
			printf("Ayse kazandi.");
		}
		else{
			printf("Berabere bitti.");
		}
		printf("\nTekrar baslamak icin e'ye basiniz.");
		scanf(" %c", &reset);
	}while((reset == 'E') ||(reset == 'e'));
	return 0;
}
