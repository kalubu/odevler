#include <stdio.h>
#include <stdlib.h>

struct Node{/*node yapisi*/
	int dest;
	struct Node* next;
};

struct Node* createNode(int val){
	struct Node* temp =(struct Node*)malloc(sizeof(struct Node));
	temp->dest = val;
	temp->next = NULL;
	return temp;
}
struct course{/*komsuluk listesi yapisi*/
	struct Node *head;
	int indeg;
	int del;
};

void createEdge(struct course* graph, int from, int to){
	struct Node* temp = createNode(to);
	if(graph[from].head == NULL){
		graph[from].head = temp;
	}
	else{
		temp->next = graph[from].head;
		graph[from].head = temp;
	}
}


void printCourses(struct course* graph,int n,int semester){
	int i;
	printf("%d.Donem:",semester+1);
	for(i=0;i<n;i++){
		if(graph[i].indeg == 0){
			printf("Course-%d  ", i+1);
		}
	}
}
int main(){
	int i,j,n,d=0,semester = 0;
	int **A;
	struct course *graph;
	struct Node *temp=NULL;
	printf("Ders sayisini giriniz:");
	scanf("%d", &n);
	graph = (struct course*)malloc(n * sizeof(struct course));/*komsuluk listelerinden olusan bir array*/
	for(i=0;i<n;i++){
		graph[i].head = NULL;
		graph[i].indeg = 0;
	}
	
	A =(int **)malloc(n * sizeof(int*));/*komsuluk matrisini almak icin dinamik bir matris*/
	for(i=0;i<n;i++){
		A[i] = (int *)malloc(n * sizeof(int));
	}
	printf("Komsuluk matrisini giriniz:\n");
	for(i = 0;i<n;i++){
		for(j = 0;j<n;j++){
			printf("%d.satirin %d.sutunu:",i+1,j+1);
			scanf("%d", &A[i][j]);
		}
	}
	printf("\n");
	for(i=0;i<n;i++){
		for(j = 0;j<n;j++){
			if(A[i][j] == 1){
				createEdge(graph, i, j);
			}
		}
	}
	for(i=0;i<n;i++){
		temp = graph[i].head;
		while(temp){/*indegreee hesabi*/
			graph[temp->dest].indeg++; 
			temp = temp->next;
		}
	}

	while(d<n){/*d: alinan ders sayisi*/
		printCourses(graph,n,semester);
		printf("\n");
		for(j=0;j<n;j++){
			if(graph[j].indeg == 0){/*O donem alabilecegi dersleri isaretliyorum*/
				graph[j].del = 1;
			}	
		}
		for(j=0;j<n;j++){
			if(graph[j].del == 1){/*Alinabilecek tum dersleri almasini sagliyorum*/
				temp = graph[j].head;
				while(temp){/*Aldigi ders baska bir dersin onsarti ise o derslerin indegreesini 1 azaltiyorum*/
					graph[temp->dest].indeg--;
					temp = temp->next;
			}
			graph[j].indeg = -1;/*Alinan derslerin indegini -1 yapiyorum. Boylece ders bir nevi algoritmadan cikmis oluyor.*/
			graph[j].del = -1;/*Ayni sekilde del degerini de -1 yapiyorum*/
			d++;
		}
	}
	semester++;
	}
	printf("Bu ogrenci bolumu %d donemde bitirir.", semester);
	return 0;
}
