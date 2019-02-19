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

int tabla[100][3],t=0,estado=0,entrada,exp=0,n=0,sn=0,se=0,e=0,dec=0,salir=0,error=0,i;
double salida;
unsigned int num=0;
char car;

for (i=0;i<100;i++) {
			tabla[i][0]=0;
			tabla[i][1]=0;
			tabla[i][2]=0;
		}

while(1){

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
       								    	if ((estado!=0) || (error)) printf("\nEntrada no valida\n\n");
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
			if ((estado==0)||(estado==1)) {
					estado=2;
					num=num*10+(car-48);
					tabla[t][0]=tabla[t][0]*10+(car-48);
					break;
				}
			if (estado==2) {
					num=num*10+(car-48);
					tabla[t][0]=tabla[t][0]*10+(car-48);
				}	
			if (estado==3) {
					estado=4;
					n++;
					num=num*10+(car-48);
					tabla[t][1]=tabla[t][1]*10+(car-48);
					break;
				}
			if (estado==4) {
					n++;
					num=num*10+(car-48);
					tabla[t][1]=tabla[t][1]*10+(car-48);
				}
			if ((estado==5)||(estado==6)) {
							estado=7;
							exp=exp*10+(car-48);
							break;
						}
			if (estado==7)	exp=exp*10+(car-48);

			break;

		case SIGNO:
			if (estado==0) {
					estado=1;
					if (car=='+') sn=1;
						else if (car=='-') sn=2;
				}
			  else if (estado==5) {
					estado=6;
					if (car=='+') se=1;
						else if (car=='-') se=2;
				}
					else error=1;
			
			break;

		case EXPO:
			if ((estado==2)||(estado==4)) {
							estado=5;
							e=1;
						}
				else error=1;

			break;

		case PUNTO:
			if ((estado==0)||(estado==1)||(estado==2)) {
							estado=3;
							dec=1;
						}
				else error=1;

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
				else printf("\nEntrada no valida\n");
			if (sn==2) tabla[t][0]=-tabla[t][0];
			if (e) if (se==2) tabla[t][2]=-exp;
					else tabla[t][2]=exp;
			if (t==100) printf("\nNo se pueden meter mas numeros\n\n");
				else if (error==0) t++;
					else for (i=0;i<3;i++) tabla[t][i]=0;
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
	}
	
}

}
