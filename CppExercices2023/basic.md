
# const and volatile
Pueden ser usado en unions, structs, classes, enum y typedefs.

## const
* Significa que un valor no es modificable
* int* a = puntero no constante a variable no constante.
* int* const a = puntero constante a variable no constante.
* const int* a = puntero no constante a variable constante.
* const int* const a = puntero constante a variable constante.

## volatile
* La variable debe de ser accedida directamente de memoria sin ninguna optimizacion ya que puede ser llamado entre varias entidades.

## mutable
* mutable
    * permite la modificacion de un miembro
