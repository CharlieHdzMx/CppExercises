# Herencia
https://www.geeksforgeeks.org/inheritance-in-c/

* Una clase derivada no hereda acceso a private data members del class base.
* Cuando una clase derivada hereda privadamente, todos los miembros de la clase base que eran publicas se vuelven privados y solamente pueden ser accedidos por las funciones miembro de la clase derivada.
* Modo protected, todos los miembros publicos y protected seran protected.

## Herencia multiple
* Es un feature de C++ donde las clases pueden heredar de mas de 2 clases.


``` cpp
class subclass_name : access_mode base_class1, access_mode base_class2, ....
{
  // body of subclass
};



class B
{
... .. ...
};
class C
{
... .. ...
};
class A: public B, public C
{
... ... ...
};
```

## Virtual inheritance
* Clases bases virtuales son usados en herencia virtual en una manera de evitar multiples instancias de una clase especifica aparecer en la herarquia de herencia (clases derivadas) cuando se tiene multiples herencias.

``` cpp
#include <iostream>
using namespace std;

class A {
public:
	void show()
	{
		cout << "Hello form A \n";
	}
};

class B : public A {
};

class C : public A {
};

class D : public B, public C {
};

int main()
{
	D object;
	/* Si show() esta definido en C y B desde A, que show se va a usar en D?*/
	object.show();
}
```

* Para resolver esa ambiguedad A es declarada como virtual cuando se hereda de B y C. Este virtual hace que solamente una copia de A sea distribuido para ambos B y C.

``` cpp
#include <iostream>
using namespace std;

class A {
public:
	int a;
	A() // constructor
	{
		a = 10;
	}
};

class B : public virtual A {
};

class C : public virtual A {
};

class D : public B, public C {
};

int main()
{
	D object;
	/* Porque A es virtual, se llama el static value de A independietemente de el multi herencia de B y C.*/
	cout << "a = " << object.a << endl;

	return 0;
}
```

* Herencia virtual impone costos adicionales en tamaño, velocidad y complejidad de inicializacion. Es mas practico cuando las clases base virtuales no tienen datos.

* La construccion de herencia dependen de como es el orden en las clases derivadas.

``` cpp
#include<iostream>
using namespace std;

class A
{
public:
A() { cout << "A's constructor called" << endl; }
};

class B
{
public:
B() { cout << "B's constructor called" << endl; }
};

/* Primero se llamara el contrusctor de B y luego de A y al final de la clase derivada C.*/
class C: public B, public A // Note the order
{
public:
C() { cout << "C's constructor called" << endl; }
};

int main()
{
	C c;
	return 0;
}
```

* Destructores se llaman en el orden reverso de la construccion, en este caso seria destructor C, destructor A y destructor B.

``` cpp
#include<iostream>
using namespace std;

class base {
	int arr[10];
};

class b1: public base { };

class b2: public base { };

class derived: public b1, public b2 {};

int main(void)
{
/* Aqui, el tamaño de derived es 80 bytes (si entero son 4 bytes). porque ek arr[] de base se duplica, uno para b1 y otro para b2.*/
cout << sizeof(derived);
return 0;
}
```

``` cpp
#include<iostream>

using namespace std;
class P {
public:
void print() { cout <<" Inside P"; }
};

class Q : public P {
public:
void print() { cout <<" Inside Q"; }
};

class R: public Q { };

int main(void)
{
R r;
/* Aun cuando R no tiene un print(), como deriva de class Q, entonces el compilador buscara de R a las clases bases un match con el nombre de print, al llegar a Q encuentra print(9 asi que pondra Inside Q.*/
r.print();
return 0;
}
```

``` cpp
#include<iostream>
using namespace std;

class Base {};

class Derived: public Base {};

int main()
{
    /* Correcto, un puntero base contiene la primera parte de base y la extension de derived no requiere ser definido. Esto es parte de polimorfismo, como es un puntero, */
	Base *bp = new Derived;
	/* No correcto, Un puntero derived necesita tambien su parte de derived y no solamente la base. En esta parte solamente estamos asignando la base,
	pero el compilador detecta que faltara la parte derived de este objeto.*/
	Derived *dp = new Base;
}
```
* Tener cuidado con el sliding inheritance, que significa que un puntero de una clase base que referencia a un objeto derived no podra ver funciones non-virtual o miembros publicos que solamente estan definidos en el derived. Para evitar esto, y si es la intencion, poner funciones virtuales, de esa manera el puntero de la clase base que referencia un objeto derived podra ver las funciones virtuales de la clase derived.

``` cpp
#include<iostream>
using namespace std;

class Base
{
public:
    /* Nota que esta funcion no tiene virutal, el derived puede sobreescribirlo*/
	void show()
	{
		cout<<" In Base ";
	}
};

class Derived: public Base
{
public:
	int x;
	/* Sobreescrito del mismo de Base, como no es virtual, un puntero de clase base no podra acceder a este aun con dynamic binding*/
	void show()
	{
		cout<<"In Derived ";
	}
	Derived()
	{
		x = 10;
	}
};

int main(void)
{
	Base *bp, b;
	Derived d;
	bp = &d;
	/* Llamara el show() de la clase base*/
	bp->show();
	/* No puede acceder a x que es un miembro publico porque el puntero de la clase base no lo puede ver.*/
	cout << bp->x;
	return 0;
}
```

``` cpp
#include<iostream>
using namespace std;

class Base
{
public:
	int fun() { cout << "Base::fun() called"; }
	int fun(int i) { cout << "Base::fun(int i) called"; }
};

class Derived: public Base
{
public:
	int fun() { cout << "Derived::fun() called"; }
};

int main()
{
	Derived d;
	/* Es un error de compilacion porque cuando una clase Derived define una funcion con el mismo nombre de una funcion no-virtual de la clase Base, entonces todo el scope de funciones de la clase base no se pueden ver y el compilador disparara un error.*/
	d.fun(5);
	return 0;
}
```
* Para arreglar esto, podemos poner el scope de la funcion de la clase Base para que el compilador pueda anexar directamente la funcion que se pidio de la clase base.

``` cpp
#include<iostream>
using namespace std;

class Base {
public:
	void fun()		 { cout << "Base::fun() called";	 }
	void fun(int i)	 { cout << "Base::fun(int i) called"; }
};

class Derived: public Base {
public:
	void fun() {	 cout << "Derived::fun() called"; }
};

int main() {
	Derived d;
	/* Debido al scope Base:: entonces el compilador puede ver que se referencia a una funcion que la clase Derived tiene acceso, asi que lo llama.*/
	d.Base::fun(5);
	return 0;
}
```

* Cuando pasas un objeto de clase Base sin referencia o sin puntero, entonces se pasa unicamente la parte de la base independientemente de que el objeto del parametro sea Derived, asi la copia del parametro solo contendra la parte base.

``` cpp
#include <iostream>
#include<string>
using namespace std;

class Base
{
public:
	virtual string print() const
	{
		return "This is Base class";
	}
};

class Derived : public Base
{
public:
	virtual string print() const
	{
		return "This is Derived class";
	}
};

/* Debido a que el parametro no es una referencia u objeto, entonces solamente se pasa la parte base aun cuando p sea Derived.*/
void describe(Base p)
{
	cout << p.print() << endl;
}

int main()
{
	Base b;
	Derived d;
	describe(b);
	/* Imprimira el print() de base porque no es un puntero o referencia.*/
	describe(d);
	return 0;
}
```

* Hay problemas al tratar de inicializar variables de la parte Base dentro de un constructor de la clase Derived aun cuando son publicos, esto es porque se requiere que los miembros de la clase Base sean inicializados con un constructor de Base y no directamente con el inicializer_list de una clase derivada.

``` cpp
#include<iostream>
using namespace std;

class Base
{
public :
	int x, y;
public:
	Base(int i, int j){ x = i; y = j; }
};

class Derived : public Base
{
public:
    /* Aqui deberia de haber un constructor de Base para inicializar sus propios  miembros
       Derived(int i, int j):Base(i,j) {}*/
	Derived(int i, int j):x(i), y(j) {}
	void print() {cout << x <<" "<< y; }
};

int main(void)
{
	Derived q(10, 10);
	q.print();
	return 0;
}
```

* Entonces recuerda, si una funcion es virtual, y tenemos un class Base = &d, vamos a poder llamar la funcion virtual derived aun cuando estamos con un puntero base.

``` cpp
#include <iostream>
using namespace std;

class Base
{
public:
	virtual void print()
	{
		cout << "Base class print function \n";
	}
	void invoke()
	{
		cout << "Base class invoke function \n";
		this -> print();
	}
};

class Derived: public Base
{
public:
	void print()
	{
		cout << "Derived class print function \n" ;
	}
	void invoke()
	{
		cout << "Derived class invoke function \n";
		this -> print(); // called under non - virtual function
	}
};

int main()
{
	Base *b = new Derived;
	/* Base llamara el Base::invoke() porque no es virtual, pero llamara el Derived::print() porque es virtual.*/
	b -> invoke();
	return 0;
}

```

* Si una clase derivada no redefine una funcion virtual pura, el compilador no mandara ningun error, pero la clase derivada se volvera abstracta tambien.



