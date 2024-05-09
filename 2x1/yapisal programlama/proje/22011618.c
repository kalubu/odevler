#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

char** getMap(char* filename,int* n,int *m,int* charX,int* charY){ /*labirenti okumak icin fonksiyon */
	int i,j;
	char** labirent;
	FILE* fp;
	fp = fopen(filename,"r");
	if(fp == NULL){
		return 0;
	}
	fscanf(fp, "%d %d",n,m);
	
	labirent = (char**)calloc(*n,sizeof(char*));
	for(i=0;i<*n;i++){
		labirent[i] = (char*)calloc(*m,sizeof(char));
	}
	for(i=0;i<*n;i++){
		for(j=0;j<*m;j++){
			/*printf("%d %d ",i,j);*/
			fscanf(fp, " %c", &labirent[i][j]);
			if(labirent[i][j] == 'G'){
				*charX = i;
				*charY = j;
			}
		}
	}
	return labirent;
	
}

void printMap(char** labirent,int n,int m,int x,int y){/*labirenti printleyen fonksiyon*/
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			/*printf("%d %d\n",i,j);*/
			if(i == x && j == y){
				printf("X ");
			}
			else{
				printf("%c ", labirent[i][j]);
			}
			
		}
	printf("\n");
	}
	
}

typedef struct{ /*player structi*/
	char isim[20];
	char soyisim[20];
	char nick[20];
	char pass[20];
}player;

void addScore(char* name, int score){/*Score dosyasina eger mevcut 5 skordan buyuk bir skor yapildiysa o skoru ekleyen fonksiyon*/
	char users[5][100];
	int scores[5];
	FILE* fp;
	int i,pos=-1;
	fp = fopen("scores.txt","r");
	for(i=0;i<5;i++){
		fscanf(fp, "%s %d\n", users[i], &scores[i]);
	}
	fclose(fp);
	for(i=4;i>-1;i--){
		if(score > scores[i]){
			pos = i;
		}
		}
	for(i=4;i>pos;i--){
		scores[i] = scores[i-1];
		strcpy(users[i] ,users[i-1]);
	}
	if(pos != -1){
		scores[pos] = score;
		strcpy(users[pos], name);
	}
	fp = fopen("scores.txt","w");
	for(i=0;i<5;i++){
		fprintf(fp, "%s %d\n", users[i], scores[i]);
	}
	fclose(fp);
}
void showScores(){/*scorelari gosteren fonksiyon*/
	char users[5][100];
	int scores[5];
	int i;
	FILE* fp;
	fp = fopen("scores.txt","r");
	for(i=0;i<5;i++){
		fscanf(fp, "%s %d\n", users[i], &scores[i]);
	}
	for(i=0;i<5;i++){
		printf("Name: %s Score: %d\n", users[i], scores[i]);
	}
}
void move(char** labirent, int* x,int* y,int n, int m, int newX,int newY,char* parcacik,int *p,int *i,player* logged){/*Karakterin hareketini saglayan fonksiyon*/
	int par[4]={0};
	int j,pr,e;
	char buffer[50];
	if( newX < n && newX >=0 && newY<m && newY >=0){/*sinir konrolu*/
		if(labirent[newX][newY] == '0' || labirent[newX][newY] == 'G'){
			*x = newX;
			*y = newY;
		}
		else if(labirent[newX][newY] == 'K'){
			*i=0;
			printf("Karadelige girdiniz. Oyun sonlaniyor\n");
		}
		else if(labirent[newX][newY] == '1'){
			printf("Duvara carptiniz");
		}
		else if(labirent[newX][newY] == 'e' || labirent[newX][newY] == 'E' || labirent[newX][newY] == 'p' || labirent[newX][newY] == 'P'){/*Parcacik toplama*/
			
			parcacik[*p] = labirent[newX][newY];
			labirent[newX][newY] = '0';
			*p = *p+1;
			*x = newX;
			*y = newY;
			
		}
		else if(labirent[newX][newY] == 'C'){/*Cikis durumunda parcacik hesabi*/
			printf("Cikisa Ulasildi\n");
			for(j=0;j<*p;j++){
				if(parcacik[j] == 'p'){
					par[0]++;
				}
				else if(parcacik[j] == 'P'){
					par[1]++;
				}
				else if(parcacik[j] == 'e'){
					par[2]++;
				}
				else if(parcacik[j] == 'E'){
					par[3]++;
				}
			}
			pr = abs(par[1]-par[0]);
			e = abs(par[3]-par[2]);
			if(pr>0 && e>0){
				printf("%d adet karsit madde uretildi. Skor: %d\n\n", pr<e ? pr:e,(pr<e ? pr:e) * n *100* m / (20-(*i)));/*burada skor hesabi var, hesaplarken atilan adim sayisi, matrisin buyuklugu ve karsit madde sayisi kullaniliyor*/
				strcpy(buffer,logged->nick);
				addScore(buffer, (pr<e ? pr:e) * n *100* m / (20-(*i)));/*skoru ekleme*/
			}
			
			*i=0;
		}
	}
	else{
		printf("Hatali hamle");					
	}
}	

int createPlayer(player* newPlayer){/*karakter olusturma, reg fonksiyonu icin ilerde kullanacagim*/
	FILE* fp;
	player temp;
	printf("Isim: ");
	scanf("%s", newPlayer->isim);
	printf("Soyisim: ");
	scanf("%s", newPlayer->soyisim);
	printf("Nick: ");
	scanf("%s", newPlayer->nick);
	printf("Password: ");
	scanf("%s", newPlayer->pass);
	fp = fopen("users.txt","rb");
	while(fread(&temp,sizeof(player),1,fp) ==1){
		if(strcmp(temp.nick, newPlayer->nick)== 0){
			printf("Bu kullanici mevcut");
			fclose(fp);

			return 0;
		}
	}	
	fclose(fp);
	return 1;
}
int login(player* logged){/*giris yapma*/
	int log=1;
	FILE* fp;
	player temp;
	char username[100];
	char pass[100];
	printf("Kullanici adi:");
	scanf("%s", username);
	printf("Sifre:");
	scanf("%s", pass);
	fp = fopen("users.txt","rb");
	while(fread(&temp,sizeof(player),1,fp) ==1){
		if(strcmp(temp.nick, username)== 0 && strcmp(temp.pass, pass)==0){
			log=0;
			
			*logged = temp;
			printf("\nHosgeldiniz: %s\n", logged->nick);
			
		}
	}
		
	if (log==1){
		printf("Hatali bilgi");
	}
	fclose(fp);
	return log;
}

int reg(player* logged){/*yeni kullanici olusturma ve yazma*/
	FILE*fp;
	int log;
	int suc;
	suc = createPlayer(logged);
	if(suc == 1){
		fp= fopen("users.txt","ab");
		fwrite(logged,sizeof(player),1,fp);
		fclose(fp);
		log=0;
	}
	else{
		log=1;
	}
	return log;
}

void pathFinder(char** labirent, int** visited,int n, int m, int x, int y,int destX, int destY, int* path, int* shortestPath, int pathLen, int* min){/*DFS ile recursive sekilde yol bulma algoritmasi, autoplay icin*/
	int i;

	if(x == destX && y == destY){
		if(pathLen < *min){/*eger mevcut en kisa yoldan daha kisa bir yol varsa yeni short pathimiz o yol oluyor*/
			*min = pathLen;
			for(i=0;i<*min;i++){
				shortestPath[i] = path[i];
			}
		}
		return;
	}
	path[pathLen] = x * m + y;
	visited[x][y] = 1;
	
	if(x+1 < n && x+1 >=0 && y<m && y >=0 && labirent[x+1][y] != 'K' && labirent[x+1][y] != '1' && visited[x+1][y] != 1) {/*Onunde engel olmayan yollardan ilerliyor*/
		pathFinder(labirent,visited,n,m,x+1,y,destX,destY,path,shortestPath,pathLen+1,min);
	}
	if(x-1 < n && x-1 >=0 && y<m && y >=0 && labirent[x-1][y] != 'K' && labirent[x-1][y] != '1' && visited[x-1][y] != 1){
		pathFinder(labirent,visited,n,m,x-1,y,destX,destY,path,shortestPath,pathLen+1,min);
	}
	if(x < n && x >=0 && y+1<m && y+1 >=0 && labirent[x][y+1] != 'K' && labirent[x][y+1] != '1' && visited[x][y+1] != 1){
		pathFinder(labirent,visited,n,m,x,y+1,destX,destY,path,shortestPath,pathLen+1,min);
	}
	if(x < n && x >=0 && y-1<m && y-1 >=0 && labirent[x][y-1] != 'K' && labirent[x][y-1] != '1' && visited[x][y-1] != 1){
		pathFinder(labirent,visited,n,m,x,y-1,destX,destY,path,shortestPath,pathLen+1,min);
	}
	
	visited[x][y] = 0;

}

void autoPlay(char** labirent, int n, int m,int x,int y, player* logged){/*autoplay*/
	int i,j,destX,destY;
	int p,a;
	int **visited = calloc(n,sizeof(int*));
	int* path = calloc(n*m,sizeof(int));
	int* shortestPath = calloc(n*m,sizeof(int));
	int min = n*m+1;
	char parcacik[20];
	
	for(i=0;i<n;i++){
		visited[i] = (int*)calloc(m,sizeof(int));
	}
	
	for(i=0;i<n;i++){/*dfs icin visited matrisini 0luyorum*/
		for(j=0;j<m;j++){
			visited[i][j]=0;
 		}
	}

	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(labirent[i][j] == 'C'){
				destX = i;
				destY = j;
			}
		}
	}

	pathFinder(labirent,visited,n,m,x,y,destX,destY,path,shortestPath,0,&min);
	free(path);
	if(min == n*m+1){
		printf("No paths");
	}
	else{
		sleep(1);system("cls");
		for(i=0;i<min;i++){/*pathteki hareketleri uyguluyorum*/
			move(labirent,&x,&y,n,m,shortestPath[i] / m ,shortestPath[i] % m,parcacik,&p,&a,logged);

			printMap(labirent,n,m,x,y);
			printf("\nParcaciklar: ");
			for(j=0;j<p;j++){
				printf("%c ",parcacik[j]);
			}
			printf("\n");
			sleep(1);system("cls");
			
		}
		if(labirent[x+1][y] == 'C'){
			move(labirent,&x,&y,n,m,x+1 ,y,parcacik,&p,&a,logged);
		}
		else if(labirent[x-1][y] == 'C'){
			move(labirent,&x,&y,n,m,x-1 ,y ,parcacik,&p,&a,logged);
		}
		else if(labirent[x][y+1] == 'C'){
			move(labirent,&x,&y,n,m,x ,y+1,parcacik,&p,&a,logged);
		}
		else if(labirent[x][y-1] == 'C'){
			move(labirent,&x,&y,n,m,x ,y-1,parcacik,&p,&a,logged);
		}
		printf("\nParcaciklar: ");
			for(j=0;j<p;j++){
				printf("%c ",parcacik[j]);
			}
			printf("\n");
		printMap(labirent,n,m,x,y);
	}
	
}
void manualPlay(char** labirent,char* map,player* logged){/*Oyuncu kontrolunde oyun icin fonksiyon*/
	int p,n,m,x,y,i,flag,j;
	char a;
	char parcacik[20];
	p=0;
	labirent = getMap(map,&n,&m,&x,&y);
	i=20;
	flag=1;
	while(i>0 && flag)
	{
		sleep(0.5); system("cls");
		printMap(labirent,n,m,x,y);
		printf("Parcaciklar: ");
		for(j=0;j<p;j++){
			printf("%c ",parcacik[j]);
		}
		printf("\nGeri Sayim:%d\n",i);
		a = getch();
		if (a==27)
		{
			printf("Cikis\n");
			break;
		}
		else
		{
			a = getch();
			/*yonlere gore move*/
			if(a == 75){
				move(labirent,&x,&y,n,m,x,y-1,parcacik,&p,&flag,logged);
			}
			else if(a==77){
				move(labirent,&x,&y,n,m,x,y+1,parcacik,&p,&flag,logged);
			}
			else if(a==72){
				move(labirent,&x,&y,n,m,x-1,y,parcacik,&p,&flag,logged);
			}
			else if(a==80){
				move(labirent,&x,&y,n,m,x+1,y,parcacik,&p,&flag,logged);
			}
		}
		i--;
		
	}
	if(i<=0){
		printf("Sure bitti"); 
	}

}
int main()
{
	int c,x,y,n,m,log=1,lf=1;
	char map[50];
	char a;
	char** labirent;
	player logged;

	do{
		if(log){
			printf("Giris yapmak icin: 1\nYeni kullanici olusturmak icin: 2\nCikis icin: 3\n");
			scanf("%d",&c);
			system("cls");
			if(c==1){
				log = login(&logged);
			}
			else if(c==2){
				log = reg(&logged);
	
			}
			else if(c==3){
				lf=0;
			}
		}
		else{
			printf("Oyuna basla:1\nSkorlari Gor:2\nCikis:3\nOyun Nasil Oynanir:4\n");
			scanf("%d",&c);
			system("cls");
			if(c == 1){
				printf("Hazir harita sec:1\nHarita yukle:2\n");
				scanf("%d",&c);
				if(c==1){
					printf("1: map.txt\n2: map2.txt\n");
					scanf("%d", &c);
					if(c ==1 ){
						strcpy(map,"map.txt");
					}
					else if(c==2){
						strcpy(map,"map2.txt");
					}
				}
				else if(c==2){
					printf("Dosya adi giriniz:");
					scanf("%s", map);
				}
			system("cls");
			printf("Manuel Oynama:1\nOtomatik Oynama:2\n");
			scanf("%d",&c);
			system("cls");
			if(c==1){
				labirent = getMap(map,&n,&m,&x,&y);
				manualPlay(labirent,map,&logged);
			}
			else if(c==2){
				labirent = getMap(map,&n,&m,&x,&y);
				autoPlay(labirent,n,m,x,y,&logged);
			}

					
			}
			else if(c==2){
				showScores();
			}
			else if(c==3){
				log=1;
			}
			else if(c==4){
				printf("Oyunda karakter G noktasindan baslar ve Cye ulasmaya calisir. Bunu yaparken karsit madde uretmek icin mumkun oldugunca p ve E toplamalidir. Maddelerin karsit halleri(ornek: p ve P) birbirini yok eder. Kullanicinin 20 adim hakki vardir\n");
			}
		}
	}while(lf);
	
	return 0;
	
}
