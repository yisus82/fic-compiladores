#include <stdio.h>
#include <string.h>
#include <stdlib.h>

main(){

int tabla[6][9],p=1,seguir=1,accion=0,aux=0,entrada=-1,salir=0,i,j,error=0;
char pila[100],car='\0',carant='\0';

pila[0]='$';
pila[1]='E';

for (i=0;i<6;i++) for (j=0;j<9;j++) tabla[i][j]=-1;

tabla[0][1]=1;
tabla[0][2]=1;
tabla[0][3]=1;
tabla[0][4]=1;
tabla[1][0]=5;
tabla[1][5]=5;
tabla[1][6]=4;
tabla[1][8]=5;
tabla[2][1]=6;
tabla[2][2]=6;
tabla[2][3]=6;
tabla[2][4]=6;
tabla[3][0]=8;
tabla[3][5]=8;
tabla[3][6]=8;
tabla[3][7]=7;
tabla[3][8]=8;
tabla[4][1]=10;
tabla[4][2]=11;
tabla[4][3]=12;
tabla[4][4]=9;
tabla[5][0]=3;
tabla[5][5]=3;
tabla[5][8]=2;


while(1){

	if (seguir) {

			  car=getchar();
			  seguir=0;

			  if ((car=='$') && (error)) {
				printf("\nNo es expresion regular\n\n");
				error=0;
				seguir=1;
				aux=0;
				p=1;
				pila[0]='$';
				pila[1]='E';
				carant=car;
				continue;
			  }

			  if (car=='$') {entrada=0; salir=0;}
			     else if (car=='a') {entrada=1; salir=0;}
				else if (car=='b') {entrada=2; salir=0;}
				    else if (car=='c') {entrada=3; salir=0;}
					else if (car=='(') {entrada=4; salir=0;}
					    else if (car==')') {entrada=5; salir=0;}
						else if (car=='+') {entrada=6; salir=0;}
						   else if (car=='.') {entrada=7; salir=0;}
							 else if (car=='*') {entrada=8; salir=0; }
								else if (car=='\n') {
											if (salir) exit(0);
												else {
													salir=1;
													seguir=1;
													error=0;
													aux=0;
													p=1;
													pila[0]='$';
													pila[1]='E';
													if (((carant!='$')&&(carant!='\0'))||(error)) printf("\nNo es expresion regular\n\n");
													carant=car;
													continue;
													}
										     }
										else {
											error=1;
											salir=0;
											seguir=1;
											carant=car;
											continue;
										}
	}

	carant=car;

	if (pila[p]=='E') aux=0;
		else if (pila[p]=='S') aux=1;
			else if (pila[p]=='R') aux=2;
				else if (pila[p]=='Q') aux=3;
					else if (pila[p]=='P') aux=4;
						else if (pila[p]=='T') aux=5;

	accion=tabla[aux][entrada];

	if (accion==-1) {
		error=1;
		seguir=1;
		continue;
	}

	if (car==pila[p]) {
		p--;
		seguir=1;
		if (car=='$') {
				if (!error) printf("\nEs expresion regular\n\n");
					else {
						printf("\nNo es expresion regular\n\n");
						error=0;
					}
				aux=0;
				p=1;
				pila[0]='$';
				pila[1]='E';
				carant=car;
			}
		continue;
	}

	switch(accion) {

		case 1: pila[p]='T';
			pila[++p]='S';
			pila[++p]='R';
			break;

		case 2: pila[++p]='*';
			break;

		case 3: p--;
			break;

		case 4: pila[p]='S';
			pila[++p]='R';
			pila[++p]='+';
			break;

		case 5: p--;
			break;

		case 6: pila[p]='Q';
			pila[++p]='P';
			break;

		case 7: pila[p]='Q';
			pila[++p]='P';
			pila[++p]='.';
			break;

		case 8: p--;
			break;

		case 9: pila[p]=')';
			pila[++p]='E';
			pila[++p]='(';
			break;

		case 10: pila[p]='a';
			 break;

		case 11: pila[p]='b';
			 break;

		case 12: pila[p]='c';
			 break;

	}

}

}
