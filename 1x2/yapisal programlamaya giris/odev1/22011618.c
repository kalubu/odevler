#include <stdio.h>

int main(){
	char kelime[999], cont, tmp, shift;
	int i, j, len;
	do{
		j = 0;
		printf("Kelimeyi giriniz:");
		scanf("%s", kelime);
		do{
			tmp = kelime[0];
			i=0;
			do{
				kelime[i] = kelime[i+1];
				i++;
			}while(kelime[i+1] != '\0');
			kelime[i] = tmp;
			len = i+1;
			printf("%s\n", kelime);
			j++;
		}while(j<len);
		printf("Devam etmek icin e ya da E'ye basiniz.");
		scanf(" %c", &cont);
	}
	while(cont == 'E' || cont == 'e');
	return 0;
}
