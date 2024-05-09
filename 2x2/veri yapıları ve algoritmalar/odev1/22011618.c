#include <stdio.h>
#include <stdlib.h>


typedef struct link{ 
	int data; /*linkli liste kullanmak icin node yapisini olusturuyoruz.*/
	struct link *next;
}Node;
/*fonksiyon prototipleri*/
void printLL(Node*);
void initialize(Node**, Node**, Node**, Node**);
void rotateClockwise(Node**, int);
void rotateAntiClockwise(Node**, int);
void rotationNumbers(Node**, Node**, Node** ,int);
int keyFinder(Node*, Node*, Node*);
int find(Node*, int);
Node *createNode(int data) { /*yeni node olusturma fonksiyonu olusturuyoruz*/
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
Node *createCog(int max, int len, int key,int index, Node* ortak){/*soruda tanimlanan carka benzer bir yapiyi dariesel linkli liste kullanarak olusturmak icin fonskiyon*/
	Node *temp,*temp2;
	Node *head=NULL;
	int i, rnd,tmp;
	do{
		rnd = (rand() % max)+1;
	}while(find(ortak, rnd) >= 0);
	head = createNode(rnd);
	for(i = 1; i<len;i++){
		do{
			rnd = (rand() % max)+1;
		}while((find(head, rnd) >= 0) || ((find(ortak, rnd) >= 0) && rnd != key));/*ortak listesine key de girecegi icin bazi ekstrem caselerde(5,3 gibi) olusabilecek tek eleman key kaliyor ve sonsuz while dongusune giriyordu. Bu durumu asmak icin random sayi keye esitse ortak listesinde olup olmamasina bakmamasini sagladim.*/
		temp = createNode(rnd);
		temp->next = head;
		head = temp;
	}
	if(find(head,key) < 0){/*eger rastgele olusmus listede keyi bulamazsa kendisi keyi koyuyor*/
		temp = head;
		for(i=0; i<index;i++){
			temp = temp->next;
		}
		temp->data = key;
	}
	else{/*key var ise keyi olmasi gereken indisteki elemanla yer degistiriyor.*/
		temp = head;
		temp2 = head;
		while(temp->data != key){
			temp= temp->next;
		}
		for(i = 0; i < index; i++){
			temp2 = temp2->next;
		}
		temp->data = temp2->data;
		temp2->data = key;
	}
	temp = head;
	while(temp->next != NULL){
		temp = temp->next;
	}

	temp->next = head;/*linkli listeyi kuyrugu basa baglayarak dairesel hale getirdim.*/
	return head;
}
int main(){
	int key;
	Node *ortak,*head1,*head2,*head3 = NULL;
	srand(time(NULL));/*rastgele sayi uretmek icin random seed*/
	initialize(&head1,&head2,&head3,&ortak); /* carklari olusturan ana fonksiyonu cagirdim.*/
	key = keyFinder(head1,head2,head3); /* keyi bulan fonksiyonu cagirdim.*/
	printf("\n");
	rotationNumbers(&head1,&head2,&head3,key); /* carklari dondurup printleyen fonksiyonu cagirdim.*/
	return 0;
}

void initialize(Node** head1, Node** head2, Node** head3, Node** ortak){
	int i,m,n,key,rnd,ind1,ind2;
	Node *tmp1 = NULL;
	Node *tmp2 = NULL;
	Node *tmp = NULL;
	printf("n degerini giriniz:");
	scanf("%d", &n);
	printf("m degerini giriniz:");
	scanf("%d", &m);
	while ((2*m-1 > n) || (m < 3)){
		printf("Hatali giris lutfen tekrar veri giriniz. Unutmayin n >= 2*m-1 ve m > 3 olmali.\nn degerini giriniz:");
		scanf("%d", &n);
		printf("m degerini giriniz:");
		scanf("%d", &m);
	}
	key = (rand() % n) + 1;
	rnd = rand() % m;
	ind1 = rnd;
	*head1 = createCog(n,m,key,rnd,*ortak);
	do{
		rnd = rand() % m;
	}while(ind1 == rnd);
	ind2 = rnd;
	*head2 = createCog(n,m,key,rnd,*ortak);
	tmp1 = *head1;
	tmp2 = *head2;
	do{/* burada 1 ve 2.carklardaki ortak degerleri buluyorum. bu degerler ile 3.carkta bunlarin tekrar etmesini onleyebilirim.*/
		do{
			if(tmp1->data == tmp2->data){
				tmp = createNode(tmp1->data);
				tmp->next = *ortak;
				*ortak = tmp;
			}
			tmp1 = tmp1->next;
		}while(tmp1 != *head1);
		tmp2 = tmp2->next;
	}while(tmp2 != *head2);
	do{
		rnd = rand() % m;
	}while((ind1 == rnd) || (ind2 == rnd));
	*head3 = createCog(n,m,key,rnd,*ortak);
	printLL(*head1);
	printf("\n");
	printLL(*head2);
	printf("\n");
	printLL(*head3);
	printf("\n");
}
int find(Node *head, int x){/* Bir elemanin linkli listedeki yerini bulan fonksiyon */
	Node *tmp = head;
	int counter = 0;
	if (tmp != NULL){
		do{
			if(tmp->data == x){
				return counter;
			}
			else{
				counter++;
				tmp = tmp->next;
			}
		}while(tmp != NULL && tmp != head);/*hem dairesel linkli listede hem de normal linkli listede çalismasi icin boyle yaptim*/
	}
	return -1;/*eger bulamazsa -1 degeri donuyor*/
}
void printLL(Node *head){ /* listeyi printleyen fonksiyon*/
	Node *tmp = head;
	do{
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}while (tmp != head);
}
int keyFinder(Node *head1, Node *head2, Node *head3){
	Node *temp = head1;
	while((find(head2,temp->data) < 0) || (find(head3,temp->data) < 0)){/*tek tek gezerek ortak sayiyi bulmaya calisiyor*/
		temp = temp->next;
	}
	printf("Ortak sayi:%d\n1.carktaki konumu: %d\n2.carktaki konumu: %d\n3.carktaki konumu: %d", temp->data,(find(head1,temp->data)+1),(find(head2,temp->data)+1),(find(head3,temp->data)+1));
	return temp->data;
}
void rotateClockwise(Node** head, int donmeSayisi){/*dairesel linkli listede headi saat yonunun tersine dondurmek icin headi dondurmek istedigimiz sayi kadar ileri tasiyabiliriz.Ayrica saat yonunde cevirmek icin ise uzunluk - donus sayisi kadar saat yonunde cevirebiliriz.*/
	Node *temp = *head;
	int len=0,i;
	do{
		len++;
		temp = temp->next;
	}while(temp != *head);
	for(i=0;i<len-donmeSayisi;i++){
		*head = (*head)->next;
	}
}
void rotateAntiClockwise(Node** head, int donmeSayisi){
	int i;
	for(i = 0; i < donmeSayisi; i++){
		*head = (*head)->next;
	}	
}
void rotationNumbers(Node** head1, Node** head2, Node** head3,int key){/*Hangi yone kac defa donmesi gerektigini bulup donduren fonksiyon*/
	int pos,rot2,rot3,len=0,i;
	Node *temp = *head1;
	pos = find(*head1,key);
	rot2= find(*head2,key);
	rot3= find(*head3,key);
	do{
		len++;
		temp = temp->next;
	}while(temp != *head1);
	if(pos > rot2){
		if((pos-rot2) <  (len - pos + rot2)){
			printf("2.cark Saat yonunde %d adim cevirilmeli.\n", pos-rot2);
			rotateClockwise(head2,pos-rot2);
		}
		else{
			printf("2.cark Saatin tersi yonunde %d adim cevirilmeli.\n", len-pos+rot2);
			rotateAntiClockwise(head2,len-pos+rot2);
		}
	}else{
		if((rot2-pos) <  (len - rot2 + pos)){
			printf("2.cark Saatin tersi yonunde %d adim cevirilmeli.\n", rot2-pos);
			rotateAntiClockwise(head2,rot2-pos);
		}
		else{
			printf("2.cark Saat yonunde %d adim cevirilmeli.\n", len - rot2 + pos);
			rotateClockwise(head2,len - rot2 + pos);
		}
	}
	if(pos > rot3){
		if((pos-rot3) <  (len - pos + rot3)){
			printf("3.cark Saat yonunde %d adim cevirilmeli.\n", pos-rot3);
			rotateClockwise(head3,pos-rot3);
		}
		else{
			printf("3.cark Saatin tersi yonunde %d adim cevirilmeli.\n", len-pos+rot3);
			rotateAntiClockwise(head3,len-pos+rot3);
		}
	}else{
		if((rot3-pos) <  (len - rot3 + pos)){
			printf("3.cark Saatin tersi yonunde %d adim cevirilmeli.\n", rot3-pos);
			rotateAntiClockwise(head3,rot3-pos);
		}
		else{
			printf("3.cark Saat yonunde %d adim cevirilmeli.\n", len - rot3 + pos);
			rotateClockwise(head3,len - rot3 + pos);
		}
	}
	printLL(*head1);
	printf("\n");
	printLL(*head2);
	printf("\n");
	printLL(*head3);
}
