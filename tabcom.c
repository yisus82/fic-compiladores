#include <stdio.h>
#include <string.h>
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

main(){

int tabla[100][3],t=0,estado=0,entrada,valor[29],columna[29],prefil[11],numfil[11],exp=0,n=0,sn=0,se=0,e=0,dec=0,salir=0,i,j,k,error=0;
double salida;
unsigned int num=0;
char car;

for (i=0;i<100;i++) {
			tabla[i][0]=0;
			tabla[i][1]=0;
			tabla[i][2]=0;
		}

valor[0]=2;
valor[1]=1;
valor[2]=3;
valor[3]=2;
valor[4]=3;
valor[5]=2;
valor[6]=5;
valor[7]=3;
valor[8]=0;
valor[9]=4;
valor[10]=8;
valor[11]=4;
valor[12]=5;
valor[13]=8;
valor[14]=0;
valor[15]=7;
valor[16]=6;
valor[17]=10;
valor[18]=9;
valor[19]=7;
valor[20]=10;
valor[21]=9;
valor[22]=7;
valor[23]=10;
valor[24]=9;
valor[25]=0;
valor[26]=0;
valor[27]=0;
valor[28]=0;

columna[0]=0;
columna[1]=1;
columna[2]=3;
columna[3]=0;
columna[4]=3;
columna[5]=0;
columna[6]=2;
columna[7]=3;
columna[8]=4;
columna[9]=0;
columna[10]=3;
columna[11]=0;
columna[12]=2;
columna[13]=3;
columna[14]=4;
columna[15]=0;
columna[16]=1;
columna[17]=2;
columna[18]=3;
columna[19]=0;
columna[20]=2;
columna[21]=3;
columna[22]=0;
columna[23]=2;
columna[24]=3;
columna[25]=4;
columna[26]=4;
columna[27]=4;
columna[28]=4;

prefil[0]=0;
prefil[1]=3;
prefil[2]=5;
prefil[3]=9;
prefil[4]=11;
prefil[5]=15;
prefil[6]=19;
prefil[7]=22;
prefil[8]=26;
prefil[9]=27;
prefil[10]=28;

numfil[0]=3;
numfil[1]=2;
numfil[2]=4;
numfil[3]=2;
numfil[4]=4;
numfil[5]=4;
numfil[6]=3;
numfil[7]=4;
numfil[8]=1;
numfil[9]=1;
numfil[10]=1;

while(1){
	
	if (estado>7) error=estado;
			
 	car=getchar();

	if ((car>='0')&&(car<='9')) {entrada=DIG; salir=0;}
		else if ((car=='-')||(car=='+')) {entrada=SIGNO; salir=0;}
			else if ((car=='e')||(car=='E')) {entrada=EXPO; salir=0;}
				else if (car=='.') {entrada=PUNTO; salir=0;}
					else if (car=='$') {entrada=DOLAR; salir=0;}
        					 else if (car=='\n') {
        							if (salir) {
        										printf("\nParte entera\t\tParte decimal\t\tExponente\n\n");
        										for (i=0;i<t;i++) printf("%10d\t\t%10d\t\t%2d\n",tabla[i][0],tabla[i][1],tabla[i][2]);
        										printf("\n");
        										exit(0);
        								}
       								    else {
       								    	if ((estado!=0) || (error==1)) printf("\nEntrada no valida\n\n");
  									salir=1;
	   								estado=0;
	   								exp=0;
									n=0;
									sn=0;
									se=0;
									e=0;
									dec=0;
									salida=0;
									num=0;
									error=0;
									continue;
	   							 	}
								}
							else {
								error=1;
								salir=0;
								continue;
							}
	
	switch(entrada){

  		case DIG:
			if ((estado==0)||(estado==1)||(estado==2)) {
										num=num*10+(car-48);
										tabla[t][0]=tabla[t][0]*10+(car-48);
									}
			if ((estado==3)||(estado==4)) {
					n++;
					num=num*10+(car-48);
					tabla[t][1]=tabla[t][1]*10+(car-48);
				}
			if ((estado==5)||(estado==6)||(estado==7)) exp=exp*10+(car-48);
			
			break;

		case SIGNO:
			if (estado==0) {
					if (car=='+') sn=1;
						else if (car=='-') sn=2;
					}
			else if (estado==5) {
					if (car=='+') se=1;
						else if (car=='-') se=2;
					}
				else error=1;
											
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
				}
			if (estado==0) error=1;
			if (error==0) {
					if(sn==2) printf("\n-");
						else if(sn==1) printf("\n+");	
							else printf("\n");
					printf("%E\n\n", salida);
				}
				else {
					if (error==8) printf("\nNo se pueden poner dos o mas puntos => ");
 
    					if (error==9) printf("\nNo se pueden poner puntos en el exponente => ");
    			
    					if (error==10) printf("\nNo se pueden poner dos o mas 'E'('e') => ");
					
					if (error<8) printf("\n");
					
					printf("Entrada no valida\n\n");
				}
			if (sn==2) tabla[t][0]=-tabla[t][0];
			if (e) if (se==2) tabla[t][2]=-exp;
					else tabla[t][2]=exp;
			if (t==100) printf("\nNo se pueden meter mas numeros\n\n");
				else if (error==0) t++;
					else for (i=0;i<3;i++) tabla[t][i]=0;
			exp=0;
			n=0;
			sn=0;
			se=0;
			e=0;
			dec=0;
			salida=0;
			num=0;
			error=0;
	}
	
	i=prefil[estado];
	j=numfil[estado];
	for (k=0;k<j;k++) if (columna[i+k]==entrada) {
							estado=valor[i+k];
							break;
						}
}

}
