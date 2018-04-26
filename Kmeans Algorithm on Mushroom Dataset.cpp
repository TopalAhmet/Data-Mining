#include<stdio.h>

int main(){
	int ozniteliksayisi=23,orneksayisi=8124;
	char centroid1[ozniteliksayisi-1],centroid2[ozniteliksayisi-1];
	char mushroom[orneksayisi][ozniteliksayisi];
	int cluster1sayac,cluster2sayac;
	int similarity1,similarity2;
	int cluster1[8124],cluster2[8124];
	int gecicitekrar,encoktekrar=0;
	int i,j,k,d,t,s;
	FILE *fp,*fp2;
	int max_iteration;
	
	if((fp=fopen("dataset.txt","r"))==NULL){
		printf("Dosya acma hatasi");
	}
		fseek(fp,0,SEEK_SET);
		
	for(i=0;i<orneksayisi;i++){
			
		for(j=0;j<ozniteliksayisi;j++){
		
			fscanf(fp,"%c",&mushroom[i][j]);
			if(mushroom[i][j]==',' || mushroom[i][j]=='\n')
			j--;
		}
	
	}
	for(i=0;i<orneksayisi;i++){
			
		for(j=0;j<ozniteliksayisi;j++){
			if(mushroom[i][j]=='?')
			mushroom[i][j]='b';
		}
	}
	//cluster merkezlerinin rastgele belirlenmesi
	/*for(i=0;i<ozniteliksayisi-1;i++){
		centroid1[i]=mushroom[1996][i+1];
		centroid2[i]=mushroom[1854][i+1];
	}*/
	
	//Weka'da kullanilan baslangic noktalarinin okunmasi
	if((fp2=fopen("wekaveri.txt","r"))==NULL){
		printf("Dosya acma hatasi");
	}
		fseek(fp2,0,SEEK_SET);
		
	
			
		for(j=0;j<ozniteliksayisi-1;j++){
		
			fscanf(fp2,"%c",&centroid1[j]);
			if(centroid1[j]==',' || centroid1[j]=='\n')
			j--;
		}
		for(j=0;j<ozniteliksayisi-1;j++){
		
			fscanf(fp2,"%c",&centroid2[j]);
			if(centroid2[j]==',' || centroid2[j]=='\n')
			j--;
		}
	
	
	
	
	
	printf("Starting Centroid of Cluster1:");
	for(i=0;i<ozniteliksayisi-1;i++)
	printf("%c,",centroid1[i]);
	printf("\n");
	printf("Starting Centroid of Cluster2:");
	for(i=0;i<ozniteliksayisi-1;i++)
	printf("%c,",centroid2[i]);
	printf("\n");
	
	printf("Maksimum iterasyon sayisini giriniz:");
	scanf("%d",&max_iteration);
	for(d=0;d<max_iteration;d++){
		printf("%d. iterasyon hesaplandi\n",(d+1));
	cluster1sayac=0;
	cluster2sayac=0;
	//tum orneklerin cluster1 ve cluster2 olarak benzerliklerine gore kumelenmesi
	for(i=0;i<orneksayisi;i++){
		similarity1=0;
		similarity2=0;
		for(j=1;j<ozniteliksayisi;j++){
			if(mushroom[i][j]==centroid1[j-1])
			similarity1++;
			if(mushroom[i][j]==centroid2[j-1])
			similarity2++;
		}
		if(similarity1>similarity2){
			cluster1[cluster1sayac]=i;cluster1sayac++;
		}
		else if(similarity1<similarity2){
			cluster2[cluster2sayac]=i;cluster2sayac++;
		}
		else{
			cluster1[cluster1sayac]=i;cluster1sayac++;
		}
	}
	
	char karsilastirma1[cluster1sayac];
	char karsilastirma2[cluster2sayac];
	//Centroid1'in merkez noktalarinin tekrar hesaplanmasi
	for(j=1;j<ozniteliksayisi;j++){
		encoktekrar=0;
		for(i=0;i<cluster1sayac;i++){
			karsilastirma1[i]=mushroom[cluster1[i]][j];
			
		}
	
		
		for(t=0;t<cluster1sayac;t++){
			gecicitekrar=0;
			for(s=0;s<cluster1sayac;s++){
				if(karsilastirma1[t]==karsilastirma1[s])
				gecicitekrar++;
			}
			if(gecicitekrar>encoktekrar){
				encoktekrar=gecicitekrar;
				centroid1[j-1]=karsilastirma1[t];
			}
			
		}
	
	}
	
	//Centroid2'nin merkez noktalarinin hesaplanmasi	
	for(j=1;j<ozniteliksayisi;j++){
		encoktekrar=0;
		for(i=0;i<cluster2sayac;i++){
			karsilastirma2[i]=mushroom[cluster2[i]][j];
			
		}
		
		for(t=0;t<cluster2sayac;t++){
			gecicitekrar=0;
			for(s=0;s<cluster2sayac;s++){
				if(karsilastirma2[t]==karsilastirma2[s])
				gecicitekrar++;
			}
			if(gecicitekrar>encoktekrar){
				encoktekrar=gecicitekrar;
				centroid2[j-1]=karsilastirma2[t];
			}
			
		}
	
	}
}
	
	
	
	float oran1=((float)cluster1sayac/(float)orneksayisi)*100;
	float oran2=((float)cluster2sayac/(float)orneksayisi)*100;
	printf("\n");
	printf("Final Centroid of Cluster1:");
	for(i=0;i<ozniteliksayisi-1;i++)
	printf("%c,",centroid1[i]);
	printf("\n");
	printf("Final Centroid of Cluster2:");
	for(i=0;i<ozniteliksayisi-1;i++)
	printf("%c,",centroid2[i]);
	printf("\n");
	printf("\n");
	printf("Clsuter1'e kumelenen ornek sayisi:%d\n",cluster1sayac);
	printf("Cluster1'e kumelenen ornek sayisi orani:%.2f",oran1);
	printf("\n");
	printf("Clsuter2'e kumelenen ornek sayisi:%d\n",cluster2sayac);
	printf("Cluster2'e kumelenen ornek sayisi orani:%.2f",oran2);
	return 0;
}
