#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int entero(char c){

	if (c=='S') return(0);
	if (c=='A') return(1);
	if (c=='B') return(2);
	if (c=='a') return(3);
	if (c=='b') return(4);
	if (c=='c') return(5);
	if (c=='d') return(6);
	return(7);
}

main (){

char tabla[8][8],aux[100],aux2[10],entrada[100],c;
int salir=0,error=0,i,j,k,l;

for (i=0;i<8;i++) for (j=0;j<8;j++) tabla[i][j]=' ';

tabla[1][3]='=';
tabla[1][5]='=';
tabla[2][3]='>';
tabla[2][5]='>';
tabla[3][1]='=';
tabla[3][4]='<';
tabla[3][5]='<';
tabla[4][1]='<';
tabla[4][2]='=';
tabla[4][4]='<';
tabla[4][5]='<';
tabla[5][3]='>';
tabla[5][5]='>';
tabla[5][6]='=';
tabla[6][3]='>';
tabla[6][5]='>';

while(1) {

	for (i=0;i<100;i++) {
		aux[i]='\0';
		aux2[(i/10)]='\0';
	}
	error=0;
	gets(entrada);

	if (!(strcmp(entrada,""))) if (salir) exit(0);
					else {
						salir=1;
						continue;
					}

	salir=1;

	printf("\n");
	printf("<");
	aux[0]='<';
	j=1;

	for (i=0;i<strlen(entrada)-1;i++) {
		printf("%c",entrada[i]);
		aux[j++]=entrada[i];
		c=tabla[entero(entrada[i])][entero(entrada[i+1])];
		if (c==' ') error=1;
		printf("%c",c);
		aux[j++]=c;
	}

	printf("%c>\n\n",entrada[i]);
	if (entero(entrada[i])==7) error=1;
	aux[j++]=entrada[i];
	aux[j++]='>';

	if (!error) {
		for (i=0;i<strlen(aux);i++) {
			if (aux[i]=='>') {
				for (j=i;j>-1;j--) {
					if (aux[j]=='<') break;
				}
				if (j>-1) break;
			}
		}
	}

	if ((i==strlen(aux)) || (j==-1)) error=1;

	k=0;

	if (!error) {
		for (l=j+1;l<i;l++) aux2[k++]=aux[l];
		printf("Pivote: %s\n\n",aux2);
		while(1) {
			c=' ';
			if (!(strcmp(aux2,"A=a=A"))) c='S';
			if (!(strcmp(aux2,"b=B"))) c='A';
			if (!(strcmp(aux2,"A=c"))) c='B';
			if (!(strcmp(aux2,"c=d"))) c='B';
			if (c==' ') error=1;
			if (!error) {
				if (j>0) aux[j]=tabla[entero(aux[j-1])][entero(c)];
				if (aux[j]==' ') error=1;
				aux[j+1]=c;
				if (i<strlen(aux)-1) aux[i]=tabla[entero(c)][entero(aux[i+1])];
				if (aux[i]==' ') error=1;
				k=i;
				for (l=j+2;l<strlen(aux);l++) aux[l]=aux[k++];
			}
			if (!error) { 
				for (i=0;i<strlen(aux);i++) {
					if (aux[i]=='>') {
						for (j=i;j>-1;j--) {
							if (aux[j]=='<') break;
						}
						if (j>-1) break;
					}
				}
			}
			if ((i==strlen(aux)) || (j==-1)) error=1;
			if (error) break;
			k=0;
			for (l=j+1;l<i;l++) aux2[k++]=aux[l];
			printf("%s\n\n",aux);
			if (!(strcmp(aux,"<S>"))) break;
			printf("Pivote: %s\n\n",aux2);
		}
	}

	if (!error) printf("Entrada valida\n\n");
		else printf("Entrada no valida\n\n");

}

}