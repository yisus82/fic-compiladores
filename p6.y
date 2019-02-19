%{
#include <stdio.h>
char car='\0';
int error=1;
%}

%%

axioma             :       noters '+' noters {error=0;}
		   |       axioma '*' {error=0;}  
		   |       noters {error=0;}   
		   ;
noters             :       noters '.' noterp
		   |	   noterp
		   ;
noterp		   :	   '(' axioma ')'  
		   |	   'a' 
		   |       'b'
		   |	   'c'
		   ;

%%

yylex() {
           char c;
           c=getchar();
	   if ((c=='\n') && (car!='$')) {if (car=='\n') exit(0);
						else {if (car!='\0') {
								if (error) printf("\nEntrada no valida\n\n");
								else {
									printf("\nEntrada valida\n\n");
									error=1;
								}
						   	}
						      c=getchar();
						      if (c=='\n') exit(0);
						}
				}
	   if (c=='$'){
			if (error) printf("\nEntrada no valida\n\n");
				else {
					printf("\nEntrada valida\n\n");
					error=1;
				}
			c=getchar();
			if (c=='\n') {
				c=getchar();
				if (c=='\n') exit(0);
			  }
		      }
	   
           car=c;
           return c;
       }
