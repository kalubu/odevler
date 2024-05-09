#include <stdio.h>

#define MAX 50

void input(int m[MAX][MAX], int N);
void printJobs(int m[MAX][MAX], int N,int head);

int main(){
	int i,N,m[MAX][MAX],head;
	printf("Is sayisini giriniz:");
	scanf("%d", &N);
	input(m,N);
	printf("head:");
	do{
		scanf("%d",&head);
	}while(head>N && head<0);
	printf("Link sirasi: ");
	for(i=0;i<N;i++){
		scanf("%d", &m[i][2]);
	}
	printJobs(m,N,head);
	return 0;	
}

void input(int m[MAX][MAX], int N){
	int i,j,f;
	printf("Is kodlari:\n");
	for(i=0;i<N;i++){
		do{
			f=0;
			printf("%d.Is kodu: ",i+1);
			scanf(" %c", &m[i][0]);
			for(j=0;j<i;j++){
				if(m[j][0] == m[i][0]){
					printf("Ayni is kodu girilemez! Tekrar giriniz.\n");
					f=1;
				}
			}
		}while(f);

		
	}
	printf("Is sureleri:\n");
	for(i=0;i<N;i++){
		do{
			printf("%d.Isin suresi: ", i+1);
			scanf("%d", &m[i][1]);
		}while(m[i][1] < 1);
		
	}
}

void printJobs(int m[MAX][MAX], int N, int head){
	int i,c;
	c = head;
	while(m[c][2] != -1){
		for(i=0;i<m[c][1];i++){
			printf("%c ", (char)m[c][0]);
		}
		c = m[c][2];
	}
	for(i=0;i<m[c][1];i++){
		printf("%c ", (char)m[c][0]);
	}
}
