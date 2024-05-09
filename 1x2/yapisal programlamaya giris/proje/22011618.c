#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 15   
void drawBoard(int matris[][MAX], int N);
void readFromFile(int matris[][MAX], char *fileName);
int drawRoad(int matris[][MAX], int fromX, int fromY, int toX, int toY);
void undo(int matris[][MAX], int pairs[2][2][MAX], int h[][2][6], int count,int history);
void userScores(char players[MAX][MAX], int users, int scores[MAX]);
void scoreCalculator(char players[MAX][MAX], int users, int scores[MAX], int playerIndex,int random, int undoCount,int N);
int playerInit(char players[MAX][MAX], int* users);
void zeroFill(int matris[MAX][MAX], int N);
void manualPlay(int matris[MAX][MAX],int N, int gameHistory[2][2][6], int pairs[2][2][MAX],int scores[MAX],int random,int users, int playerIndex,char players[MAX][MAX]);

int main(){
    int i,j,k,choice,matris[MAX][MAX]={{0}},x,y,pairs[2][2][MAX],val,N,gameHistory[2][2][6],scores[MAX] = {0},users=0,playerIndex=0,random;
	char players[MAX][MAX]; 
    char fileName[20];
    srand(time(NULL));

    
	do{
  		printf("Ana menu\n1: Rastgele Matris Olustur\n2: Dosyadan Matris Olustur\n3: Kullanicilarin Skorlarini Goster\n4: Cikis\nTercihiniz: ");
  		random = 0;
		scanf("%d", &choice);
		if(choice == 1 || choice == 2){
			playerIndex = playerInit(players,&users);
		}
		
		if(choice == 1){
			printf("Matris Boyutunu Giriniz:");
			scanf("%d", &N);
			zeroFill(matris,N);
			random = 1;
			for(i=0;i<N;i++){
				for(j=0;j<2;j++){
					do{
						x = rand() % N;
						y = rand() % N;
					}while(matris[x][y] != 0);/*ciftleri pairs matrisine atiyor*/
					matris[x][y] = i+1;
					pairs[j][0][i] = x;
					pairs[j][1][i] = y;
				}
			}
			drawBoard(matris,N);
		}
		
		else if(choice == 2){
		  	printf("Dosya Adini Giriniz:");
		  	scanf("%s",fileName);
		  	printf("Matris Boyutunu Giriniz:");
			scanf("%d", &N);
			zeroFill(matris,N);
			readFromFile(matris, fileName);
		    drawBoard(matris,N);
			for(i=0;i<N;i++){
		    	for(j=0;j<2;j++){
		    		for(k=0;k<2;k++){
		    			pairs[j][k][i] = -1;
					}
				}
			}

		    for(i=0;i<N;i++){
		    	for(j=0;j<N;j++){
		    		val = matris[i][j] - 1;
		    		if(val != -1){
		    			if(pairs[0][0][val] == -1 && pairs[0][1][val] == -1){
		    				pairs[0][0][val] = i;
		    				pairs[0][1][val] = j;
						}
						else{
							pairs[1][0][val] = i;
		    				pairs[1][1][val] = j;
						}
					}
				}
			}
		}
		
		else if(choice == 3){
				userScores(players,users,scores);
		}

		
		if(choice == 1 || choice == 2){
			printf("\n1: Manuel Modda Oyna\n2: Otomatik Modda Oyna\n3: Ana Menuye Don\n");
			scanf("%d",&choice);
			if(choice == 1){
				manualPlay(matris,N,gameHistory, pairs,scores,random,users,playerIndex,players);
			}
			if(choice == 2){
				printf("Otomatik oynama ozelligi mevcut degildir.\n");
			}
		}
	}while(choice != 4);
	return 0;
}
void readFromFile(int matris[][MAX], char *fileName){ /*Dosyadan veri okuyan fonksiyon*/
	int i,j, temp;
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("Dosya Acilamadi!");
		return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);  
		matris[i][j]=temp; 
    }  
  	fclose(data);
}

void drawBoard(int matris[][MAX], int N){/*Oyun matrisini bastirir*/
    int i,j,k;
    for(i=0;i<N;i++){
        printf("\n");
        for (k=0;k<N;k++)
            printf("-------");
        printf("\n");
        for(j=0;j<N;j++)
            if (matris[i][j]!=0)
                printf("  %d   |",matris[i][j]);
            else
                 printf("      |",matris[i][j]);
    }
}

int drawRoad(int matris[][MAX], int fromX, int fromY, int toX, int toY){ /*Oyuncunun girdigi degerlere gore yol cizer*/
	int i,val = matris[fromX][fromY];
	if((matris[toX][toY] == 0 || val == matris[toX][toY]) && (fromX == toX || fromY == toY)){/*Kulanicinin varmaya calistigi yer ya 0 olmali ya eslesmesi gereken sayi*/
		if(fromX == toX){/*hangi duzlemde hareket edilecegini buluyor.*/
			if(fromY<toY){
				for(i=fromY+1;i<toY;i++){
					if(matris[fromX][i]!=0){/*Arada 0dan farkli deger varsa cizmeyip 0 donduruyor */
						return 0;
					}
				}
				for(i=fromY+1;i<toY+1;i++){
						matris[fromX][i] = val;
				}
			}
			else{
				for(i=toY+1;i<fromY;i++){
					if(matris[fromX][i]!=0){
						return 0;
					}
				}
				for(i=toY;i<fromY+1;i++){
						matris[fromX][i] = val;
				}
			}
		}
		else if(fromY == toY){
			if(fromX<toX){
				for(i=fromX+1;i<toX;i++){
					if(matris[i][fromY]!=0){
						return 0;
					}
				}
				for(i=fromX+1;i<toX+1;i++){
						matris[i][fromY] = val;
				}
			}
			else{
				for(i=toX+1;i<fromX;i++){
					if(matris[i][fromY]!=0){
						return 0;
					}
				}
				for(i=toX;i<fromX+1;i++){
						matris[i][fromY] = val;
				}
			}
		}
		else{
			return 0;
		}
		return 1;
	}
	else{
		return 0;
	}
}

void userScores(char players[MAX][MAX], int users, int scores[MAX]){/*Oyuncu puanlarini bastiran fonksiyon*/
	int i;
	for(i=0;i<users;i++){
		printf("%s: %d\n", players[i], scores[i]);
	}
	
	
}
void scoreCalculator(char players[MAX][MAX], int users, int scores[MAX], int playerIndex,int random, int undoCount,int N){/*Oyuncu puanlarini hesaplayan fonksiyon*/
	int score = 100;
	
	score *= N;
	
	if(random == 1){
		score *= 2;
	}
	score -= undoCount * N;
	scores[playerIndex] += score;
	printf("\n%d puan kazandiniz.", score);
	
}
void zeroFill(int matris[MAX][MAX], int N){/*Bir matrisi 0'la dolduran fonksiyon*/
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			matris[i][j] = 0;
		}
	}
}
int playerInit(char players[MAX][MAX],int* users){/*Oyuncu ismi daha once girildiyse o oyuncuya atama yapiyor. Eger isim daha once girilmemis bir isimse yeni kullanici olusturuyor.*/
	char playerName[MAX];
	int n,i,r,j;
	printf("Username: ");
	scanf("%s", playerName);
	n=0;
	for(i=0;i<*users;i++){
		r=1;
		j=0;

		while(players[j][i] != '\0'){
			if(players[j][i] != playerName[j]){
				r=0;
			}
		j++;
		}
		if(r==1 && playerName[j] == '\0' && players[j][i] == '\0'){
			return i;
		}
	}
	
	if(n==0){
		strcpy(players[*users], playerName);
		(*users)++;
		return (*users)-1;
		
	}
	return 0;
}
void undo(int matris[][MAX], int pairs[2][2][MAX], int h[][2][6], int count,int history){/*Kullanici yaptigi hareketi geri almak isterse bu fonksiyonu cagiriyor. Parametre olarak h matrisi gecmiste yapilan degerleri tutuyor. Bu degerlere gore 0lardan yol ciziyor diye dusunebiliriz.*/
	int i,val,pairSelect,fromX,fromY,toX,toY;
	val = matris[h[0][0][0]][h[0][1][0]]-1;

	fromX = h[0][0][0];
	fromY = h[0][1][0];
	toX = h[1][0][0];
	toY = h[1][1][0];
	if(pairs[0][0][val] == toX &&  pairs[0][1][val] == toY){
		pairSelect = 0;
	}
	else if(pairs[1][0][val] == toX &&  pairs[1][1][val] == toY){
		pairSelect = 1;

	}	

	if(fromX == toX){
		if(fromY<toY){
			for(i=fromY+1;i<toY+1;i++){
				matris[fromX][i] = 0;
			}
		}
		else{
			for(i=toY;i<fromY;i++){
				matris[fromX][i] = 0;
				
			}
		}
	}
	else if(fromY == toY){
		if(fromX<toX){
			for(i=fromX+1;i<toX+1;i++){

				matris[i][fromY] = 0;

			}
		}
		else{
			for(i=toX;i<fromX;i++){
				matris[i][fromY] = 0;
			}
		}
	}

	if(pairs[0][0][val] == pairs[1][0][val] && pairs[0][1][val] == pairs[1][1][val]){
		matris[pairs[0][0][val]][pairs[0][1][val]] = val+1;
		matris[pairs[1][0][val]][pairs[1][1][val]] = val+1;
	}
	pairs[pairSelect][0][val] = fromX;
	pairs[pairSelect][1][val] = fromY;
	for(i=0;i<history;i++){
		h[0][0][i] = h[0][0][i+1];
		h[0][1][i] = h[0][1][i+1];
		h[1][0][i] = h[1][0][i+1];
		h[1][1][i] = h[1][1][i+1];
	}
}
	
void manualPlay(int matris[MAX][MAX],int N, int gameHistory[2][2][6], int pairs[2][2][MAX],int scores[MAX],int random,int users, int playerIndex,char players[MAX][MAX]){/*Manuel oynamanin fonksiyonu. Parametre olarak oyun matrisini, gecmis hareketleri, matrisin uzunlugunu vs. aliyor ve oyunu oynatiyor.*/
	int history=0,fromX,fromY,f,toX,toY,val,undoCount=0,pairSelect,i;
	printf("Hamlenizi geri almak icin Source'a -1 giriniz");
	do{
		
	
	printf("\nSource:");
	scanf("%d",&fromX);
	if(fromX == -1){
		if(history >0){
			f=1;
			history--;
			undo(matris,pairs,gameHistory,1,history);
			drawBoard(matris,N);
			undoCount++;
		}
	}
	else{
	f = 0;
	scanf("%d",&fromY);
	printf("Destination:");
	scanf("%d",&toX);
	scanf("%d",&toY);
	val = matris[fromX][fromY] - 1;
	if(((pairs[0][0][val] == fromX &&  pairs[0][1][val] == fromY) || (pairs[1][0][val] == fromX &&  pairs[1][1][val] == fromY)) && (toX < N && toY < N && toX>=0 && toY>=0)){ /*Kullanici hareket icin pairlerden birini secmeli ve matrisin disina tasmamali*/
		if(pairs[0][0][val] == fromX &&  pairs[0][1][val] == fromY){/*Hangi pairin hareket edecegini buluyor.*/
			pairSelect = 0;
		}
		else if(pairs[1][0][val] == fromX &&  pairs[1][1][val] == fromY){
			pairSelect = 1;

		}
		if(drawRoad(matris,fromX,fromY,toX,toY)){
			printf("Basarili, yol cizildi!\n");

			pairs[pairSelect][0][val] = toX;
			pairs[pairSelect][1][val] = toY;
			for(i=history;i>0;i--){/*Historyi saga kaydiriyor*/
				gameHistory[0][0][i] = gameHistory[0][0][i-1];
				gameHistory[0][1][i] = gameHistory[0][1][i-1];
				gameHistory[1][0][i] = gameHistory[1][0][i-1];
				gameHistory[1][1][i] = gameHistory[1][1][i-1];
			}/*Historye kaydediyor*/
			gameHistory[0][0][0] = fromX;
			gameHistory[0][1][0] = fromY;
			gameHistory[1][0][0] = toX;
			gameHistory[1][1][0] = toY;
			if(history!=5){
				history++;
			}
		}
		else{
			printf("Hatali hamle");
		}
		for(i=0;i<N;i++){/*pairler birbiriyle eslesiyor mu kontrol ediliyor.*/
			if(pairs[0][0][i] != pairs[1][0][i] || pairs[0][1][i] != pairs[1][1][i]){
				f=1;
			}
			else{
				printf("%d: eslesti ", i+1);
			}
		}
			
	}
	else{
		printf("Hatali hamle");
		f=1;
	}
	drawBoard(matris,N);
	}
	}while(f);
	scoreCalculator(players,users,scores,playerIndex,random,undoCount,N);
}
