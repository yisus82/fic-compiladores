#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#define DIG 0
#define SIGNO 1
#define EXPO 2
#define PUNTO 3
#define DOLAR 4

int potencia (int base, int exponente) {
        int resultado=1;
        int i;
        for (i=0;i<exponente;i++) {
                resultado=resultado*base;
        }
        return resultado;
}

int main(int argc,char * argv[]){

int estado=0,car,entrada,matriz[9][5],exp=0,n=0,sn=0,se=0,e=0,dec=0,fin=0,i,j,error=0;
double salida;
unsigned int num=0;

for (i=0;i<9;i++) for (j=0;j<5;j++) if (i!=8) matriz[i][j]=-1;
								else matriz[i][j]=0;

matriz[0][DIG]=2;
matriz[0][SIGNO]=1;
matriz[0][PUNTO]=3;
matriz[1][DIG]=2;
matriz[1][PUNTO]=3;
matriz[2][DIG]=2;
matriz[2][DOLAR]=0;
matriz[2][EXPO]=5;
matriz[2][PUNTO]=3;
matriz[3][DIG]=4;
matriz[3][PUNTO]=8;
matriz[4][DIG]=4;
matriz[4][EXPO]=5;
matriz[4][DOLAR]=0;
matriz[4][PUNTO]=8;
matriz[5][DIG]=7;
matriz[5][SIGNO]=6;
matriz[5][EXPO]=10;
matriz[5][PUNTO]=9;
matriz[6][DIG]=7;
matriz[6][EXPO]=10;
matriz[6][PUNTO]=9;
matriz[7][DIG]=7;
matriz[7][EXPO]=10;
matriz[7][PUNTO]=9;
matriz[7][DOLAR]=0;

while(1){

	if (estado==8) {
				printf("\nNo se pueden poner dos o mas puntos\n");
    				error=1;
    				}
    				
    	if (estado==9) {
				printf("\nNo se pueden poner puntos en el exponente\n");
    				error=1;
    				}
    				
    	if (estado==10) {
				printf("\nNo se pueden poner dos o mas 'E'('e')\n");
    				error=1;
    				}
    				

 	car=getchar();

	if ((car>='0')&&(car<='9')) entrada=DIG;
		else if ((car=='-')||(car=='+')) entrada=SIGNO;
			else if ((car=='e')||(car=='E')) entrada=EXPO;
				else if (car=='.') entrada=PUNTO;
					else if (car=='$') {
										if (error) {
													estado=0;
													error=0;
												}
										entrada=DOLAR;
									}
        					 else if (car==10) {
        							if (estado!=0) printf("\nEntrada no valida\n");
        							exit(0);
								}
							else {
								printf("\nEntrada no valida\n");
								exit(0);
							}
							
	switch(entrada){

  		case DIG:
			if ((estado==0)||(estado==1)||(estado==2)) num=num*10+(car-48);
			if ((estado==3)||(estado==4)) {
					n++;
					num=num*10+(car-48);
				}
			if ((estado==5)||(estado==6)||(estado==7)) exp=exp*10+(car-48);
			
			break;

		case SIGNO:
			if (estado==0) {
					if (car=='+') sn=1;
						else if (car=='-') sn=2;
					}

			if (estado==5) {
					if (car=='+') se=1;
						else if (car=='-') se=2;
					}
											
			break;

		case EXPO:
			if ((estado==2)||(estado==4)) e=1;

			break;

		case PUNTO:
			if ((estado==0)||(estado==1)||(estado==2)) dec=1;

			break;

		case DOLAR:
			if ((estado==2)||(estado==4)||(estado==7)) {
					salida=num;
					salida=salida/potencia(10,n);
					if (se==2) salida=salida/potencia(10,(exp));
						else salida=salida*potencia(10,(exp));
					if(sn==2) printf("\n-");
						else if(sn==1) printf("\n+");	
							else printf("\n");
					printf("%E\n", salida);
					exp=0;
					n=0;
					sn=0;
					se=0;
					e=0;
					dec=0;
					fin=0;
					salida=0;
					num=0;
				}
	}
	
	if (estado!=-1) estado=matriz[estado][entrada];
}

}
