#include <stdio.h>

int main(){
	int n,m,i,j,x, M[100][100],max=0,tmp,count, benzer,asdas;
	freopen("input.txt","r",stdin);
	scanf("%d", &n);
	scanf("%d", &m);
	scanf("%d", &x);
	x--;
	for (i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d", &M[i][j]);	
		}
	}
	for (i=0;i<n;i++){
		count = 0;
		tmp = 0;
		if(i != x){
			for(j=0;j<m;j++){
				if(M[i][j]!=0 && M[x][j] != 0){
					count++;
					benzer = M[i][j] < M[x][j] ? (M[x][j] - M[i][j]): (M[i][j] - M[x][j]);
					tmp = tmp + benzer;
				}
			}
			tmp = tmp/count;
			if (count > m/2){
				if (tmp > max){
					max = tmp;
					asdas = i;
				}
			}
		}
	}
	printf("%d", asdas+1);
	return 0;
}
