#include <stdio.h>
#include <stdlib.h>

typedef struct urun{
	int kod;
	char ad[20];
	float birimfiyat;
	float kilofiyat;
}urun;

void urunleriListele(urun* list, int n){
	int i;
	printf("Kod\tÜrün Adi\tBirim Fiyat\tKilo Fiyat\n");
	for(i=0;i<n;i++){
		printf("%d\t%s\t%.2fTL\t%.2fTL\n",list[i].kod,list[i].ad,list[i].birimfiyat,list[i].kilofiyat);
	}
}

float tutarHesap(urun* list,int kod, int type, int n){
	float sum;
	if(type == 1){
		sum = list[kod-1].birimfiyat *n;
	}
	else{
		sum = list[kod-1].kilofiyat *n;
	}
	return sum;
}

void indirimHesap(float* toplam){
	if((*toplam) >50 && (*toplam) <100){
		*toplam = *toplam * 95/100;
	}
	else if((*toplam) > 100){
		*toplam = *toplam * 90/100;
	}
}

int main(){
	int f=1,pick,type,count;
	char cont;
	float toplam=0;
	urun *urunliste;
	urunliste = calloc(6,sizeof(urun));
	urunliste[0] = ((urun) {1,"domates",8.25,23.75});
	urunliste[1] = ((urun) {2,"biber",6.25,29.50});
	urunliste[2] = ((urun) {3,"süt",15.85,27.15});
	urunliste[3] = ((urun) {4,"peynir",23.00,95.59});
	urunliste[4] = ((urun) {5,"muz",13.45,45.50});
	urunliste[5] = ((urun) {6,"armut",5.50,20.15});

	while(f){
		urunleriListele(urunliste,6);
		
		do{
			printf("Urun kodu giriniz:");
			scanf("%d",&pick);
			if(pick>6 || pick <1){
				printf("Hatali Giris\n");
			}
		}while(pick>6 || pick <1);

		do{
			printf("Alis tipi(1:Birim, 2:Kilo):");
			scanf("%d",&type);
			if(type<1 || type > 2){
				printf("Hatali Giris");
			}
		}while(type<1 || type > 2);
		
		printf("Miktari giriniz:");
		scanf("%d",&count);
		toplam += tutarHesap(urunliste,pick,type,count);
		printf("Toplam tutar: %.2fTL\n",toplam);
		printf("Devam etmek istiyor musunuz?(E/H):");
		scanf(" %c",&cont);
		
		if(cont == 'H'){
			f=0;
		}
	}
	printf("Toplam tutar: %.2fTL\n",toplam);
	indirimHesap(&toplam);
	printf("Indirimli tutar: %.2fTL\nProgramdan cikis yapiliyor",toplam);
	return 0;
}
