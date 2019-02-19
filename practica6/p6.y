%{
#include <stdio.h>
char car='\0';
%}

%%

linea		   :	   axioma '\n' {printf("\nEntrada valida\n\n");
					yyparse();}
axioma             :       noters '+' noters 
		   |       axioma '*'  
		   |       noters    
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

int yyerror(char *s) {
	printf("\nEntrada no valida\n\n");
	return (1);
}

yylex() {
           char c;
           c=getchar();
	   if (c=='\n') if (car=='\n') exit(0);
	   			else if (car=='\0') {
	   				car=c;
	   				c=getchar();
	   				if (c=='\n') exit(0);
	   			}
	   car=c;
           return c;
       }
