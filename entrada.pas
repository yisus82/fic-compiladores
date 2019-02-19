var
i,j,k : integer;
b : boolean;

begin

{ Esto es un comentario }

j := 20;
k := j - 13;
for i := 2 to j do
begin
repeat
k := k + i;
until ( k > j ); 
end;

{ Esto es
otro comentario,
pero de varias lineas }

b := ( true or ( k > 2 ) )

while ( k > 1 and b ) do
k := k - 1;

if ( b ) then
k := 3
else
k := 4;

end.
