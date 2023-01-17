


# Function overloading.
* Ordinariamente el coma, addres-of, logical AND, OR no deben de sobrecargarse.
* Funciones que distinguen entre mover o copiar un parametro, normalmente tienen una version const T& y otra sin const.
* Puedes definir funciones si son de move o copy como sigue.
    * Foo sorted()&&; //Move
    * Foo sorted()const&;  // Copy.

## stream << operator
    * ostream& operator<<(ostream &os, const Sales_data& item);
        * usualmente el primer parametro es un nonconst ostream object.
        * Deben de ser nonmember functions.

## Arithmetic and relational operations.
    * Nonmember functions de dos objetos
    * Sale_data operator==(const Sale_data& lhs, const Sale_data& rhs);
    * Foo& Foo::operator=(const Fo& rhs);

