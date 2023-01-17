## Copy control

* Copy constructor
    * StrVec::StrVec(const StrVec& obj);

* Lvalue es una referencia de un objeto (variable name, dereference pointer, funcion call that returns a reference).
* Rvalue es un valor. (Literales que no tienen ningun almacenamiento asociado).
* **Rvalue reference** es una referencia que debe de linkearse a un rvalue. Esto es obtenido usando un && en vez de &
    * Asi pueden ser linkeados a un "objeto" que esta a punto de ser destruido

* Move constructor
    * StrVec::StrVec(StrVec&& s);
