%{
  char salida[100];
  int error=0;
  int salir=0;
  int i;
%}
digito	[0-9]
exp	[E e]
signo	[+ -]
punto	[.]
dolar	[$]
salir	[\n]
%%
{signo}?({digito}*{punto})?{digito}+({exp}{signo}?{digito}+)?{dolar} {
        for (i=0;i<100;i++) salida[i]='\0';
        strncpy(salida,yytext,yyleng-1);
        if (error) {
			error=0;
			printf("\nEntrada no valida\n\n");
		}
	    else printf("\n%s es un numero valido\n\n",salida);
	salir=0;
  }   						
{salir} {
	if (error) {
			error=0;
			printf("\nEntrada no valida\n\n");
		}
	if (salir) exit(0);
	   else salir=1;
	}
. {error=1; salir=0;}
%%
main()
{
    yylex();
}
