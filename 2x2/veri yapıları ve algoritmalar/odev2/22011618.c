#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct treeNode *tree;
typedef struct stackNode *stack;
struct treeNode{
	int data,dmg;
	tree left,right;
};

struct stackNode {
	int data;
	stack next;
};

stack createNode(int);
void push(stack*, int);
int pop(stack*);
tree createTree(int);
tree insert(tree, int);
tree search(tree, int);
tree minVal(tree);
tree del(tree, int);
void printTree(tree);

int main(){
	tree root = NULL, target = NULL;
	stack top = NULL, top2 = NULL;
	int n,m,i,tmp,k,p,f=1;
	srand(time(NULL));
	do{
		scanf("%d", &n);
		scanf("%d", &m);
	}while(m<=0 || n<m);
	tmp = (rand() % n) + 1;
	root = insert(root, tmp);
	for (i = 1; i < m;i++){
		do{
			tmp = (rand() % n) + 1;
		}while(search(root,tmp) != NULL);
		insert(root, tmp);
	}	
	
	do{
		printTree(root);
		do{
			printf("\n");
			scanf("%d", &k);
			scanf("%d", &p);
			target = search(root,k);
			if(target == NULL){
				printf("Girdiginiz deger agacta bulunmuyor. Lutfen gecerli bir deger giriniz.");
			}
		}while(target == NULL);
		target->dmg = target->dmg + p;
		if(root->data <= root->dmg && root->left == NULL && root->right == NULL){
			f = 0;
			push(&top,root->data);
		}
		else if(target->dmg >= target->data){
			target->dmg = 0;
			push(&top,target->data);
			root = del(root,target->data);
		}
	}while(f);
	while(top != NULL){
		push(&top2,pop(&top));
	}
	while(top2 != NULL){
		printf("%d ", pop(&top2));
	}
	return 0;
}


stack createNode(int val){
	stack tmp = (stack)malloc(sizeof(struct stackNode));
	tmp->data = val;
	tmp->next = NULL;
	return tmp;
}

void push(stack* head, int val){
	stack tmp = createNode(val);
	tmp->next = *head;
	*head = tmp;
}

int pop(stack* head){
	if(*head == NULL) {
		return -1;
	}
	stack tmp = *head;
	*head = (*head)->next;
	int val = tmp->data;
	free(tmp);
	return val;
}

tree createTree(int val){
	tree tmp = (tree)malloc(sizeof(struct treeNode));
	tmp->data = val;
	tmp->dmg = 0;
	tmp->right = NULL;
	tmp->left = NULL;
	return tmp;
}

tree insert(tree a, int val){
	if(a == NULL){
		return createTree(val);
	}
	if(val < a->data){
		a->left = insert(a->left, val);
	}
	else if(val > a->data){
		a->right = insert(a->right, val);
	}
	return a;
}

tree search(tree a, int val){
	if(a == NULL){
		return NULL;
	}
	if(val < a->data){
		search(a->left, val);
	}
	else if(val > a->data){
		search(a->right, val);
	}
	else{
		return a;
	}
}

tree minVal(tree a){
	if(a && a->left){
		return minVal(a->left);
	}
	else{
		return a;
	}
}

tree del(tree a, int val){
	if(a == NULL){
		return a;
	}
	if(val < a->data){
		a->left = del(a->left, val);
	}
	else if(val > a->data){
		a->right = del(a->right, val);
	}
	else if(a->left !=NULL && a->right != NULL){
		a->data = minVal(a->right)->data;
		a->dmg = minVal(a->right)->dmg;
		a->right = del(a->right, a->data);
		
	}
	else{
		if(a->right != NULL){
			a = a->right;
		}
		else{
			a = a->left;
		}
	}
	return a;
}
void printTree(tree a){
	if (a==NULL){
		return;
	}
	printTree(a->left);
	if(a->dmg > 0){
		printf("%d(%d) ", a->data, a->data - a->dmg);
	}
	else{
		printf("%d ", a->data);
	}
	printTree(a->right);
}
