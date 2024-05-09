#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct Node{
	char data[MAX];
	int last;
	struct Node* child[10];
	
}trie;

trie* createNode(){
	int i;
	trie* temp = (trie*)malloc(sizeof(trie));
	temp->last = 0;
	for(i=0;i<10;i++){
		temp->child[i] = NULL;
	}
	return temp;
}

void insert(trie* root, char* word){
	int i=0,val,f=0;
	trie* temp = root;
	while(word[i] != '\0'){
		if(word[i] == 'a' || word[i] == 'b' || word[i] == 'c'){
			val = 2;
		}
		else if(word[i] == 'd' || word[i] == 'e' || word[i] == 'f'){
			val = 3;
		}
		else if(word[i] == 'g' || word[i] == 'h' || word[i] == 'i'){
			val = 4;
		}
		else if(word[i] == 'j' || word[i] == 'k' || word[i] == 'l'){
			val = 5;
		}
		else if(word[i] == 'm' || word[i] == 'n' || word[i] == 'o'){
			val = 6;
		}
		else if(word[i] == 'p' || word[i] == 'q' || word[i] == 'r' || word[i] == 's'){
			val = 7;
		}
		else if(word[i] == 't' || word[i] == 'u' || word[i] == 'v'){
			val = 8;
		}
		else if(word[i] == 'w' || word[i] == 'x' || word[i] == 'y' || word[i] == 'z'){
			val = 9;
		}
		if(temp->child[val] == NULL){
			temp->child[val] = createNode();
			f=1;
		}
		temp = temp->child[val];
		i++;
	}
	
	if(f==0){
		if(temp->last==1){
			while(temp->child[0]!=NULL){
					temp = temp->child[0];
				}
			temp->child[0] = createNode();
			temp = temp->child[0];
		}
	}
	
	i = 0;
	while(word[i] != '\0'){
		temp->data[i] = word[i];
		i++;
	}
	temp->data[i] = '\0';
	temp->last = 1;
}
void search(trie* root, int key){
	trie* temp = root;
	int keyTemp,bas,i;

	while(key>0){
		bas=0;
		keyTemp=key;
		while(keyTemp>=10){
			keyTemp = keyTemp / 10;
			bas++;
		}
		temp = temp->child[keyTemp];
		if(temp == NULL){
			printf("Sozlukte bu sayinin kelime karsiligi yoktur.\n");
			return;
		}
		for(i=0;i<bas;i++){
			keyTemp *=10;
		}
		key -=keyTemp;
	}
	if(temp->last==1){
		printf("%s\n",temp->data);
	}
	else{
		printf("Sozlukte bu sayinin kelime karsiligi yoktur.\n");
	}
	
	while(temp->child[0] !=NULL){
		temp = temp->child[0];
		printf("%s\n",temp->data);
	}
	
}

int main(){
	char input[MAX];
	int key;
	trie* root = createNode();
	FILE *read = fopen("dict.txt", "r");
	while(!feof(read)){
		fscanf(read,"%s", input);
		/*printf("%s ", input);*/
		insert(root, input);
    }
    printf("\nCikmak icin 0 yaziniz.\n");
    do{
    	scanf("%d",&key);
		search(root,key);
		printf("\n");
	}while(key != 0);

	return 0;
}
