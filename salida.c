#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char *argv[]) {

int i,j,k;
int b;

/* Esto es un comentario */

j = 20 ;
k = j - 13 ;
for(i=2;i<=j;i++)
{
do {
k = k + i ;
} while (!( k > j ) );
}

/* Esto es
otro comentario,
pero de varias lineas */

b = ( 1 || ( k > 2 ) ) ;

while ( k > 1 && b ) 
k = k - 1 ;

if ( b ) k = 3 ;
else
k = 4 ;

exit(0);

}

