%{
#include <stdio.h>
       int i=0;
	int num_enter=0;
     
%}

%%

linea		   :       axioma '$' '\n'        
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

yylex() {
           
	while (num_enter!=2){
	       char c;
               c=getchar();
	       i++;
	       if ((c=='\n') && (i==1)) exit(0);
	         if ((c=='$') && (i==1)) {} 	
 					 
					 
                      else if ((c=='\n') && (i!=1)){
					 i=0;
					 num_enter++;
				}	   
			 else num_enter=0;
               return c;
	       		
            
          }
        	
       }
