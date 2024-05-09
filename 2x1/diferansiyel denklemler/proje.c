#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*double lossFunc(int w[], int ohv[],int dictLen, int sampleLen){
	
}*/
int main(){
	clock_t t;
	char dict[1600][50];
	char temp[500];
	int ohv[200][1600] = {0};
	double w1[1600]={0},w2[1600]={0},w3[1600]={0};
	char* tempw; /*strtok için temp bir pointer*/
	int i=0,j,f=0,k,dictLen,sampleLen,y,l,u;
	double loss,product=0,out,lRate=0.01,error=0,eps=1,sum,oldLoss,oldOut,acc,random,mhat,vhat,b1=0.9,b2=0.999,e=0.00000001,m[200]={0},v[200]={0},grad[200]={0},timeVar;
	FILE *fptr,*write,*write2,*write3,*write4;
	srand(time(NULL));
	fptr = fopen("text.txt", "r");
	while(fgets(temp,400,fptr)){ /*Her satiri tek tek alip bosluklarla ayirip sozlugu olusturma*/
		temp[strcspn(temp, "\n")] = 0;/*fgets new line charini da katiyor, bunu duzeltmek icin*/
		tempw = strtok(temp," ");
		while(tempw != NULL){
			f=0;
			for(j=0;j<i;j++){
				if(strcmp(tempw,dict[j]) == 0){
					f=1;
				}
			}
			if(f==0){
				strcpy(dict[i],tempw);
				i++;
			}
			tempw = strtok(NULL, " ");
		}	
	}
	dictLen = i;
	printf("%d",dictLen);
	for(j=0;j<dictLen;j++){
		printf("%s ",dict[j]);
	}
	printf("\n");
	rewind(fptr); /*dosyanin basina don*/
	i=0;
	while(fgets(temp,400,fptr)){ /*Her satiri tek tek alip bosluklarla ayirip sozlugu olusturma*/
		temp[strcspn(temp, "\n")] = 0;/*fgets new line charini da katiyor, bunu duzeltmek icin*/
		tempw = strtok(temp," ");
		j=0;
		while(tempw != NULL){
			f=0;
			k=0;
			while(k<dictLen && f==0){
				if(strcmp(tempw,dict[k]) == 0){
					f=1;
					ohv[i][k] = 1;
				}
				k++;
			}
			tempw = strtok(NULL, " ");
		}
		i++;
	}
	sampleLen = i;
	for(u=0;u<5;u++){
		printf("\nIter: %d\n",u+1);
	
		for(i=0;i<dictLen;i++){
			random = (-1 + rand() % 3)*0.05;
			w1[i] = random;
			w2[i] = random;
			w3[i] = random;
		}
		/*for(i=0;i<dictLen;i++){
			printf("%f ", w[i]);
		}*/
		k=0;
		eps=1;
		oldLoss=10;
		write = fopen("write.txt","a");
		write2 = fopen("write2.txt","a");
		write3 = fopen("write3.txt","a");
		write4 = fopen("write4.txt","a");
		t= clock();
		while(eps>0.00001){
			acc=0;
			for(i=0;i<sampleLen;i++){
				if(i<(sampleLen/2) * 80/100 ) {
					product = 0;
					for(j=0;j<dictLen;j++){
						product += w1[j] * ohv[i][j];
					}
					out = tanh(product);
					if(i > sampleLen/2){
						y = -1;
					}
					else{
						y = 1;
					}
					eps = out-y;
					for(j=0;j<dictLen;j++){
						w1[j] -= lRate  * ohv[i][j] * eps * (1-out*out);
					}
				}
				else if(i<(sampleLen/2) * 90/100*2 && i>(sampleLen/2) * 80/100 ){
					product = 0;
					for(j=0;j<dictLen;j++){
						product += w1[j] * ohv[i][j];
					}
					out = tanh(product);
					if(i > sampleLen/2){
						y = -1;
					}
					else{
						y = 1;
					}
					eps = out-y;
					for(j=0;j<dictLen;j++){
						w1[j] -= lRate  * ohv[i][j] * eps * (1-out*out) ;
					}
				}
			}
			loss=0;
			for(j=0;j<sampleLen;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w1[i] * ohv[j][i];
					
				}
				if(j<101){
					loss += pow((1-tanh(sum)),2);
				}
				else{
					loss += pow((-1-tanh(sum)),2);
				}
	
			}
			acc=0;
			for(j=80;j<100;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w1[i] * ohv[j][i];
				}
				if(tanh(sum)>0){
					acc += 1;
				}
			}
			for(j=180;j<200;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w1[i] * ohv[j][i];
				}
				if(tanh(sum)>0){
				}
				else{
					acc += 1;
				}
				
			}
			acc /= 40;
			loss = loss/sampleLen;		
			
			eps = fabs(loss-oldLoss);
			oldLoss = loss;
			k++;
			timeVar = ((double)clock()-t)/CLOCKS_PER_SEC;
			fprintf(write, "%d %f %f\n",k,loss,timeVar);
			for(j=0;j<dictLen;j++){
				fprintf(write3,"%f ", w1[j]);
			}
			fprintf(write3,"\n");
		}
		fprintf(write3,"\nEND\n");
		
		printf("\nGD loss: %f acc: %f batch:%d time:%f ",loss,acc*100,k,timeVar);
		/*sgd*/
		k=0;
		out=0;
		eps=1;
		oldLoss=100;
		t = clock();
		while(eps>0.00001){
				
				acc=0;
				do{
					i = rand()%200;
				}while((i>80 && i<100) || (i>180 && i<200));
				
				if(i<(sampleLen/2) * 80/100 ) {
					product = 0;
					for(j=0;j<dictLen;j++){
						product += w2[j] * ohv[i][j];
					}
					out = tanh(product);
					if(i > sampleLen/2){
						y = -1;
					}
					else{
						y = 1;
					}
					eps = out-y;
					for(j=0;j<dictLen;j++){
						w2[j] -= lRate  * ohv[i][j] * eps * (1-out*out) ;
					}
				}
				else if(i<(sampleLen/2) * 90/100*2 && i>(sampleLen/2) * 80/100 ){
					product = 0;
					for(j=0;j<dictLen;j++){
						product += w2[j] * ohv[i][j];	
					}
					out = tanh(product);
					if(i > sampleLen/2){
						y = -1;
					}
					else{
						y = 1;
					}
					eps = out-y;
					for(j=0;j<dictLen;j++){
						w2[j] -= lRate  * ohv[i][j] * eps * (1-out*out) ;
					}
				}
				loss=0;
			for(j=0;j<sampleLen;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w2[i] * ohv[j][i];
					
				}
				if(j<101){
					loss += pow((1-tanh(sum)),2);
				}
				else{
					loss += pow((-1-tanh(sum)),2);
				}
	
			}
			acc=0;
			for(j=80;j<100;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w2[i] * ohv[j][i];
				}
				if(tanh(sum)>0){
					acc += 1;
				}

			}
			for(j=180;j<200;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w2[i] * ohv[j][i];
				}
				if(tanh(sum)>0){
	
				}
				else{
					acc += 1;
				}
				
			}
			acc /= 40;
			loss = loss/sampleLen;		
			
			eps = fabs(loss-oldLoss);
			oldLoss = loss;
			k++;
			timeVar = ((double)clock()-t)/CLOCKS_PER_SEC;
			for(j=0;j<dictLen;j++){
				fprintf(write4,"%f ",w2[j]);
			}
			fprintf(write4,"\n");
			fprintf(write2, "%d %f %f\n",k,loss,timeVar);
		}
		fprintf(write4,"\nEND\n");
		printf("\nSGD loss: %f acc: %f batch:%d time:%f ",loss,acc*100,k,timeVar);
		/*adam*/
		k=0;
		oldLoss=0;
		eps=10;
		while(eps>0.0001){
			acc=0;
			for(l=0;l<sampleLen/20;l++){
				product = 0;
				do{
					i = rand()%200;
				}while((i>80 && i<100) || (i>180 && i<200));
				if(i<(sampleLen/2) * 80/100 ) {
					for(j=0;j<dictLen;j++){
						product += w3[j] * ohv[i][j];
					}
					out = tanh(product);
					/*printf("%f %f",out,product);*/
					eps = out - 1+e;
					for(j=0;j<sampleLen;j++){
						grad[j] = eps * ohv[i][j]+e; 
						
					}
					for(j=0;j<sampleLen;j++){
						m[j] = m[j]*b1 +(1-b1)*grad[j];
						v[j] = v[j]*b2 +(1-b2)*grad[j]*grad[j];
		
					}
					
					mhat = m[j]/(1-pow(b1,k+1));
					vhat = v[j]/(1-pow(b2,k+1));
					for(j=0;j<sampleLen;j++){
						w3[j] -= lRate  * mhat/(sqrt(vhat) + e);
					}
				}
				else if(i<(sampleLen/2) * 90/100*2 && i>(sampleLen/2) * 80/100 ){
					for(j=0;j<dictLen;j++){
						product += w3[j] * ohv[i][j];
					}
					out = tanh(product);
					/*printf("%f %f",out,product);*/
					eps = out + 1+e;
					for(j=0;j<sampleLen;j++){
						grad[j] = eps * ohv[i][j]+e; 
					}
					for(j=0;j<sampleLen;j++){
						m[j] = m[j]*b1 +(1-b1)*grad[j];
						v[j] = v[j]*b2 +(1-b2)*grad[j]*grad[j];
	
					}
					mhat = m[j]/(1-pow(b1,k+1));
					vhat = v[j]/(1-pow(b2,k+1));
					for(j=0;j<sampleLen;j++){
						w3[j] -= lRate  * mhat/(sqrt(vhat) + e);
					}
				}
			}
			loss=0;
			for(j=0;j<sampleLen;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w3[i] * ohv[j][i];
					/*printf("%f ",sum);*/
				}
				if(j<100){
					loss += pow((1-tanh(sum)),2);
				}
				else{
					loss += pow((-1-tanh(sum)),2);
				}
				/*printf("%f ",loss);*/
			}
			acc=0;
			for(j=80;j<100;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w3[i] * ohv[j][i];
				}
				if(tanh(sum)>0){
					acc += 1;
				}
				else{
					acc += -1;
				}
			}
			for(j=180;j<200;j++){
				sum=0;
				for(i=0;i<dictLen;i++){
					sum += w3[i] * ohv[j][i];
				}
				if(tanh(sum)>0){
					acc += -1;
				}
				else{
					acc += 1;
				}
				
			}
			acc /= 40;
			loss = loss/sampleLen;		
			
			eps = fabs(loss-oldLoss);
			oldLoss = loss;
			k++;
		}
		printf("\nADAM: %f %f %f batch:%d",out,loss,acc,k);
	}
	return 0;
}
