#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char *tabla_simbolos[2][100];
int pos_int=0,pos_bool=0,linea=0;


int busca_variable(char *variable,int tipo) {
	int i,encontrada=0;
	
	if (tipo) {
			for(i=0;i<pos_bool;i++) {
				if (!strcmp(tabla_simbolos[tipo][i],variable)) {
					encontrada=1;
					break;
				} 
			}
	}
		else for(i=0;i<pos_int;i++) {
				if (!strcmp(tabla_simbolos[tipo][i],variable)) {
					encontrada=1;
					break;
				} 
		}
	
	return encontrada;
}

void comenta (int n) {
	int i,j;
	char sentencia[255],*tokens[25];
	
	while(1) {
		gets(sentencia);
		tokens[0] = strtok(sentencia," ");
		i=1;
		while(tokens[i++]=strtok(NULL," "));

		if (tokens[0]==NULL) {
				printf("\n");
				linea++;
				continue;
		}
		
		for (j=0;j<(i-2);j++) printf("%s ",tokens[j]);
		
		if ((n) && (!strcmp(tokens[i-2],"}"))) {
						printf("*/\n");
						linea++;
						break;
					}
			else if ((!n) && (!strcmp(tokens[i-2],"*)"))) {
						printf("*/\n");
						linea++;
						break;
					} 
				else {
					printf("%s\n",tokens[i-2]);
					linea++;
				}
	}
}

void lee_variables() {
	int i,j;
	char sentencia[255],*tokens[25],*variables[10];

	while(1) {
		gets(sentencia);
		tokens[0] = strtok(sentencia," ");
		i=1;
		while(tokens[i++]=strtok(NULL," "));
		linea++;

		if (tokens[0]==NULL) 	continue;
						
		if (!strcmp(tokens[0],"begin")) {
			if ((i-2)>0) {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"'begin' no puede llevar nada a su derecha\n");
				exit(1);
			}
			if (!(pos_int || pos_bool)) {
					fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
					fprintf(stderr,"No se ha declarado ninguna variable\n");
					fprintf(stderr,"Ejemplo de utilizacion de la clausula var:\n\n");
					fprintf(stderr,"var\nvariable1,variable2 : tipo1\nvariable3,variable4 : tipo2\n");
					exit(1);
			}
			printf("int main(int argc,char *argv[]) {\n\n");
			if (pos_int) {
				printf("int ");
				for (j=0;j<(pos_int-1);j++) printf("%s,",tabla_simbolos[0][j]);
				printf("%s;\n",tabla_simbolos[0][j]);
			}
			if (pos_bool) {
				printf("int ");
				for (j=0;j<(pos_bool-1);j++) printf("%s,",tabla_simbolos[1][j]);
				printf("%s;\n",tabla_simbolos[1][j]);
			}
			break;
		}

		if (((i-2)!=2) || (strcmp(tokens[1],":"))) {
					fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
					fprintf(stderr,"Ejemplo de utilizacion de la clausula var:\n\n");
					fprintf(stderr,"var\nvariable1,variable2 : tipo1\nvariable3,variable4 : tipo2\n");
					exit(1);
		}

		if ((strcmp(tokens[2],"integer;")) && (strcmp(tokens[2],"boolean;"))) {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"Los unicos tipos de datos validos son entero(integer) y booleano(boolean)\n");
				exit(1);
		}

		variables[0]=strtok(tokens[0],",");
		i=1;
		while(variables[i++]=strtok(NULL,","));

		if (!strcmp(tokens[2],"integer;")) {
			for (j=0;j<(i-1);j++) {
					if (pos_int==100) {
							fprintf(stderr,"\nNo se pueden meter mas variables de tipo entero(integer) en la tabla de simbolos\n");
							break;
					}
					if (busca_variable(variables[j],0)) {
							fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
							fprintf(stderr,"La variable %s ya ha sido declarada\n",variables[j]);
							exit(1);
					}
						else if (busca_variable(variables[j],1)) {
							fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
							fprintf(stderr,"La variable %s ya ha sido declarada con tipo boolean\n",variables[j]);
							exit(1);
						}
					tabla_simbolos[0][pos_int]=(char *) malloc(strlen(variables[j])*sizeof(char));
					strcpy(tabla_simbolos[0][pos_int],variables[j]);
					pos_int++;
			}
			continue;
		}

		for (j=0;j<(i-1);j++) {
				if (pos_bool==100) {
						fprintf(stderr,"\nNo se pueden meter mas variables de tipo booleano(boolean) en la tabla de simbolos\n");
						break;
					}
				if (busca_variable(variables[j],1)) {
							fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
							fprintf(stderr,"La variable %s ya ha sido declarada\n",variables[j]);
							exit(1);
				}
					else if (busca_variable(variables[j],0)) {
							fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
							fprintf(stderr,"La variable %s ya ha sido declarada con tipo integer\n",variables[j]);
							exit(1);
					}
				tabla_simbolos[1][pos_bool]=(char *) malloc(strlen(variables[j])*sizeof(char));
				strcpy(tabla_simbolos[1][pos_bool],variables[j]);
				pos_bool++;
		}
	}
}

int main() {

int i,j,fase=0,bloques=0,ifs=0,reps=0,pars=0;
char sentencia[255],*tokens[25];

printf("#include <sys/types.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <fcntl.h>\n\n");

while (1) {

	gets(sentencia);
	tokens[0]=strtok(sentencia," ");
	i=1;
	while(tokens[i++]=strtok(NULL," "));
	linea++;
	
	if (tokens[0]==NULL) {
			printf("\n");
			continue;
	}

	if ((tokens[1]) && (!strcmp(tokens[1],":="))) {
		if (fase<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Las asignaciones deben ir despues del primer 'begin'\n");
			exit(1);
		}
		if (!(tokens[2])) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de las asignaciones:\n\n");
			fprintf(stderr,"variable := expresion;\n");
			exit(1);
		}
		if (busca_variable(tokens[0],0)) {
			printf("%s = ",tokens[0]);
			for (j=2;j<(i-2);j++) {
				if ((atoi(tokens[j])) || (!strcmp(tokens[j],"0"))) printf("%s ",tokens[j]);
					else if (busca_variable(tokens[j],0)) printf("%s ",tokens[j]);
							else if (!strcmp(tokens[j],"(")) {
													printf("( ");
													pars++;
												}
									else if (!strcmp(tokens[j],")")) {
															if (pars) {
																	printf(") ");
																	pars--;
															}
																else {
																	fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																	fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																	exit(1);
																}
														}
										else if (!strcmp(tokens[j],"div")) printf("/ ");
											else if (!strcmp(tokens[j],"mod")) printf("% ");
												else if ((!strcmp(tokens[j],"+")) || (!strcmp(tokens[j],"-")) || (!strcmp(tokens[j],"*")) || (!strcmp(tokens[j],"/"))) printf("%s ",tokens[j]);
													else {
														fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
														fprintf(stderr,"Token no valido: %s\n",tokens[j]);
														exit(1);
													}
			}
			if (tokens[i-2][strlen(tokens[i-2])-1]==';') {
				tokens[i-2][strlen(tokens[i-2])-1]='\0';
				if ((atoi(tokens[i-2])) || (!strcmp(tokens[i-2],"0"))) printf("%s ",tokens[i-2]);
					else if (busca_variable(tokens[i-2],0)) printf("%s ",tokens[i-2]);
							else if (!strcmp(tokens[i-2],"(")) {
													printf("( ");
													pars++;
												}
									else if (!strcmp(tokens[i-2],")")) {
															if (pars) {
																	printf(") ");
																	pars--;
															}
																else {
																	fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																	fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																	exit(1);
																}
														}
										else if (!strcmp(tokens[i-2],"div")) printf("/ ");
											else if (!strcmp(tokens[i-2],"mod")) printf("% ");
												else if ((!strcmp(tokens[i-2],"+")) || (!strcmp(tokens[i-2],"-")) || (!strcmp(tokens[i-2],"*")) || (!strcmp(tokens[i-2],"/"))) printf("%s ",tokens[i-2]);
													else {
														fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
														fprintf(stderr,"Token no valido: %s;\n",tokens[i-2]);
														exit(1);
													}
				printf(";\n");
				continue;
			}
				else {
					if ((atoi(tokens[j])) || (!strcmp(tokens[j],"0"))) printf("%s ",tokens[j]);
						else if (busca_variable(tokens[j],0)) printf("%s ",tokens[j]);
							else if (!strcmp(tokens[j],"(")) {
													printf("( ");
													pars++;
												}
									else if (!strcmp(tokens[j],")")) {
															if (pars) {
																	printf(") ");
																	pars--;
															}
																else {
																	fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																	fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																	exit(1);
																}
														}
										else if (!strcmp(tokens[j],"div")) printf("/ ");
											else if (!strcmp(tokens[j],"mod")) printf("% ");
												else if ((!strcmp(tokens[j],"+")) || (!strcmp(tokens[j],"-")) || (!strcmp(tokens[j],"*")) || (!strcmp(tokens[j],"/"))) printf("%s ",tokens[j]);
													else {
														fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
														fprintf(stderr,"Token no valido: %s\n",tokens[j]);
														exit(1);
													}
					printf(";\n");
					if (pars) {
							fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
							fprintf(stderr,"Faltan %d parentesis por cerrar\n",pars);
							exit(1);
					}
					continue;
				}
		}
		else if (busca_variable(tokens[0],1)) {
			printf("%s = ",tokens[0]);
			for(j=2;j<(i-2);j++) {
				if ((!strcmp(tokens[j],"0")) || (atoi(tokens[j]))) printf("%s ",tokens[j]);
					else if (!strcmp(tokens[j],"and")) printf("&& ");
						else if (!strcmp(tokens[j],"or")) printf("|| ");
								else if(!strcmp(tokens[j],"true")) printf("1 ");
									else if (!strcmp(tokens[j],"false")) printf("0 ");
										else if (!strcmp(tokens[j],"=")) printf("== ");
											else if (!strcmp(tokens[j],"<>")) printf("!= ");
												else if ((!strcmp(tokens[j],"<")) || (!strcmp(tokens[j],"<=")) || (!strcmp(tokens[j],">")) || (!strcmp(tokens[j],">=")) || (busca_variable(tokens[j],0)) || (busca_variable(tokens[j],1))) printf("%s ",tokens[j]);
													else if (!strcmp(tokens[j],"(")) {
																	printf("( ");
																	pars++;
														}
														else if (!strcmp(tokens[j],")")) {
																	if (pars) {
																			printf(") ");
																			pars--;
																	}
																		else {
																			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																			fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																			exit(1);
																		}
																}
															else {
																fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																fprintf(stderr,"Token no valido: %s\n",tokens[j]);
																exit(1);
															}
			}
			if (tokens[i-2][strlen(tokens[i-2])-1]==';') {
				tokens[i-2][strlen(tokens[i-2])-1]='\0';
				if ((!strcmp(tokens[i-2],"0")) || (atoi(tokens[i-2]))) printf("%s ",tokens[i-2]);
					else if (!strcmp(tokens[i-2],"and")) printf("&& ");
						else if (!strcmp(tokens[i-2],"or")) printf("|| ");
							else if(!strcmp(tokens[i-2],"true")) printf("1 ");
								else if (!strcmp(tokens[i-2],"false")) printf("0 ");
									else if (!strcmp(tokens[i-2],"=")) printf("== ");
											else if (!strcmp(tokens[i-2],"<>")) printf("!= ");
												else if ((!strcmp(tokens[i-2],"<")) || (!strcmp(tokens[i-2],"<=")) || (!strcmp(tokens[i-2],">")) || (!strcmp(tokens[i-2],">=")) || (busca_variable(tokens[i-2],0)) || (busca_variable(tokens[i-2],1))) printf("%s ",tokens[i-2]);
													else if (!strcmp(tokens[i-2],"(")) {
																	printf("( ");
																	pars++;
														}
														else if (!strcmp(tokens[i-2],")")) {
																	if (pars) {
																			printf(") ");
																			pars--;
																	}
																		else {
																			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																			fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																			exit(1);
																		}
																}
																else {
																	fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																	fprintf(stderr,"Token no valido: %s;\n",tokens[i-2]);
																	exit(1);
																}
			}
				else {
					if ((!strcmp(tokens[j],"0")) || (atoi(tokens[j]))) printf("%s ",tokens[j]);
						else if (!strcmp(tokens[j],"and")) printf("&& ");
							else if (!strcmp(tokens[j],"or")) printf("|| ");
								else if(!strcmp(tokens[j],"true")) printf("1 ");
									else if (!strcmp(tokens[j],"false")) printf("0 ");
										else if (!strcmp(tokens[j],"=")) printf("== ");
											else if (!strcmp(tokens[j],"<>")) printf("!= ");
													else if ((!strcmp(tokens[j],"<")) || (!strcmp(tokens[j],"<=")) || (!strcmp(tokens[j],">")) || (!strcmp(tokens[j],">=")) || (busca_variable(tokens[j],0)) || (busca_variable(tokens[j],1))) printf("%s ",tokens[j]);
														else if (!strcmp(tokens[j],"(")) {
																		printf("( ");
																		pars++;
															}
															else if (!strcmp(tokens[j],")")) {
																		if (pars) {
																				printf(") ");
																				pars--;
																		}
																			else {
																				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																				fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																				exit(1);
																			}
																	}
																else {
																	fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																	fprintf(stderr,"Token no valido: %s\n",tokens[j]);
																	exit(1);
																}
				}
			printf(";\n");
			if (pars) {
					fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
					fprintf(stderr,"Faltan %d parentesis por cerrar\n",pars);
					exit(1);
			}
			continue;	
		}
			else {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"La variable %s no esta definida\n",tokens[0]);
				exit(1);
			}
	}

	if (!strcmp(tokens[0],"if")) {
		if (fase<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"La sentencia 'if' debe ir despues del primer 'begin'\n");
			exit(1);
		}
		if ((i-2)<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'if':\n\n");
			fprintf(stderr,"if condicion then\nsentencia\nelse\nsentencia;\n");
			exit(1);
		}
		if (strcmp(tokens[i-2],"then")) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'if-then-else':\n\n");
			fprintf(stderr,"if condicion then\nsentencia\nelse\nsentencia;\n");
			exit(1);
		}
		printf("if ");
		for(j=1;j<(i-2);j++) {
			if ((!strcmp(tokens[j],"0")) || (atoi(tokens[j]))) printf("%s ",tokens[j]);
				else if (!strcmp(tokens[j],"and")) printf("&& ");
					else if (!strcmp(tokens[j],"or")) printf("|| ");
							else if(!strcmp(tokens[j],"true")) printf("1 ");
								else if (!strcmp(tokens[j],"false")) printf("0 ");
									else if (!strcmp(tokens[j],"=")) printf("== ");
											else if (!strcmp(tokens[j],"<>")) printf("!= ");
												else if ((!strcmp(tokens[j],"<")) || (!strcmp(tokens[j],"<=")) || (!strcmp(tokens[j],">")) || (!strcmp(tokens[j],">=")) || (busca_variable(tokens[j],0)) || (busca_variable(tokens[j],1))) printf("%s ",tokens[j]);
													else if (!strcmp(tokens[j],"(")) {
																	printf("( ");
																	pars++;
														}
														else if (!strcmp(tokens[j],")")) {
																	if (pars) {
																			printf(") ");
																			pars--;
																	}
																		else {
																			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																			fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																			exit(1);
																		}
																}
															else {
																fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																fprintf(stderr,"Token no valido: %s\n",tokens[j]);
																exit(1);
														}
		}
		if (pars) {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"Faltan %d parentesis por cerrar\n",pars);
				exit(1);
		}
		ifs++;
		continue;
	}

	if (!strcmp(tokens[0],"else")) {
		if (fase<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"La sentencia 'else' debe ir despues del primer 'begin'\n");
			exit(1);
		}
		if ((i-2)>0) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"'else' no puede llevar nada a su derecha\n");
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'if-then-else':\n\n");
			fprintf(stderr,"if condicion then\nsentencia\nelse\nsentencia;\n");
			exit(1);
		}
		if (!ifs) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"No hay ningun 'if' para cerrar\n");
			exit(1);
		}
		printf("else\n");
		ifs--;
		continue;
	}

	if (!strcmp(tokens[0],"for")) {
		if (fase<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"La sentencia 'for' debe ir despues del primer 'begin'\n");
			exit(1);
		}
		if ((i-2)!=6) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'for':\n\n");
			fprintf(stderr,"for variable := valor_inicial {downto|to} valor_final do\nsentencia;\n");
			exit(1);
		}
		if (!busca_variable(tokens[1],0)) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"La variable %s no esta declarada con tipo integer\n",tokens[1]);
			exit(1);
		}
		if (strcmp(tokens[2],":=")) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'for':\n\n");
			fprintf(stderr,"for variable := valor_inicial {downto|to} valor_final do\nsentencia;\n");
			exit(1);
		}
		if ((!atoi(tokens[3])) && (strcmp(tokens[3],"0")) && (!busca_variable(tokens[3],0))) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'for':\n\n");
			fprintf(stderr,"for variable := valor_inicial {downto|to} valor_final do\nsentencia;\n");
			exit(1);
		}
		if ((strcmp(tokens[4],"downto")) && (strcmp(tokens[4],"to"))) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'for':\n\n");
			fprintf(stderr,"for variable := valor_inicial {downto|to} valor_final do\nsentencia;\n");
			exit(1);
		}
		if ((!atoi(tokens[5])) && (strcmp(tokens[5],"0")) && (!busca_variable(tokens[5],0))) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'for':\n\n");
			fprintf(stderr,"for variable := valor_inicial {downto|to} valor_final do\nsentencia;\n");
			exit(1);
		}		
		if (strcmp(tokens[6],"do")) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'for':\n\n");
			fprintf(stderr,"for variable := valor_inicial {downto|to} valor_final do\nsentencia;\n");
			exit(1);
		}
		printf("for(%s=%s;%s",tokens[1],tokens[3],tokens[1]);
		if (!strcmp(tokens[4],"to")) printf("<=%s;%s++)\n",tokens[5],tokens[1]);
			else printf(">=%s;%s--)\n",tokens[5],tokens[1]);
		continue;
	}

	if (!strcmp(tokens[0],"while")) {
		if (fase<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"La sentencia 'while' debe ir despues del primer 'begin'\n");
			exit(1);
		}
		if ((i-2)<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'while':\n\n");
			fprintf(stderr,"while condicion do\nsentencia;\n");
			exit(1);
		}
		if (strcmp(tokens[i-2],"do")) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'while':\n\n");
			fprintf(stderr,"while condicion do\nsentencia;\n");
			exit(1);
		}
		printf("while ");
		for(j=1;j<(i-2);j++) {
			if ((!strcmp(tokens[j],"0")) || (atoi(tokens[j]))) printf("%s ",tokens[j]);
				else if (!strcmp(tokens[j],"and")) printf("&& ");
					else if (!strcmp(tokens[j],"or")) printf("|| ");
							else if(!strcmp(tokens[j],"true")) printf("1 ");
								else if (!strcmp(tokens[j],"false")) printf("0 ");
									else if (!strcmp(tokens[j],"=")) printf("== ");
											else if (!strcmp(tokens[j],"<>")) printf("!= ");
												else if ((!strcmp(tokens[j],"<")) || (!strcmp(tokens[j],"<=")) || (!strcmp(tokens[j],">")) || (!strcmp(tokens[j],">=")) || (busca_variable(tokens[j],0)) || (busca_variable(tokens[j],1))) printf("%s ",tokens[j]);
													else if (!strcmp(tokens[j],"(")) {
																	printf("( ");
																	pars++;
														}
														else if (!strcmp(tokens[j],")")) {
																	if (pars) {
																			printf(") ");
																			pars--;
																	}
																		else {
																			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																			fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																			exit(1);
																		}
																}
															else {
																fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																fprintf(stderr,"Token no valido: %s\n",tokens[j]);
																exit(1);
															}
		}
		printf("\n");
		if (pars) {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"Faltan %d parentesis por cerrar\n",pars);
				exit(1);
		}
		continue;
	}

	if (!strcmp(tokens[0],"repeat")) {
		if (fase<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"La sentencia 'for' debe ir despues del primer 'begin'\n");
			exit(1);
		}
		if ((i-2)>0) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"'repeat' no puede llevar nada a su derecha\n");
			exit(1);
		}
		printf("do {\n");
		reps++;
		continue;
	}

	if (!strcmp(tokens[0],"until")) {
		if (fase<2) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"La sentencia 'for' debe ir despues del primer 'begin'\n");
			exit(1);
		}
		if ((i-2)<1) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Ejemplo de utilizacion de la sentencia 'until':\n\n");
			fprintf(stderr,"until condicion;\n");
			exit(1);
		}
		if (!reps) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"No hay ningun 'repeat' sin cerrar\n");
			exit(1);
		}
		printf("} while (!");
		for(j=1;j<(i-2);j++) {
			if ((!strcmp(tokens[j],"0")) || (atoi(tokens[j]))) printf("%s ",tokens[j]);
				else if (!strcmp(tokens[j],"and")) printf("&& ");
					else if (!strcmp(tokens[j],"or")) printf("|| ");
							else if(!strcmp(tokens[j],"true")) printf("1 ");
								else if (!strcmp(tokens[j],"false")) printf("0 ");
									else if (!strcmp(tokens[j],"=")) printf("== ");
											else if (!strcmp(tokens[j],"<>")) printf("!= ");
												else if ((!strcmp(tokens[j],"<")) || (!strcmp(tokens[j],"<=")) || (!strcmp(tokens[j],">")) || (!strcmp(tokens[j],">=")) || (busca_variable(tokens[j],0)) || (busca_variable(tokens[j],1))) printf("%s ",tokens[j]);
													else if (!strcmp(tokens[j],"(")) {
																	printf("( ");
																	pars++;
														}
														else if (!strcmp(tokens[j],")")) {
																	if (pars) {
																			printf(") ");
																			pars--;
																	}
																		else {
																			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																			fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																			exit(1);
																		}
																}
															else {
																fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																fprintf(stderr,"Token no valido: %s\n",tokens[j]);
																exit(1);
															}
		}
		if (tokens[i-2][strlen(tokens[i-2])-1]==';') {
			tokens[i-2][strlen(tokens[i-2])-1]='\0';
			if ((!strcmp(tokens[i-2],"0")) || (atoi(tokens[i-2]))) printf("%s ",tokens[i-2]);
				else if (!strcmp(tokens[i-2],"and")) printf("&& ");
					else if (!strcmp(tokens[i-2],"or")) printf("|| ");
							else if(!strcmp(tokens[i-2],"true")) printf("1 ");
								else if (!strcmp(tokens[i-2],"false")) printf("0 ");
									else if (!strcmp(tokens[i-2],"=")) printf("== ");
											else if (!strcmp(tokens[i-2],"<>")) printf("!= ");
												else if ((!strcmp(tokens[i-2],"<")) || (!strcmp(tokens[i-2],"<=")) || (!strcmp(tokens[i-2],">")) || (!strcmp(tokens[i-2],">=")) || (busca_variable(tokens[i-2],0)) || (busca_variable(tokens[i-2],1))) printf("%s ",tokens[i-2]);
													else if (!strcmp(tokens[i-2],"(")) {
																	printf("( ");
																	pars++;
														}
														else if (!strcmp(tokens[i-2],")")) {
																	if (pars) {
																			printf(") ");
																			pars--;
																	}
																		else {
																			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																			fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																			exit(1);
																		}
																}
															else {
																fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																fprintf(stderr,"Token no valido: %s;\n",tokens[i-2]);
																exit(1);
															}
		}
			else {
				if ((!strcmp(tokens[j],"0")) || (atoi(tokens[j]))) printf("%s ",tokens[j]);
					else if (!strcmp(tokens[j],"and")) printf("&& ");
						else if (!strcmp(tokens[j],"or")) printf("|| ");
							else if(!strcmp(tokens[j],"true")) printf("1 ");
									else if (!strcmp(tokens[j],"false")) printf("0 ");
										else if (!strcmp(tokens[j],"=")) printf("== ");
												else if (!strcmp(tokens[j],"<>")) printf("!= ");
													else if ((!strcmp(tokens[j],"<")) || (!strcmp(tokens[j],"<=")) || (!strcmp(tokens[j],">")) || (!strcmp(tokens[j],">=")) || (busca_variable(tokens[j],0)) || (busca_variable(tokens[j],1))) printf("%s ",tokens[j]);
														else if (!strcmp(tokens[j],"(")) {
																		printf("( ");
																		pars++;
															}
															else if (!strcmp(tokens[j],")")) {
																		if (pars) {
																				printf(") ");
																				pars--;
																		}
																			else {
																				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																				fprintf(stderr,"No hay ningun parentesis para cerrar\n");
																				exit(1);
																			}
																	}
																else {
																	fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
																	fprintf(stderr,"Token no valido: %s\n",tokens[j]);
																	exit(1);
																}
			}
		printf(");\n");
		if (pars) {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"Faltan %d parentesis por cerrar\n",pars);
				exit(1);
		}
		reps--;
		continue;
	}					

	if (!strcmp(tokens[0],"program")) {
		if (fase>0) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"La clausula 'program' debe ir al principio del programa\n");
			exit(1);
		}
		if ((i-2)!=1) {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"Ejemplo de utilizacion de la clausula 'program':\n\n");
				fprintf(stderr,"program nombre;\n");
				exit(1);
		}
		if (tokens[i-2][strlen(tokens[i-2])-1]==';') {
						fase=1;
						continue;
		}
			else {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"Ejemplo de utilizacion de la clausula 'program':\n\n");
				fprintf(stderr,"program nombre;\n");
				exit(1);
			}
	}

	if (!strcmp(tokens[0],"var")) {
		if (fase>1) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"Las variables deben de declararse antes del primer 'begin'\n");
			exit(1);
		}
		if ((i-2)>0) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"'var' no puede llevar nada a su derecha\n");
			exit(1);
		}
		lee_variables();
		fase=2;
		bloques++;
		continue;
	}

	if (!strcmp(tokens[0],"begin")) {
		if ((i-2)>0) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"'begin' no puede llevar nada a su derecha\n");
			exit(1);
		}
		if (fase>1) {
			printf("{\n");
			bloques++;
			continue;
		}
			else {
				printf("int main(int argc,char *argv[]) {\n\n");
				fase=2;
				bloques++;
				continue;
			}
	}
	
 	if ((!strcmp(tokens[0],"end;")) || (!strcmp(tokens[0],"end"))) {
		if ((i-2)>0) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"'end' no puede llevar nada a su derecha\n");
			exit(1);
		}													
			else if (bloques<2) {
					fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
					fprintf(stderr,"No hay ningun bloque 'begin' sin cerrar\n");
					exit(1);
			}
				else {
					printf("}\n");
					bloques--;
					continue;
				}
	}
	
	if (!strcmp(tokens[0],"end.")) {
	 	if ((i-2)>0) {
			fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
			fprintf(stderr,"'end' no puede llevar nada a su derecha\n");
			exit(1);
		}
		if (bloques>1) {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"Quedan %d bloques 'begin' sin cerrar\n",bloques-1);
				exit(1);
		}
			else if (reps) {
				fprintf(stderr,"\nError de parsing en la linea %d\n",linea);
				fprintf(stderr,"Quedan %d 'repeat' sin cerrar\n",reps);
				exit(1);
			}
				else {
					printf("exit(0);\n\n}\n\n");
					fprintf(stderr,"Traducidas %d lineas sin fallos\n",linea);
					exit(0);
				}
	}

	if (!strcmp(tokens[0],"(*")) {
		printf("/* ");
		for(j=1;j<(i-2);j++) printf("%s ",tokens[j]);
		if (!strcmp(tokens[i-2],"*)")) {
					printf("*/\n");
					continue;
		}
			else {
				printf("%s\n",tokens[i-2]);
				comenta(0);
			}
	}

	if (!strcmp(tokens[0],"{")) {
		printf("/* ");
		for(j=1;j<(i-2);j++) printf("%s ",tokens[j]);
		if (!strcmp(tokens[i-2],"}")) {
					printf("*/\n");
					continue;
		}
			else {
				printf("%s\n",tokens[i-2]);
				comenta(1);
			}
	}

}

exit(0); 

}


