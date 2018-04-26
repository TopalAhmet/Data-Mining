#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main(){
	//k en yakin komsu yontemi
	//8124-fold cross validation icin yapilmistir.
	printf("K en yakin komsu yontemi,K=8124(Leave-one-out) icin\n");
	int ozniteliksayisi=23,orneksayisi=8124,komsusayisi;
	int similarity[orneksayisi],sirali[orneksayisi];
	char mushroom[orneksayisi][ozniteliksayisi];
	int dogrusiniflandirma=0,yanlissiniflandirma=0,benzerlik=0,dogru=0,yanlis=0;
	int i,j,k,t,u,v,tmp;
	char actualclass,predictedclass;
	int sayac1=0,sayac2=0,sayac3=0,sayac4=0;
	//Her ornegin diger orneklerle benzerliginin bulunmasi ayni ornek karsilastirmasi icin benzerlik sifir olarak aliniyor.
	FILE *fp;
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
	printf("En yakin kac komsuya bakilsin:");
	scanf("%d",&komsusayisi);
	for(i=0;i<orneksayisi;i++){
	printf("%d. hesaplandi\n",(i+1));
		actualclass=mushroom[i][0];
		for(k=0;k<orneksayisi;k++){
			if(k!=i){
			for(j=1;j<ozniteliksayisi;j++){
				
					if(mushroom[i][j]==mushroom[k][j])
					benzerlik++;
				
			}
		}
			similarity[k]=benzerlik;
			benzerlik=0;
		}
		
		
		for(u=0;u<orneksayisi;u++){
			if(u<komsusayisi) {
			
			
			sirali[u]=u;
			for(v=u+1;v<orneksayisi;v++){
				if(similarity[v]>similarity[u]){
			
				tmp=similarity[u];
				similarity[u]=similarity[v];
				similarity[v]=tmp;
				sirali[u]=v;
			}
				
				
			}
		}
	}
	
	
		for(t=0;t<komsusayisi;t++){
			predictedclass=mushroom[sirali[t]][0];
			if(predictedclass==actualclass)
			dogru++;
			else
			yanlis++;
		}
		if(dogru>yanlis)
		dogrusiniflandirma++;
		else
		yanlissiniflandirma++;
		if(actualclass=='p' && dogru>yanlis)
		sayac1++;
		if(actualclass=='p' && dogru<yanlis)
		sayac2++;
		if(actualclass=='e' && dogru>yanlis)
		sayac3++;
		if(actualclass=='e' && dogru<yanlis)
		sayac4++;
		dogru=0;
		yanlis=0;
		
	}
	
	//Hesaplama islemlerinin yapilmasi
	
	float basarimorani=(float)(dogrusiniflandirma*100)/(float)orneksayisi;
//	float yuzde=basarimorani/orneksayisi;
	
	printf("Dogru siniflanan ornek sayisi:%d",dogrusiniflandirma);
	printf("\n");
	printf("Yanlis siniflanan ornek sayisi:%d",yanlissiniflandirma);
	printf("\n");
	printf("Siniflama basarim orani:%.2f\n\n",basarimorani);
	printf(":::::::::::::::::::::::::Class Confusion Matrix::::::::::::::::::::::::::::");
	printf("\t\t Class p");printf("\t Class e\n\n");
	printf("Class p");
	printf("     %d",sayac1);printf("\t%5d",sayac2);
	printf("\n\nClass e");
	printf("     %d",sayac4);printf("\t%15d",sayac3);
		return 0;
	
}

void Clustering(Edge gr[],int label[],int vertexCount,int clusterNums){
	int zeroCount=0;
	int currentclass=0;
	int labelcount=0;
	int stop=0;
	int j,k,uu,vv;
	for(k=0;k<vertexCount;k++) 
		label[k]=0;
		
	j=0;
	while(!stop){
		uu=gr[j].u;
		vv=gr[j].v;
		zeroCount=0;
		if(label[uu]+label[vv]==0){
			labelcount++;
			currentclass++;
			label[uu]=labelcount;
			label[vv]=labelcount;
			j++;
		}
		else{
			if(label[uu]!=label[vv]){
			j++;
				if(label[uu]==0){
					for(k=0;k<vertexCount;k++) {
						if(label[k]==0)zeroCount++;
					}
					if(clusterNums-currentclass==zeroCount){
						currentclass++;
						labelcount++;
						label[uu]=labelcount;
						
					}
					else{
						label[uu]=label[vv];
					}
				}
				else{
					if(label[vv]==0){
						for(k=0;k<vertexCount;k++) {
						if(label[k]==0)zeroCount++;
					}
					if(clusterNums-currentclass==zeroCount){
						currentclass++;
						labelcount++;
						label[vv]=labelcount;
						
					}
					else{
						label[vv]=label[uu];
						
					}
				}
				else{
					if(currentclass>clusterNums){
						int value=label[uu];
						for(k=0;k<vertexCount;k++){
							if(label[k]==value)
							label[k]=label[vv];
							currentclass--;
							
						}
					}
					
				}
			}
	}
			else j++;
		}
		stop=flag(label,vertexCount,0);
	}
	arrangeAndPrint(label,vertexCount,labelcount);
}
