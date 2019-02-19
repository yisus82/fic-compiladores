
%%

linea		:	axioma '\n'	{printf("%c\n",$1);}
axioma		:	noterc noterc
noterc		:	'c' noterc
		|	'd'
		;

%%

yylex() {
	char c;
	c=getchar();
	return c;
	}	
