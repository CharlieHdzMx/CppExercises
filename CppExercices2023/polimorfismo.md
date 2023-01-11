## Object oriented programming
* Base class define virtual a las funciones que espera que sean definidas tambien en las clases derivadas.
* Cuando tienes herencia publica, puedes usar los miembros de la clase base como si fueran de la clase derivada.
* **overrride**, es una manera en la que una clase derivada indica explicitamente que tiene una funcion para sobreescribir una funcion virtual que hereda.
* Dynamic bending es la manera en la que las llamadas de las funciones dependen del objeto en la que se estan llamando.
    * Esto sucede cuando una funcion virtual es llamada mediante una referencia.
* Para prevenir que una clase sea usada como base, ponemos el keyword de final en la declaracion.
* Polimorfismo, cuando tenemos una clase base con funciones virtuales que son redefinidas en las clases derivadas, entonces es posible tener un abstraccion de que tipo derivado es usado (y como se ejecuta su funcion) en tiempo de ejecucion si se usa un puntero de clase base. Ya que un puntero con una clase base puede representar las clases derivadas porque todo puntero de la clases derivadas contiene una parte de la clase base que es el inicio de la direccion que estaria apuntando el puntero.
* Pure virtual function es una funcion que es declarada pero que no es definida ya que su definicion se hara solamente en las clases derivadas.
    * Cuando una clase tiene una funcion pure virtual, esta clase se vuelve abstracta y no puede ser usada directamente como un objeto. Pero si se puede usar como referencia para dynamic binding.
    * Todas las clases derivadas de una clase abstracta deben de sobreescribir las funciones virtuales puras de la clase base. Si no habra un error de compilacion.
* Toda funcion virtual entre base class y derived class deben de tener la misma declaracion para que el dynamic relation.
* Friendship is not inherentance, significa que si hay un friend en la clase base, este friend no es de las clases derivadas.
* = delete es usado para evitar que el compilador crea copy constructors o constructors implicitamente.
* move assign syntaxis es:
    * Quote& operator = (Quote&&) = default;
* copy assign syntaxsis es:
    * Quote& operator = (const Quote&) = default;
* En contenedores de elementos que pueden tener diferentes tipos basados en una clase base, en vez de pasar objetos, pasas referencias o pasas smart pointers para que el puntero permita usar todos los diferentes tipos derivados de objetos mediante el polimorfirsmo de la clase base.
* Deque es un doble ended container que sizes dinamicos puiedne expandirse or contractar en ambos finales (ya sea en el front or the back).

# Polymorfismo.
* Polymorfismo significa diferentes modos, y ocurre cuando tienes varias clases relacionadas por herencia.
    * Polimorfismo en tiempos de compilacion es basado en una funcion con el mismo nombre actuando diferente basado en sus parametros de entrada.
    * Polymorfismo en tiempos de ejecucion (runtime) es cuando el programa necesita esperar a el codigo corriendo para saber como representar un objeto o funcion.
        * Una funcion virtual es una funcion miembro que es declarada en la clase base como virtual y es redefinida en las clases derivadas.
            * Esta funcion virtual permite el llamar la funcion especifica en tiempos de ejecucion cuando tienes un puntero de una clase base pero que puede ser una clase derivada con una funcion especifica que viene de la funcion virtual.
            * virtual = intended to be overrrided.
            * Una funcion nonvirtual no se espera que sea sobreescrita por clases derivadas y por ello para referenciar entre ellos necesitas el scope de la clase (Base::, por ejemplo), o depender del scope del objeto para la llamada de la funcion.
```
// C++ Program to demonstrate
// the Virtual Function
#include <iostream>
using namespace std;

// Declaring a Base class
class GFG_Base {
public:
    // Funcion virtual que PUEDE ser sobreescrito y referenciado por un puntero de clase base.
    virtual void display()
    {
        cout << "Called virtual Base Class function" <<
                "\n\n";
    }
    // Funcion non virtual que puede ser sobreescrito pero dependera de su objeto que lo llama.
    void print()
    {
        cout << "Called GFG_Base print function" <<
                "\n\n";
    }
};

// Declaring a Child Class
class GFG_Child : public GFG_Base {
public:
    void display()
    {
        cout << "Called GFG_Child Display Function" <<
                "\n\n";
    }

    void print()
    {
        cout << "Called GFG_Child print Function" <<
                "\n\n";
    }
};

// Driver code
int main()
{
    // Create a reference of class GFG_Base
    GFG_Base* base;

    GFG_Child child;
    /* Hacemos que el puntero de la clase base referencie al objeto derivado.*/
    base = &child;

    // El puntero base llama a la funcion virtual, pero como se forza la llamada de display de clase base
    // entonces display sera Called virtual Base Class function.
    base->GFG_Base::display();

    // Como print es funcion no virtual, entonces dependera totalmente del objeto que lo llama. En este caso, base class-
    base->print();
}

```

* Si en otro caso se deja al software determinar que llamada de display se va a llamar dinamicamente, se hace al no pedir un scope specifico de la funcion virtual:
```
// C++ Program to demonstrate
// the Virtual Function
#include <iostream>
using namespace std;

// Declaring a Base class
class GFG_Base {
public:
    // Funcion virtual que PUEDE ser sobreescrito y referenciado por un puntero de clase base.
    virtual void display()
    {
        cout << "Called virtual Base Class function" <<
                "\n\n";
    }
    // Funcion non virtual que puede ser sobreescrito pero dependera de su objeto que lo llama.
    void print()
    {
        cout << "Called GFG_Base print function" <<
                "\n\n";
    }
};

// Declaring a Child Class
class GFG_Child : public GFG_Base {
public:
    void display()
    {
        cout << "Called GFG_Child Display Function" <<
                "\n\n";
    }

    void print()
    {
        cout << "Called GFG_Child print Function" <<
                "\n\n";
    }
};

// Driver code
int main()
{
    // Create a reference of class GFG_Base
    GFG_Base* base;

    GFG_Child child;
    /* Hacemos que el puntero de la clase base referencie al objeto derivado.*/
    base = &child;

    // El puntero base llama a la funcion virtual, no se fuerza un scope, asi que llamara al display() de
    // la clase base.
    base->display();

    // Como print es funcion no virtual, entonces dependera totalmente del objeto que lo llama. En este caso, base class-
    base->print();
}

```
* La clase virtuales deben de tener el mismo steryotype para funcionar como funcion polymorfica.
    * Si una clase derivada define una funcion con el mismo nombre que una funcion virtual de una clase base, entonces el compilador, tomara, esta funcion como uno diferente y no funcionara con virtual.
    * Puedes definir en las clases derivadas el keywork **override** que le dira al compilador que es la intencion tener una funcion virtual, asi que si hay una funcion con el mismo nombre que una clase base virtual y es diferente en parametros, el compilador marcara un error si la funcion derivada tiene el override.
    * En el caso contrario, si en una clase ponemos el keywork **final**, el compilador marcara un error si se trata de sobreescribir esa funcion.
* No es necesario poner virtual en todas las clases derivadas cuando una clase base tiene virtual porque eso se hace implicitamente. Se puede hacer pero no es necesario.
* Si tienes diferentes niveles de herencia en clases, aun asi la funcion dependera del objeto que se referencia para la llamada virtual.

```
// C++ Program to illustrate Run-Time
// Polymorphism in Hierarchical inheritance

#include <iostream>
using namespace std;

class Base1 {
public:
    // Virtual function of Parent Class
    virtual void funct1()
    {
        cout << "Base1::funct1() is called\n";
    }
    virtual void funct2(int x)
    {
        cout << "Base1's Val of x:" << x << endl;
    }

    // Non-Virtual Function
    void funct3()
    {
        cout << "Base1 is the Parent class!"
            << endl;
    }
};

class Base2 : public Base1 {
private:
    void funct1()
    {
        cout << "Base2::funct1() is called\n";
    }
    void funct2(int x)
    {
        cout << "Base2's Val of x:"
            << x << endl;
    }
    void funct3()
    {
        cout << "Base2 is the first"
            << " Derived class!" << endl;
    }
};

class Base3 : public Base1 {
private:
    void funct1()
    {
        cout << "Base3::funct1() is called\n";
    }
    void funct2(int x)
    {
        cout << "Base3's Val of x:"
            << x << endl;
    }
    void funct3()
    {
        cout << "Class Base3 is second"
            << " Derived class!" << endl;
    }
};

// Grand-Child_1 of Base1 class
class Derived1 : public Base3 {
private:
    void funct1()
    {
        cout << "Derived1::funct1() is called\n";
    }
    void funct2(int x)
    {
        cout << "Derived1 Class's Val of x:"
            << x << endl;
    }
    void funct3()
    {
        cout << "Class Derived1 is Good!!"
            << endl;
    }
};

// Grand-Child_2 of Base1 class
class Derived2 : public Base3 {
private:
    void funct1()
    {
        cout << "Derived2::funct1()"
            << " is called\n";
    }
    void funct2(int x)
    {
        cout << "Derived2 Class's Val "
            << "of x:" << x << endl;
    }
    void funct3()
    {
        cout << "Class Derived2 is Good!!"
            << endl;
    }
};

// Run-Time Polymorphism
// in Hierarchical Inheritance
int main()
{

    // Base1 class's(Parent class's)
    // pointer points to Derived1 class
    Base1* b1ptr = new Derived1();

    // Run-Time Polymorphism
    b1ptr->funct1();
    Derived2 d2;

    // Now the Base1 class pointer
    // points to d2 object(Derived2 class)
    b1ptr = &d2;

    // Run-Time Polymorphism
    b1ptr->funct2(30);

    // Compile-Time Binding
    b1ptr->funct3();

    return 0;
}

```


## Funciones virtuales y parametros por default.
* Se espera que los parametros por default sean los que estan definidos en la clase base cuando se hace un dynamic binding con funciones virtuales de una clase derivada.

## Funciones virtuales puras.
* Cuando tenemos una funcion virtual pura, la clase completa se vuelve abstracta, indicando que no DEBE ser instanciada (porque es abstracta) pero si puede ser usada como puntero para hacer el dynamic binding con clases derivadas. Una funcion virtual pura si se puede definir afuera de la clase pero esto no es la intencion del concepto.
* Una clase virtual pura se define como *virtual f() = 0*,
    * Al hacer una funcion virtual pura estamos FORZANDO a las clases derivadas a definir una funcion con el mismo signature que la funcion virtual pura porque es necesario rellenar la definicion que la clase base abstracta definio para todos los hijos.
