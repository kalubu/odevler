#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int siparis;
	int id;
	char isim[40];
	char urunTip[40];
	char siparisGun[40];
	struct musteri *next;
	
}musteri;

musteri *read(char* fname){
	FILE *fp =fopen(fname,"r");
	int i=0;
	char buffer[10000];
	char line[100];
	char *token;
	int min=9999;
	musteri *head=NULL;
	musteri *temp,*temp2;
	fread(buffer,sizeof(buffer),1,fp);
	printf("%s",buffer);
	token = strtok(buffer, " \n");
	while(token!=NULL){
		musteri *node = (musteri*)malloc(sizeof(musteri));
		node->siparis = atoi(token);
		token = strtok(NULL, " \n");
		node->id = atoi(token);
		token = strtok(NULL, " \n");
		strcpy(node->isim,token);
		token = strtok(NULL, " \n");
		strcpy(node->urunTip,token);
		token = strtok(NULL, " \n");
		strcpy(node->siparisGun,token);
		token = strtok(NULL, " \n");
		if(head == NULL || head->id > node->id){
			node->next=head;
			head = node;
		}
		else{
			temp = head;
			while(node->id > temp->id && temp->next != NULL){
				temp = temp->next;
			}
			node->next = temp->next;
			temp->next = node;
			
		}
		
	}
	return head;
	}
int main(){
	FILE *fp;
	musteri* head = read("input.txt");
	musteri* temp;
	temp = head;
	while(temp){
		printf("%d %d %s %s %s\n", temp->id,temp->siparis,temp->isim,temp->urunTip,temp->siparisGun);
		fp = fopen("temp->isim","w+");
		fprintf(fp,"Merhaba %s %s günü tarafizidan siparis numarasi %d olan müsteri id %d olan %s alisverisi gerceklestirmistir. iyi günler", temp->isim,temp->siparisGun,temp->siparis,temp->id,temp->urunTip);
		temp = temp->next;
		
		
	}
	
	
	
	return 0;
}
