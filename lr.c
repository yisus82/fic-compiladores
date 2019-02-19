#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ACEPTAR 100
#define des(n) n+100 //desplazar n
#define red(n) n+200 //reducir por la regla n

main(){

int tabla[10][3],ir_a[10][2],p=0,seguir=1,accion=0,aux=0,entrada=-1,salir=0,i,j,error=0;
char pila[100],car='\n',carant='$';

pila[0]='0';

for (i=0;i<10;i++) {
			for (j=0;j<2;j++) tabla[i][j]=-1;
			tabla[i][j]=1;
		}

for (i=0;i<10;i++) for (j=0;j<2;j++) ir_a[i][j]=-1;

tabla[0][0]=des(3);
tabla[0][1]=des(4);
ir_a[0][0]=1;
ir_a[0][1]=2;
tabla[1][2]=ACEPTAR;
tabla[2][0]=des(6);
tabla[2][1]=des(7);
ir_a[2][1]=5;
tabla[3][0]=des(3);
tabla[3][1]=des(4);
ir_a[3][1]=8;
tabla[4][0]=red(3);
tabla[4][1]=red(3);
tabla[5][2]=red(1);
tabla[6][0]=des(6);
tabla[6][1]=des(7);
tabla[7][2]=red(3);
ir_a[6][1]=9;
tabla[8][0]=red(2);
tabla[8][1]=red(2);
tabla[9][2]=red(2);


while(1){ 

	if (seguir) {

	                   car=getchar();	
	                   seguir=0;

	                   if (car=='c') {entrada=0; salir=0;}
		              else if (car=='d') {entrada=1; salir=0;}
		        	  else if (car=='$') {entrada=2; salir=0;}
					else if (car=='\n') {
								if (salir) exit(0);
									else {
										if (carant!='$') printf("\nEntrada no valida\n\n");
										salir=1;
										seguir=1;
										error=0;
										p=0;
										pila[0]='0';
										continue;
									}
							}
						else {
							error=1;
							salir=0;
							seguir=1;
							continue;
						}

	}

	carant=car;

	aux=pila[p]-'0';
	accion=tabla[aux][entrada];

	if (accion==-1) {
		error=1;
		seguir=1;
		continue;
	}
	
	if (accion==1) {
		printf("\nEntrada no valida\n\n");
		error=0;
		seguir=1;
		p=0;
		pila[0]='0';
		continue;
	}

	switch(accion) {

		//ACEPTAR

		case 100: printf("\nEntrada valida\n\n");
			  p=0;
			  pila[0]='0';
			  seguir=1;
			  error=0;
			  accion=0;
			  break;

		//DESPLAZAR 3

		case 103: pila[++p]=car;
			  pila[++p]='3';
			  seguir=1;
			  break;

		//DESPLAZAR 4

		case 104: pila[++p]=car;
			  pila[++p]='4';
			  seguir=1;
			  break;

		//DESPLAZAR 6

		case 106: pila[++p]=car;
			  pila[++p]='6';
			  seguir=1;
			  break;

		//DESPLAZAR 7

		case 107: pila[++p]=car;
			  pila[++p]='7';
			  seguir=1;
			  break;

		//REDUCIR POR LA REGLA 1 (S->CC)

		case 201: for (i=p-1;i>2;i=i-2) if ((pila[i]=='C')&&(pila[i-2]=='C')) {
							i=i-2;
							p=i;
							pila[p++]='S';
							break;
						}
     			  if (i<1) {    
				    error=1;
				    continue;
			  }
			  pila[p]=ir_a[(pila[i-1]-'0')][0]+'0';
			  break;

		//REDUCIR POR LA REGLA 2 (C->cC)

		case 202: for (i=p-1;i>2;i=i-2) if ((pila[i]=='C')&&(pila[i-2]=='c')) {
							i=i-2;
							p=i;
							pila[p++]='C';
							break;
						}
			  if (i<1) {  
					error=1;
					continue;
				}
			  pila[p]=ir_a[(pila[i-1]-'0')][1]+'0';
			  break;

		//REDUCIR POR LA REGLA 3 (C->d)

		case 203: for (i=p-1;i>0;i=i-2) if (pila[i]=='d') {
							p=i;
							pila[p++]='C';
							break;
						}
			  if (i<1) {  
					error=1;
					continue;
				}
			  pila[p]=ir_a[(pila[i-1]-'0')][1]+'0';
			  break;

	}

}

}
