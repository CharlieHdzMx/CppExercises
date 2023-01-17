# RTTI

* RTTI(Run time type information) es un mecanismo que expone informacion de un tipo de dato de objeto en runtime y es disponible solo para las clases que almenos tienen una funcion virtual. Permite el tipo de un objeto ser determinado durante ejecucion de programa.

Tienes 3 tipos de RTTI:
* Dynamic_cast operator
    * Usado para conversion de tipos polimorficos.
* Typeid
    * Usado para identificar el tipo exacto de un objeto.
    * Reference, pointer and subscripted pointer pueden ser runtime checked cuando un tipo de clase polimorfica es aplicada.
* Type_info
    * Usado para mantener informacion retornada por el operator typeid.

## Runtime cast
* Determina el tipo  del objeto usando un puntero o referencia.
    * Esto es especialmente benefico cuando necesitamos castear un puntero desde una clase base a una clase derivada.

* Dynamic_cast es una herarquia de herencia, que es usado para downcasting un puntero de clase base con una clase hijo. En success, retorna un puntero del tipo convertido
    * D* d = dynamic_cast<D*>(b);

``` cpp
// C++ program to demonstrate
// Run Time Type Identification(RTTI)
// but without virtual function

#include <iostream>
using namespace std;

// initialization of base class
class B {
    virtual void func();
};

// initialization of derived class
class D : public B {};

// Driver Code
int main()
{
	B* b = new D; // Base class pointer
	D* d = dynamic_cast<D*>(b); // Derived class pointer
	if (d != NULL)
		cout << "works";
	else
		cout << "cannot cast B* to D*";
	getchar(); // to get the next character
	return 0;
}
```

* En este ejemplo solamente sirve porque la clase base B tiene una funcion virtual.

## Typeid operator

``` cpp
#include <iostream>
#include <typeinfo>

class Base {
public:
   virtual void vvfunc() {}
};

class Derived : public Base {};

using namespace std;
int main() {
   Derived* pd = new Derived;
   Base* pb = pd;
   cout << typeid( pb ).name() << endl;   //prints "class Base *"
   cout << typeid( *pb ).name() << endl;   //prints "class Derived"
   cout << typeid( pd ).name() << endl;   //prints "class Derived *"
   cout << typeid( *pd ).name() << endl;   //prints "class Derived"
   delete pd;
}
```
