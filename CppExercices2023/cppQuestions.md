# Preguntas
* Si casi todas las llamadas de function foo() pasa uno de 10 valores particulares, que metodo cambiaria de forma significativa el tiempo de ejecucion de la funcion llamada.

``` cpp
    inline int foo (int x) {
2   int r;
3
4   * // time-consuming operation on x, result stored in r
5
6   return r;
7 }
```
    * Reemplazar * con un lookup table  con los 10 valores y sus valores correspondientes de r.

* Como es la manera correcta de acceder una variable static de una clase.
    * C::m

* Cuando un destructor e C++ debe de ser declarado en la clase virtual?
    * Cuando tienes una clase Base con al menos una funcion virtual, esto es para soportar que un puntero de clase Base con funciones virtuales tambien destruya el destructor de la clase Derived cuando se elimina el recurso mediante el puntero de la clase Base.

* Modifica el codigo para corregir el acceso del Driver para errores de compilacion.

``` cpp
clude <iostream>
using namespace std;

class Bus {
    /* friend void useBus();*/
protected:
    class Driver;

public:
    static Driver* createDriver() {
        return new Driver;
    }
private:
    int seats;
protected:
    class Driver {
    public:
        string  name;
    };
};

class DeriveDriver : public Bus {};

void useBus()
{
    Bus::Driver*    driver = Bus::createDriver();
    driver->name = "DRIVER";
}

int main(int argc, char* argv[])
{
    return 0;
}
```
    * Derivar una clase de Bus. Hacer objeto driver un DeriveDriver class pointer.
    * Hacer la funcion createDriver() no estatico.
    * Declara la funcion useBus() friend de la clase bus.
        * Correcto, de esta manera el tipo driver sera visible para la funcion useBus()
    * Cambiar el accesso del miembro Driver a publico.
    * Hacer que la funcion CreateDriver() retorne Driver& .

* Cuales son llamadas legales en un function template?

``` cpp
#include <iostream>
using namespace std;

template <typename T, int duration>
double power (double amplitude, int frequency = 1000) { return amplitude * frequency; }

int main(int argc, char* argv[])
{
    double output;

    output = power<int, 100>(3.0, 'a'); /* Ok, porque estos tipos se pueden reintepretar.*/
    output = power<500>(3.0); /* No hay matching de la funcion solamente un <> y un solo ()*/
    output = power<int, 500>(3.0, 100); /* Ok porque estos tipos se pueden reintepretar.*/
    output = power<int>(3.0, 100); // No matching function for call to 'power', solamente un <i t>
    output = power<int, char>(3.0); // No matching function for call to 'power' solamente un ()
    output = power<int, 500>(3.0);/* Ok porque estos tipos se pueden reintepretar.*/

    cout << output << endl;

    return 0;
}
```

* Cuales NO son elementos de procesamiento de excepciones en C++?
    * Hacer una especificacion de exception usando throw().
    * Usar dynamic_cast<> en referencias.
        * CORRECTO Dynamic cast no tiene nada que ver con error handling.
    * Uso de assert().
        * Assert no es poarte del procesamiento de excepciones?
    * Realizar una exception usando noexcept.
    * Throwing an object de clase Exception.
* Cual de los siguientes es una declaracion correcta para un copy constructor de clase?

``` cpp

#include <iostream>
using namespace std;

class Gizmo{
    Gizmo();
    ~Gizmo();

    Gizmo(const Gizmo* copy_me) const; // const no es permitido en copy constructor porque el constructor requiere modificar el objeto.

    Gizmo(const Gizmo&) const; // const no es permitido en copy constructor porque el constructor requiere modificar el objeto.

    Gizmo(Gizmo& const copy_me); // const of high level are not intended to reference.

    Gizmo(const Gizmo& v);

    Gizmo(const Gizmo&);
};

int main(int argc, char* argv[])
{
    return 0;
}
```

* Que es verdad de los access specifications de herencia de C++?
    * Herencia protegida de una clase base hace todos los miembros de la clase base protected en la clase derivada.
        * Herencia protegida vuelve protected solamente los miembros publicos y protected, private members se quedan igual.
    * Herencia dinamica de una clase base permite al acceso de miembros de la clase derivada a ser cambiadas en el vuelo.
        * No hay herencia dinamica en C++.
    * Herencia publica de una clase base hace todos los miembros public de la clase Derived.
        * Herencia publica mantiene todos los miembros como estan.
    * Herencia privada de una clase base hace todos los miembros private de la clase Derived.
        * Herencia privada pone todos los miembros publicos y protected como privados.
    * Miembros private en la clase base no son cambiados  mediante un spec de acceso de herencia.
        * Este es el correcto, porque los miembros private nunca cambian basados en el acceso de la herencia.

* Cual de estos describe correctamente C++?
    * Una referencia puede referenciar para diferentes objetos por assignment.
        * No, una referencia es un alias de un solo objeto.
    * Una referencia crea un alias para otro objeto.
        * Correcto.
    * Una referencia permanece valido irrespectivamente del scope o lifetime del objeto de referencia.
        * No, porque depende del scope del objeto y de si mismo.s
    * El operador -> debe de ser usado para acceder el objeto referenciado.
        * No exactamente. el operator . tambien puede ser usado.
    * Una referencia debe de ser inicializada cuando es declarado.
        * Correcto, no puede haber una referencia no apuntando a algo.

* Que parte del codigo contiene un error?

``` cpp
#include <iostream>
using namespace std;

int getLength() {
    return 10;
}

int size = getLength();
/* size no se puede definir en tiempos de compilacion, asi que este es un error ya que el software necesita saber que tanto ocupa de espacio para poder alojar la memoria de message para una varible no dinamica.*/
char message[size];
int main(int argc, char* argv[])
{
    bool ok = true;

    if (!ok) {
        cout << "not ok" << endl;
    }

    const int size = 10;
    char message[size];

    int numerator, denominator;

    numerator = 10.0;
    denominator = 3.0;

    float quotient = numerator / denominator;

    for (char idx = 0; idx < 250; idx ++) { // El tipo del caracter tiene un range de -128 a 127, asi que este for sera infinito porque nunca llegara a 250.
        cout << "hello world" << endl;
    }

    return 0;
}
```

* Cuales son correctos acerca de los operadores de C++11 alignof() y alignas()?
    * alignof() es usado para obtener el alignment de una variable o tipo especifico.
        * correcto.
    * alignas() es usado para especificar alignment customizado de una variable o tipo especifico.
        * Correcto, si customizado significa que puedes poner un valor cualquier en el tipo.
    * alignas() retorna el size, en bytes de la expresion entre parentesis
        * No, alignas() forza una expresion a tener el mismo alignment. Por ejemplo, en este caso b esta forzado a alinearse con un double.
            * alignas(double) char b;
    * alignof() retorna el size en bytes de la expression entre parentesis
        * Correcto.
    * alignas() funciona en expresiones.
        * No, no funciona en expresiones.

* Cuales son fo loop syntax legales?

``` cpp
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    for (double d = 1.0; d <= 1.9; d += 0.1)
        cout << "testA" << endl;

    for (int i = 15; i; i --)
        cout << "testB" << endl;

//    for (true) // Expected ';' in 'for' statement specifier
        cout << "testC" << endl;

    for (; ;)
        cout << "testD" << endl;

//    for (int i = 0, i < 10, i ++) // , comma without ; is not complete for()
        cout << "testE" << endl;

    return 0;
}
```

* Cuando usando el multithread library de C++, cuales objeto no son callables para correr en un thread?
    * Una clase con un operator() sobreescrito.
    * A class member function
    * A lambda function
    * An executable file.
        * Este no son callables porque el thread requiere meter un objeto en su constructor y un file ejecutable no es un objeto callable.
    * A regular function.

* Que es la verdad acerca del segmento de codigo de C++ de abajo?

    * El operator < overloading no es necesario. Usa la implementacion por defecto.
        * Este no es cierto, clase de tipo X ocupa un metodo de comparativa.
    * El operator < tiene el tipo incorrecto de retorno.
        * Correcto, un operator de comparacion debe de retornar bool. ya que el lhs es el objeto que se esta usando ahorita.
    * El operator < puede no ser sobreescrito.
        * Este es incorrecto, este operador si es necesario siempre sera sobreescrito porque depende del tipo.
    * El operator < esta implementado correcto.
        * No, retornar una referencia es incorrecto.
    * El operator < no va a ser accedido al codigo usando un objeto de tipo X.
        * No, Es accedido
``` cpp

#include <iostream>
using namespace std;

class x {
/* The return value shall be boolean*/
    x& operator< (const x& rhs) const {
        int thisVol = height * width * length;
        int thatVol = rhs.height * rhs.width * rhs.length;

        return thisVol < thatVol;
    }
/*
    bool operator< (const x& rhs) const {
        int thisVol = height * width * length;
        int thatVol = rhs.height * rhs.width * rhs.length;

        return thisVol < thatVol;
    }
*/
private:
    int height;
    int length;
    int width;
};

int main(int argc, char* argv[])
{
    return 0;
}
```

* En cual de los siguientes situaciones el compilador de C++ estara generando un constructor por defecto de la clase?
    * Cuando un compilador switch es usado para indicar al compilador de usar un constructor por defecto.
    * Cuando la clase no tiene un constructor por defecto definido.
        * Correcto
    * Cuando la clase ha declarado un constructor virtual.
    * Cuando la clase no tiene un constructor definido o deleted.
        * Correcto
    * Cuando el compilador de C++ necesita un constructor a un objeto temporal de la clase.

* Cuales son declaraciones de C++ de punteros variables que no pueden ser cambiados ( no pueden apuntar a otro lado) const pointer to non const variable

int* const p;
    * extern float* const ptr;
        * ok
    * extern const std::vector<int>* ptr;
        * nok
    * extern const void* ptr;
        * ok
    * extern const int* const ptr;
        * nok ambos son constantes.
    * extern double* ptr const;
        * nok, no puedes definir un puntero con esta syntax.

* Que representa una declaracion valida para el codigo de abajo para sobreescribir el operador [] que retorna un int& en C++?
    * int& operator()(int);
    * int& operator[int](int);
    * int& operator[int]();
    * int& operator(int)();
    * int& operator[](int);
        * Correcto.

* Cuales de los siguientes indican una optimizacion de codigo en C++.
    * En la fase de generacion de un ejecutable de un programa ejecutable, donde una funcion de libreria son resueltos.
    * En el proceso de modificar codigo fuente para mejorar algunos aspectos de su ejecucion, usualmente en costos de otros aspectos.
        * Ok, lo demas explica cosas que no optimizan codigo pero mas bien procesos comunes.
    * Es el proceso de tailoring el codigo de maquina generado durante la compilacion asi que el codigo resultante corre mas rapido y eficiente.
    * Referencia a la coleccion y precompilacion de archivos de header para un procedimiento mas eficiente que tiempos de compilacion.
    * En el proceso de capturar los aspectos requeridos de un paquete de software antes de que el codigo fuente sea escrito.

* Cuales son los resultados de correr el fragmento de codigo de abajo?
    * 65, porque el derived no tiene ningun scope de la clase base y los miembros de todas maneras no se comparten.

``` cpp
#include <iostream>
using namespace std;

class base {
public:
    base() : code('B') { }
    char code;
};

class derived : public base
{
public:
    int code;
};

int main(void)
{
    derived d;
    d.code = 65;
    std::cout << d.code;
};
```

* Cual es el substituto de **** para que el programa de abajo imprima "0 1 2 3 4 5 6 7 8 9 10 11"?

``` cpp
#include <iostream>
#include <vector>
#include <numeric>      // std::iota
#include <utility>      // std::move
#include <algorithm>    // std::copy_if, std::for_each
using namespace std;

int main()
{
    std::vector<int> sequence{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    // 0 1 2 3 4 5 6 7 8 9 10 11, el ++sequence.begin() omite el primer indice de 0.
    iota( ++sequence.begin(), sequence.end(), 1 );

    // Print out the modified sequence -- what will it be?
    for( int elem : sequence )
    {
        std::cout << elem << " ";
    }

    std::cout << std::endl;

    return 0;
}
```

* Cuales son los tipos de polimorfismo en C++?
    * Parametric polymorfismo.

* Cual substituto de ***** seria ilegal?

``` cpp
#include <iostream>
using namespace std;

class A {
public:
    int age;
    int weight;
protected:
    int iq;
};

class B : protected A {
public:
    using A::iq;
    using A::age;
};

class C : private B {
public:
    using B::iq;
    using B::weight;
};

int main()
{
    B   bObj;
    C   cObj;

    /*****/

    bObj.iq = 190; /* Ok, tenemos un iq que estamos usando desde A.*/
    cObj.iq = 190; /* Ok, tenemos un iq que se vuelve privado pero sigue siendo accesible para C.*/
    bObj.weight = 110; /* NOK, weight es un miembro protected de A. Como no estamos introduciendo el nombre de weight en B esta bien, por es en la clase la declaracion esta bien porque solamente estamos  reusando el nombre, pero como es protected no podemos usarlo aqui como si
    fuera publica.*/
    bObj.age = 20; /* Ok.*/
    cObj.weight = 110; /* Introduccion de nombre, aun cuando es un private inheritance*/

    return 0;
}
```

* Cuales son validos cuando se usa una libreria multi-threating que es parte de C++ STL?
    * Multiples threads en un solo programa no tienen manera de comunicarse entre ellos.
        * Nok
    * Multi-threads requieren librerias de propiedades.
        * Nok
    * Multiple thread de un solo programa pueden compartir los mismos recursos
        * Ok.
    * Multithreads no es posible en una computadora que un solo CPU  conteniendo un solo core.
        * NOk. Threads no son dependiendes de un solo core. Depende del sistema de ejecutar tareas paralelamente. Multithread != Multicore
    * Multithreads es una habilidad de crear un proceso que consiste en multiples threads de ejecucion. (la sequencia mas pequeña de una instrucción que puede ser manejado independientemente por un scheduler).
        * Ok.
* Que cambios son necesarios en el siguiente codigo para compilar?

``` cpp
#include <iostream>
using namespace std;

namespace controllers {
    namespace rotary {
        void spin(bool start) {
            if (!start) { } /* Aqui falta un statement.*/
        }
    }

    namespace horizontal {
        void move(bool start) {
            if (start) {
                spin(false);

                controllers::spin(false);

                rotary::spin(false);

                horizontal::spin(false);
            }
        }
    }
}

int main(int argc, char **argv)
{
    move(true); /* No se especifica namespace.*/

    controllers::horizontal::move(true); /*Ok*/

    horizontal::move(true); /* Debe de tener scope de controllers.*/
}
```

* Cuales son las maneras validas de crear un type alias?

``` cpp
#include <iostream>
#include <vector>
using namespace std;

template<class T> using vec = std::vector<T>;
vec<float> incomes;


typedef std::vector<T>  vec; // T no esta definido, no es un template clause.
vec<double> weights;


typedef int intAlias; // ok
intAlias count;


typedef T genricAlias<T>; // T no esta definido.
genricA1ias<int> population;


template<typename T> using myGenric = T;
myGenric<int> age;

int main(int argc, char **argv)
{
}
```

* Cuales son statements correctos  acerca de exception handling de C++?
    * El mas general de los catch blocks aparrece al final, con catches mas especificos predeciendole.
        * Correcto
    * Un manejo de exceptiones con un parametro de exception, como catch(), va a capturar cualquier exception independientemente si hay un bloque de catch que coincida.
        * Nok, no what catch() asi, debe de ser catch(...).
    * Multiples clases pueden ser capturados en un solo clause de catch() como multiples argumentos.
        * Falso, un catch por cada clase, solamente un argumento.
    * Excepciones que no coincidan con otros catch() son capturados por catch(...).
        * Correcto, tambien por eso es importante dejarlo al final porque la ejecucion de catch() son basados en su orden.
    * Una excepcion esta enrutado al match mas apropiado independietemente del orden de catch
        * Falso, no hay enrutamiento, solamente si el throw coincide con un catch con una clase especifica de la falla, es donde entra.

* Dado un **arreglo de punteros en C++** cual es la declaracion correcta para un procesor de funcion?
    * double processor(int i, double(*f), int idx);
        * Falso, un puntero a una funcion con mal sintaxis
    * double processor(int i, double(*f(int)), int idx);
        * Falso,
    * double processor(int i, double(*f)(int), int idx);
        * Falso, este es un puntero a una funcion que toma un int y retorna double
    * double processor(int i, double(*f[]), int idx);
        * Correcto, array the punteros.
    * double processor(int i, double(f[])(), int idx);
        * Falso, arreglo de funciones (sin punteros).

* Cual de los siguientes statements son true con respecto al codigo?
    * a6 is a const reference to a3.
        * FALSE
    * d5 is an int initialized to 5.
        * TRUE
    * a1 is an instance of class auto, instantiated by an integer value of "5" being passed to a constructor.
        * FALSE
    * a2 is an int equal to 10.
        * TRUE
    * d4 is an int initialized to 10.
        * FALSE.

``` cpp
#include <iostream>
#include <typeinfo> // std::typeid
using namespace std;

int somFunc() { return 10; }

int main(int argc, char **argv)
{
    auto a1 = 5;
    auto a2 = somFunc();

    decltype(a2)    d4;
    decltype(somFunc()) d5 = 5;

    double a3 = 4.0;
    auto &a6 = a3;

    cout << typeid(a1).name() << endl;
    cout << typeid(a2).name() << endl;
    cout << typeid(d4).name() << endl;
    cout << typeid(d5).name() << endl;
    cout << typeid(a3).name() << endl;
    cout << typeid(a6).name() << endl;
}
```

* Cuales de las funciones miembros de C++ STL clases de contenedor que retorna un iterador al primer elemento en el contenedor?
    * begin()
* Que puede usarse en ***** para crear un arreglo rectangular de 10x5 de doubles en el heap?
    * dArray[r] = new double*;
    * dArray[r] = new double[columns];
        * OK
    * dArray[r] = new double;
    * *dArray[r] = new double[columns];
    * dArray[r] = new double*[columns];

``` cpp
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int rows = 10;
    int columns = 5;

    double **dArray = new double*[rows];

    for (int r = 0; r < rows; r ++) {
        /*****/

        // Assigning to 'double *' from incompatible type 'double **'; dereference with *
        dArray[r] = new double*; /* NOK Incompatible double* a double** */
        dArray[r] = new double[columns]; /* OK arreglo de columns en indice 1*/
        dArray[r] = new double; /* NOK variable en arreglo.*/
        // Assigning to 'double' from incompatible type 'double *'; dereference with *
        *dArray[r] = new double[columns]; /*NOK Incompatible double* a dereferencia.*/
        // Assigning to 'double *' from incompatible type 'double **'; dereference with *
        dArray[r] = new double*[columns]; /* NOK double** a double**/
    }
}
```

* Cuales de los siguientes correctamente describe  el proposito de C++ STL numeric_limit?
    * Es un tipo que especifica los limites de varios recursos que un programa va a incluir en la memoria , storage space y CPU time.
        * Falso, solamente son limites de los numeros.
    * Es un tipo que es usado para designar acciones que pueden ser tomados cuando las variables exceden sus limites.
        * Falso, estos no realiza ninguna accion, solamente indica cuales son los limites de range de los tipos.
    * Es un template que es especializado para tipos basicos designando los limites de arriba y de abajo para esa plataforma en especifico.
        * True
    * Es usado para poner limites en variables numericos, pasando en la que una excepcion sucedera.
        * Falso, esto no dispara automoaticamente una excepcion.
    * Es usado para setear los limites superiores e inferiores de una variable puede tener.
        * Falso, La variable ya sabe sus limites, asi que no lo va a usar.

* Cuales de los siguientes son verdaderos acerca de las declaraciones representando la herarquia de C++ de abajo?
    * Level5::func2(int) will override any functionality defined in Level2::func2(int).
        * Falso, no puede haber override porque el func2() no es virtual.
    * Level1::func1() functionality has been removed from Level2 but is still available to subsequent levels.
        * Falso, Level 3 no sobreescribe el constructor deleted, asi que nisiquiera este puede usarlo.
    * Level5::func4(char) will produce a compiler error since it is not a true override.
        * Falso, No marca un error de compilacion porque poner overrride cuando no lo esta haciendo por los parametros no es un error de compilacion.
    * Level5::func3(int) will produce a compiler error since virtual functions implemented elsewhere cannot be deleted.
        * Falso, no es virtual puro
    * Level5 results in a compiler error since it cannot inherit from Levei3.
        * Correcto, Level3 esta marcado como Final, asi que Level 5 no es correcto.

``` cpp
#include <iostream>
using namespace std;

class Level1 {
public:
    void func1();
};

class Level2 : public Level1 {
public:
    void func1() = delete;
    int func2(char);
};

class Level3 final : public Level2 {
public:
    virtual double func3(int);
};

class Level4 : public Level2 {
    virtual double func4(int);
    double func5(char a);
};

class Level5 : public Level3 { // Base 'Level3' is marked 'final'
public:
    double func2(char) override; // Only virtual member functions can be marked 'override'
    virtual double func3(int) = delete;
    virtual double func4(char) override; // 'func4' marked 'override' but does not override any member functions
};

int main(int argc, char **argv)
{
    Level3 obj;

    obj.func1(); // Attempt to use a deleted function

    return 0;
}

```
* Cuales correctamente describe C++11 unordered associative container, por ejemplo unordered_set,unordered_map, unordered_multimap?
    * Ellos realizan su lookup basado en una funcion hash.
        * Correcto.
    * Lookup tiene un o(log(n)) complexity.
        * Falso, lookup es lineal
    * Realizan un lookup basado en su criterio de orden.
        * Falso, no hay criterio de orden en unordered.
    * Son implementados como trees binarios.
        * Falso, binary trees son ordenados.
    * Todos permiten multiples entradas de la misma llave.
        * Falso, los map y set no son con misma entrada.

* Cual de estos correctamente describe atributos de overloading de funcion en C++ programming?
    * Las funciones deben de estar dentro de un namespace.
    * El codigo de la funcion debe de ser diferente.
    * El nombre de las funciones deben de ser diferentes.
    * Los tipos de argumentos y el numero de argumentos de la funcion debe de ser diferente.
        * Ok
    * El tipo de retorno de las funciones deben de ser diferentes.

* Inmmediatamente despues de la evaluacion de una expresion y un assignment de los resultados de una variable entera "a", que debe de ser correcto, acerca de el valor de a?

``` cpp
#include <iostream>
using namespace std;

int b = 1;

int x() { b ++; return b; }
int y() { b *= 3; return b - 1; }
int z() { b = b + 8; return b + 2; }

int main(int argc, char **argv)
{
    /* El valor de A no puede ser determinado y depende de cada compilador, no es standard el orden de llamadas de funciones como aqui.*/
    int a = x() - y() + z(); // 2 - 5 + 16

    // 13
    cout << a << endl;

    // 14
    cout << b << endl;

    return 0;
}
```

* Que tipo de clase debe de contener al menos una funcion pura virtual en C++?
    * Una clase abstracta.

* Que cambios se deben de hacer para que el codigo de C++ compile ?
    * Remove the constexpr qualifier from Line 5.
    * Remove the constexpr qualifier from Line 2.
    * Add the constexpr qualifier to Line 3.
    * Add the constexpr qualifier to Line 4.
    * Remove the constexpr qualifier from Line 1.

``` cpp
#include <iostream>
using namespace std;

class Vector {
public:
    constexpr Vector( double i, double j, double k ) // Line 1
    : ivec( i ), jvec( j ), kvec( k )
    {}

    constexpr Vector( const Vector &rhs )   // Line 2
    : ivec( rhs.ivec ), jvec( rhs.jvec ), kvec( rhs.kvec )
    {}

private:
    double ivec, jvec, kvec; // Line 3
};

int main(int argc, char **argv)
{
    Vector vec1( 2, 7, -1 ); // Line 4
    /* No compila aqui porque no le estas dando una constexpr para ser inicializada.A*/
    constexpr Vector vec2( vec1 ); // Line 5
    Vector vec2( vec1 ); // Line 5

    return 0;
}

```

* Al escribir un programa multithread, usando la libreria de multithread que es valido acerca de threads accediendo recursos compartidos?
    * Resource sharing entre threads no puede ser seguro en todas las situaciones y es mejor evitarlos.
    * Cuando un multithread comparte un recurso, el orden de que los threads acceden el recurso no importa porque cada uno tiene una instancia virtual del recurso.
    * Hay bastantes cosas que un thread debe de ser en orden de compartir seguramente un recurso.
    * Si un thread "bloquea" un recurso, el recurso es liberado automaticamente cuando el thread termina.
        * Correcto.
    * Cuando multiples threadsson accedidos por un recurso compartido, el control de accesso es hecho automaticamente por un ambiente runtime de C++ y es seamless de los threads individuales.

* Cual es una expresion C++ valida para crear y usar el using alias?
    *

``` cpp
#include <iostream>
using namespace std;

typedef int MYVAR1;
MYVAR1 m1;

alias MYVAR4 long; // Unknown type name 'alias'

using MYVAR2 = char;
MYVAR2 m2;

type MYVAR3 double; // Unknown type name 'type'

typedef MYVAR5 using int; // Unknown type name 'MYVAR5'

int main(int argc, char **argv)
{
    m2 = 'a';

    return 0;
}
```

* Dado un arreglo de punteros a funciones de abajo, cuales de las siguientes lineas debe de agregarse en el loop en **** ya que funciones sucesivas fx(), fy() y fz() son apuntados y ejecutados por ciclo?

``` cpp
#include <iostream>
using namespace std;

void fx() {}
void fy() {}
void fz() {}

typedef void(*PFvv)();
PFvv functions[3] = {fx, fy, fz};

int main(int argc, char **argv)
{
    for (int i = 0; i < 3; i++ ) {
        /*****/
//        PFvv[i](); // Redefinition of 'i'
//        *functions[i](); // Indirection requires pointer operand ('void' invalid)
//        &functions[i](); // Cannot take the address of an rvalue of type 'void'
        functions[i]();
        functions[i];
    }

    return 0;
}
```

* Throwing y cachar exceptions de C++ es una alternativa de los siguientes tecnicas.
    * Running the program with stack tracing enabled
    * Returning error codes
        * Ok
    * Using hardware exceptions
    * Using assertions
        * Ok
    * Exhaustive debugging

* Que es cierto acerca de el programa de C++11?
    * Line 1 does nothing if NDEBUG is not defined.
        * False
    * The program compiles normally, but prints the warning message If the collection is empty.
    * False
    * Line 2 results in a compiler error if the collection is empty.
        * Ok
    * Line 2 will cause a compiler error because ">>" will be mistaken for the right-shift operator.
    * Line 2 results in a compiler error if type std::vector<int> is not an empty class.

``` cpp
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void processCollection(T t) {
    // Static_assert failed "collection is empty"
    static_assert(std::is_empty<T>::value, "collection is empty"); // Line 1

    // ...
};

int main(int argc, char **argv)
{
    std::vector<int>    ages;

    // ...
    /*Static assert revisa estaticamente el codigo, como el ages esta vacio, se puede detectar que va a tener un
      error a checar si esta vacio en linea 1*/
    processCollection<std::vector<int>>(ages);  // Line 2

    return 0;
}
```

* Cual es el equivalente DeMorgan equivalente al statement? return !a || !b !(a||b)
    * return !b || !a;
    * return !a && !b;
    * return a && b;
    * return !(a && b);
        Ok
    * return !(a || b);

* Cual de los siguientes es correcto acerca de weak_ptr?
    * Cada una de las instancias no incrementan el contador de referencia cuando un objeto puntero es compartido.
    * Una instancia debe de ser inicializada por un objeto shared_ptr o weak_ptr.

* Cuales correctamente identifican los resultados de construir un codigo C++ de abajo?
    * Compilacion genera un error debido a que main() no esta permitido para acceder un miembro protegido de SomeClass.
    * Compilacion genera un error debido a que SomeFunc() no esta permitido para acceder un miembro protegido de SomeClass.
    * Compilacion genera un error debido a que Another() no esta permitido para acceder un miembro protegido de SomeClass.

``` cpp
#include <iostream>
using namespace std;

class SomeClass {
protected:
    int data;
    friend class AnotherClass;
};

void SomeFunc(SomeClass sc) {
    sc.data = 5; // 'data' is a protected member of 'SomeClass'
}

class AnotherClass {
public:
    void Another(SomeClass sc) {
        sc.data = 25; //data es protegido de SomeClass
    }

    friend void SomeFunc(SomeClass sc);
};

int main(int argc, char **argv)
{
    SomeClass sc;
    SomeFunc(sc);

    cout << sc.data << endl; // 'data' is a protected member of 'SomeClass'

    return 0;
}
```

* Cuales son verdaderos?
    * It cannot be assigned to.
        True.
    * It can be passed to a function by value.
    * It cannot be returned from a funtion by value.
        * True.
    * It can be copied.
    * Another class can be derived from it.
        * True.

``` cpp
#include <iostream>
using namespace std;

class BBus {
    int     DriverID;
    string  routeName;

    BBus(BBus &orig) {
        DriverID = orig.DriverID;
        routeName = orig.routeName;
    }

    BBus& operator=(BBus &rhs) {
        DriverID = rhs.DriverID;
        routeName = rhs.routeName;
        return *this;
    }

public:
    BBus(int id = 0, string rt = "") : DriverID(id), routeName(rt) {}
};

class C : public BBus {
public:
    void print() {
        cout << __func__ << endl;
    }
};

void testB(BBus objB) {
    cout << __func__ << endl;
}

/*
BBus testB2() {
    BBus objB;
    return objB; // Calling a private constructor of class 'BBus'
}
 */

int main(int argc, char **argv)
{
    BBus obj;

    BBus obj3;
    //    obj3 = obj; // 'operator=' is a private member of 'BBus'

    //    testB(obj); // Calling a private constructor of class 'BBus'

    //    BBus obj2(obj); // Calling a private constructor of class 'BBus'

    C objC;

    objC.print();

    return 0;
}
```

* Cuales de los siguientes statements son validos acerca del uso de algoritmos de STL con STL containers?
    * Algoritmos de STL son proveidos para operaciones comunmente realizadas en contenedores de STL.
        * Ok
    * Algoritmos de STL son usados con los contenedores de STL a travez de iteradores.
        * Ok

* Cuales de los siguientes statements describen correctamente excepciones de C++.
    * Cuando una excepcion es thrown,  y hay mas de un handler de excepciones para este tipo de excepcion, el control es transferido para manejar al mas cercano punto de excepcion.
        * True
    * Cuando una excepcion es disparado, no se puede tirar mas.
        * Falso.
    * un try block puede ser declarado sin ningun bloque de catch.
        * False
    * Cuando una excepcion es disparada, todos los objetos dinamicamente creados son released y sus destructores son llamados.
        * False
    * Si hay multiples catch blocks, las excepciones que capturan no podrian venir de la misma herarquia de herencia.
        * False
* Cual de los siguientes declaraciones correctamente usa el overloading del operator << de cout para imprimir el contenido de un class user-defined de tipo Record?
    * std::ostream& operator <<(std::ostrearas, Records);

``` cpp
#include <iostream>
using namespace std;

//add declaration here

int main()
{
    Record myRecord;

    // other code omitted
    cout << myRecord << endl;
}
```

* Cual de los siguientes son errores con el uso de la memoria dinamica en C++?
    * Hay un intento de acceder a la memoria alojado en el heap despues de que se destruyera.
        * True
    * Allocation con un new operation debe de estar dentro de un try/catch
        * Falso.
    * Hay un intento de remover un objeto que ha sido declarado en el stack.
        * True
    * Debido a que el chequeo del puntero esta sobreescrito, la memoria alojada no puede ser accedido o liberado.
        * Falso
    * Hay un intento de alojar memoria deleted en el heap sin usar un puntero.
        * Falso

* Cual de los siguientes statements acerca de funciones virtuales en C++ son validos?
    * Un miembro data puede ser accedido como virtual.
        * False
    * Una funcion estatica puede ser declarada virtual.
        * Falso, funciones estaticas no pueden ser declaradas virtual.
    * Una funcion virtual necesita ser declarada virtual solamente en la clase base y opcionalmente en las clases derivadas.
        * True
    * Un operator puede ser declarado como virtual.
        * True
    * Un funcion virtual puede ser declarada como virtual.
        * False

* Cual de los siguientes statements correctamente describe el uso de unrestricted union C++?
    * Es permitido contener miembros de tipo de clase.
        * True
    * No es permitido contener miembros de un built-in type.
        * False
    * Tiene el keywork unrestricted  en el nombre de union.
        * False
    * Debe de contener un constructor.
        * False
    * Debe de definir un operador de asignacion
        * False.
* Cuales de las siguientes lineas de codigo de C++ son implementaciones validas para una funcion Penguin swim() definido abajo?

``` cpp
#include <iostream>
using namespace std;

class Animal {
private:
    int position;
public:
    Animal() { position = 0; }
    void changePosition(int i) {
        position += i;
    }
};

class WalkingAnimal : virtual public Animal {
public:
    void move() { changePosition(2); }
};

class SwimmingAnimal : virtual public Animal {
public:
    void move() { changePosition(1); }
};

class Pengiun : public WalkingAnimal, public SwimmingAnimal {
public:
    void swim() {
        // insert code here
        SwimmingAnimal.move(); // NOk, Clase.funcion() no es un syntaxis correcto
        SwimmingAnimal::move(); // Ok , scope::a funcion publica.
        Animal::changePosition(2); //Ok
        move(); // NOk, Cual move? Necesita scope
        position += 2;
    }
    void walk() {}
};

int main(int argc, char **argv)
{
    return 0;
}
```

* Dado un operator unario sobrecargado, cuales de los siguientes son opciones legales con respecto al numero de parametros para ser usados?
    * Un parametro dummy, cuando el operador es de un tipo particular de incremento/decremento de una funcion miembro.
        * True, para diferenciar entre postfijo y prefijo.
    * Un parametro, cuando la funcion operador es de un tipo particular de incremento/decremento (no un miembro de la clase).
        * False
    * Cualquier numero de parametros,  cuando una funcion operador es free standing (no un miembro de la clase).
    * No parametros, cuando la funcion operator es una funcion free standing( no un miembro de la clase)
        * False, para no parametros requieres el objeto implicito this.
    * No parametros, cuando la funcion de operator es miembro.
        * True

* Cuales de los siguientes statements son verdaderos acerca del uso de promise y future en el snippet de abajo. cuando solamente usamos la libreria de multithreading que es parte de la libreria standard de C++.
    * Despues de la asignacion de un valor a y1 en Linea I, la funcion thread func1() puede asignar un nuevo valor al objeto promesa y el valor puede asignarse a variable y1 con otra llamada de get() como en Linea K.

``` cpp
#include <iostream>
#include <future>
using namespace std;

int func1(std::future<int>& delayedParam)
{
    int x = delayedParam.get();     // Line A

    // do other work here...

    int y = function_potentially_throwing_exception();  // Line B

    return y;                       // Line C
}

void func2(std::promise<int> &result, std::promise<bool> &done)
{
    // do other work here...

    result.set_value(10);           // Line D
    done.set_value(true);           // Line E

    // could do other work here...
}

int main()
{
    //-----------------for func1----------------------------
    std::promise<int>   promisedArgument;
    std::future<int>    futureArgument = promisedArgument.get_future();

    auto f = std::async(std::launch::async, func1,
                        std::ref(futureArgument));  // Line F

    promisedArgument.set_value(4);                  // Line G

    try {
        bool isValid = f.valid();                   // Line H
        int yl = f.get();                           // Line I

        isValid = f.valid();                        // Line J
        int y2 = f.get();                           // Line K
    }
    catch (...) {
    //...
    }

    //--------------for func2--------------
    std::promise<int>       resultPromise;
    std::promise<bool>      donePromise;

    std::future<int>    resultFuture = resultPromise.get_future();
    std::future<bool>   doneFuture = donePromise.get_future();

    std::async(std::launch::async, func2,
               std::ref(resultPromise), std::ref(donePromise) );    // Line L

    bool done = doneFuture.get();           // Line M
    int result_f2 = resultFuture.get();     // Line N

    // do other things with result_f2 ...

    return 0;
}
```

* Cual de los siguientes identifica correctamente la salida de ejecucion del codigo C++ de abajo?
    * Type of new_arg is not const / Type of new一arg is not const / Type of new_arg is not const

``` cpp
#include <iostream>
using namespace std;

template<class T>
void stripConst( T arg ) {
    typename std::remove_const<T>::type new_arg;

    if (std::is_const< decltype(new_arg) >::value)
        cout << "Type of new_arg is const" << endl;
    else
        cout << "Type of new_arg is not const" << endl;
}

int main(int argc, char **argv)
{

    /* El tipo siempre checa el new_arg que es un local variable que no cambia basado en la entrada.
       Asi que siempre sera not const.*/
    stripConst( "Blinkin" );
    stripConst( 676 );
    stripConst( 3.14 );

    return 0;
}
```

* Para las declaraciones de C++ de abajo, cuales son operadores validos?

``` cpp
#include <iostream>
using namespace std;

enum REG {stocks, bonds};
enum LTC {swaps, swaptions};
enum DRV {futures, options};

REG team1;
LTC team2;
DRV team3;

int main(int argc, char **argv)
{
    //    team2 = 1; // Al parecer no se puede asignar ints a valores enum.
    //    team1 = stocks + 1;  // Al parecer no se puede asignar ints a valores enum.
    //    team3 = options + futures; // No hay valor en el enum definido para esta suma .
    /*  Correcto.*/
    team1 = bonds;

    //    team1 = futures; // Tipo no es de este enum.

    return 0;
}
```

* Un programador a decidido el guardar objetosde tipo user defined (una estructura) dentro de un unordered_set. Cual de los siguientes pasos deben de considerarse para que funcione apropiadamente?
    * La estructura debe de tener un operator() para que los elementos puedan ser localizados en una coleccion.
    * La estructura debe de crear una especializacion de std::hash para el tipo de user defined.
    * La estrucrua debe de tener un operator == () en orden de ser soportado por esta coleccion.
        * True, como es set, entonces tienes que ver si hay algun key que ya esta para no duplicarlo.
    * La estructura debe de tener un constructor por default.
    * La estructura debe de tener un operator<() asi que los elementos pueden ser guardados en un lugar correcto de la collecion.
        * Falso, como es unordered, entonces no necesitas comparar cual es menor o mayor.

* Dado el codigo de abajo, cuando se usa un regular expression library, cuales de los siguientes statements son verdaderos para la ejecucion de Linea 1?
    * El element match [n] corresponde al caracter nth del match.
    * El size() member del objeto match contiene el numero de matches encontrado en el target string.
        * True.
    * El elemento match [n] corresponde al nth match de la expresion del target string.
        * True

* Un requerimiento  especificado para un C++ class llamado Rotator llama un manejador exclusivo de un recurso critico. Ha sido decidido enforzar la exclusividad en parte para prevenir la clase de ser copiado. En adicion, la llamada de diseño para el uso del compilador genera un constructor por defecto. Cual de los siguientes pasos pueden ser implementados para seguir este requerimiento?
    * Declarar un operator= y explicitamente deleted it.
    * Declarar un default destructor y explicitamente deleted it.

* Dado el C++ except de abajo, cuales son las siguientes tecnicas que pueden ser usados para asignar un puntero rw con puntero w.
    * Const_cast.
        * True
    * Reinterpret_cast
        * Falso, reintepretatred cast es bajo nivel de intepretacion de bits.


``` cpp
#include <iostream>
using namespace std;

class widget {};

int main(int argc, char **argv)
{
    widget const *cw = new widget;
    widget *w;

/*
    w = cw; // Assigning to 'widget *' from incompatible type 'const widget *'
    w = reinterpret_cast< widget* >(cw); // Reinterpret_cast from 'const widget *' to 'widget *' casts away qualifiers
    w = static_cast< widget* >(cw); // Static_cast from 'const widget *' to 'widget *', which are not related by inheritance, is not allowed
*/
    w = const_cast< widget* >(cw);

    return 0;
}
```

* Cuales de los siguientes son declaraciones correctas de un puntero y una asignacion de una funcion miembro de C++ avg en class MyClass?
    * double (MyClass::*f)() = MyClass::avg;

* Cual de los siguientes statements acerca de C++ son correctos?
    * Va haber un error en linea B porque el puntero myPet no refiere a ningun objeto.

``` cpp
#include <memory>
#include <iostream>
using namespace std;

class animal {
    string name = "";
public:
    void setName(string n) { name = n; }
    string getName(void) { return name; }
};

void process(animal *pet)
{
    //I already have a pet
    unique_ptr<animal> myPet(new animal);   // Line A
    myPet->setName("Fluffy");

    // now you are getting a pet
    unique_ptr<animal> yourPet;

    // I'll give you my pet
    yourPet = std::move(myPet);                  // Line D

    // No puedes setear nombre ya que no tienes control.
    myPet->setName ("Not Fluffy");          // Line B

    // Tomar el control de nuevo
    myPet.reset (pet);

    // Es posible ahora ya que tienes ownership.
    myPet->setName("New Fluffy");
}

int main ()
{
    // in main...

    animal *stray = new animal;

    stray->setName("Scratchy");
    process (stray);
    string name = stray->getName();         // Line X

    // other code here

    return 0;
}
```

* En el siguiente codigo de C++, cual de los siguientes statements son correctamente identificados como Mon de un enum puede ser asignado a una variable var?


``` cpp
#include <iostream>
using namespace std;

int main ()
{
    enum DAY { Mon = 11, Tue = 12 };

    enum DAY var = Mon;
    DAY var = DAY::Mon;
//    enum DAY var = dynamic_cast<enum DAY>(Mon); // 'enum DAY' is not a reference or pointer
    enum DAY var = DAY::Mon;
//    enum DAY var = DAY.Mon; // 'DAY' does not refer to a value

    return 0;
}
```

* Cual de los siguientes son statements correctos acerca del comportamiento del operador de dynamic_cast de C++?
    * El operador dynamic_cast puede solamente ser aplicado a un puntero o referencia de un objeto polimorfico.
        * False
    * El operator dynamic_cast puiede ser aplicado a un puntero que retorna cero si la operacion falla.
        * Correcto.
    * El operator de dynamic_cast es un subset del comportamiento del reinterpret_cast?
        * False
    * Un dynamic_Cast dispara un throw error si la operacion falla
        * False
    * El dynamic_cast falla si se usa para upcasting?
        * False

* Un programa ha definido parcialmente una funcion template compliance con C++11, Al no saber cuales son los tipos de lhs y rhs, el coder no esta seguro de como especificar el valor de retorno de esta funcion? De que manera se puede programar?
    * The coder must use auto as the return type and let the compiler determine what to replace it with, such as: auto myfunc (const T1 &lhs, const T2 &rhs) {return lhs + rhs;}
        * True
    * The coder must use the utility function decltype() to determine the return type, such as: decltype (lhs + rhs) myfunc (const T1 &lhs, const T2 &rhs) {return lhs + rhs;}
        * True
    * The coder must specify a single return type that will be returned from any instantiation of the template function.
        * Falso
    * The coder must use a combination of auto and decltype: auto myfunc (const T1 &lhs, const T2 &rhs) -> decltype (lhs+rhs) {return lhs + rhs;}
        * Falso, mala syntaxis con el -> y el return al mismo tiempo.
    * The coder must specify one of template parameter types as the return type, then ensure that the template function converts/casts its results to match that return type.
        * True

``` cpp
#include <iostream>
using namespace std;

template<class T1, class T2>
// RETURN-TYPE-HERE myfunc(const T1 &lhs, const T2 &rhs) {return lhs + rhs;}
// auto myfunc (const T1 &lhs, const T2 &rhs) {return lhs + rhs;} // 'auto' return without trailing return type; deduced return types are a C++14 extension

// decltype(lhs + rhs) myfunc (const T1 &lhs, const T2 &rhs) {return lhs + rhs;} // Use of undeclared identifier 'rhs'

auto myfunc(const T1 &lhs, const T2 &rhs)->decltype(lhs+rhs) {return lhs + rhs;}

int main ()
{
    return 0;
}
```

* Cuales de los siguientes NO son segmentos validos de codigo cuando son insertados en un programa de C++ (opciones para un punto de insercion dado no son mutualmente exclusivos)?
    * **1** : std::unordered_map<std::string, int> colorCommands = {{"red", 3}, {"yellow", 2}, {"green", 1}};
        * Este es correcto
    * **1** : std::unordered_map<std::string, int> colorCommands; colorCommands["red”] = 3; colorCommands["yellow"] = 2; colorCommands["green"] = 1;
        * Este NO es correcto
    * **1** : std::unordered_map<std::string, int> colorCommands; colorCommands.insert(std::make_pair("red", 3)); colorCommands.insert({ "yellow", 2 }); colorCommands.emplace("green", 1);
        * Este es correcto
    * **2** : switch(colorCommands.find(color))
        * Este NO es correcto
    * **2** : switch (colorCommands[color])
        * Este es correcto.

``` cpp
#include <iostream>
#include <unordered_map>

std::string checkTheLight() {
    return "green";
}

int main ()
{
    enum colors {green, yellow, red};

    /**1**/
    std::unordered_map<std::string, int> colorCommands = {{"red", 3}, {"yellow", 2}, {"green", 1}};
/*
    std::unordered_map<std::string, int> colorCommands;
    colorCommands["red"] = 3;
    colorCommands["yellow"] = 2;
    colorCommands["green"] = 1;

    std::unordered_map<std::string, int> colorCommands;
    colorCommands.insert(std::make_pair("red", 3));
    colorCommands.insert({ "yellow", 2 });
    colorCommands.emplace("green", 1);
*/
    std::string color = checkTheLight();

    /**2**/
//    switch (colorCommands.find(color)) // Statement requires expression of integer type ('iterator' (aka '__hash_map_iterator<__hash_iterator<std::__1::__hash_node<std::__1::__hash_value_type<std::__1::basic_string<char>, int>, void *> *> >') invalid)

    switch (colorCommands[color])
    {
    case green:
        std::cout << "get going";
        break;
    case yellow:
        std::cout << "slow down";
        break;
    case red:
    default:
        std::cout << "stop";
        break;
    }

    std::cout << std::endl;

    return 0;
}
```

* Un programador desea construir un nuevo tipo, basado en is_floating_point<T> en la libreria standard de C++11. Este nuevo trait no solamente validara tipos de punto flotante built-in, sino complex::<T>, parametrizado con los mismos tipos. CUal de los siguientes declaraciones cumplen con esto?
    * template< class T > struct is_complex_or_fp< std::complex< T > > std::is_floating_point< T > { };
    * template< class T > struct is_complex_or_fp : std::is_floating_point< T > { static constexpr bool value{true}; };
        * Ok
    * template< class T > struct is_complex_or_fp : std::ia_floating_point< T > { }; template< class T > struct is_complex_or_fp< T > : std::is_floating_point< std::complex< T > > { };
    * template< class T > struct is_complex_or_fp : std::is_floating_point< T > { }；template< class T > struct is_complex_or_fp< std::complex< T > > : std::is_floating_point< T > { };
        * Ok
    * template< class T > struct is_complex_or_fp< T > : std::is_floating_point< std::complex< T > > { };


``` cpp
#include <iostream>
#include <complex>

/*
template< class T >
struct is_complex_or_fp< std::complex< T > > std::is_floating_point< T > { }; // Explicit specialization of non-template struct 'is_complex_or_fp'
*/

/* type struc is_complex es template*/
template< class T >
struct is_complex_or_fp : std::is_floating_point< T > { static constexpr bool value{true}; };


/*
template< class T >
struct is_complex_or_fp : std::is_floating_point< T > { };

template< class T >
struct is_complex_or_fp< T > : std::is_floating_point< std::complex< T > > { }; // Class template partial specialization does not specialize any template argument; to define the primary template, remove the template argument list
 */


template< class T >
struct is_complex_or_fp : std::is_floating_point< T > { };

template< class T >
struct is_complex_or_fp< std::complex< T > > : std::is_floating_point< T > { };


/*
template< class T >
struct is_complex_or_fp< T > : std::is_floating_point< std::complex< T > > { }; // Explicit specialization of non-template struct 'is_complex_or_fp'
*/

int main ()
{
    return 0;
}
```

* Cual de los siguientes statements son verdaderos con respecto al codigo de C++?
    * El constructor de Course(double d) puede que no llame otro constructor como Course(int a).
        * Falso
    * El constructor por defecto resulta en un objeto con todos los miembros si inicializar.
        * Falso, las variables ya estan inicializadas.
    * El constructor por defecto resulta en un objeto con todos los miembros de datos inicializados con los valores mostrados en la definicion de la clase.
        * True
    * El uso de braces para la instancia de la clase de objetos course1,course2, course 3 y course4 no son sintaxis validos en C++
        * Falso, este uso es valido.
    * Miembro de datos estatico no debe de inicializarse en la definicion de la clase como se muestra
        * True, el dato estatico se tiene que inicializar afuera de la clase.

``` cpp
#include <iostream>

class Course {
    static int  classCount = 0; // Non-const static data member must be initialized out of line
    std::string courseName {"CS101"};
    int         room = 100;
    int quizzes[5] {0, 0, 0, 0, 0};

public:
    Course( ) {};
    Course(int a) : room(a) {}
    Course (std::string b) : courseName(b), room(200) {}
    Course(double d) : Course( static_cast<int>(d) ) {}
};

int main ()
{
    Course course1{};
    Course course2{300};
    Course course3{"EnglishlOl"};
    Course course4{3.14};

    return 0;
}
```

* Cual de los siguientes cambios deben de ser realizados en el codigo de C++ de abajo para que la definicion de la clase Wdiget sea const-correct para su uso en main()?
    * Change Widget(Widget& w); to Widget(const Widget& w);
        * Ok
    * Change Gizmo (int p, int r) ; to Gizmo (const int p, const int r);
        * NOk
    * Change Widget& operator=(Widget& rhs); to Widget& operator=(const Widget& rhs);
        * NOk
    * Change Widget (Gizmo& g) ; to Widget (const Gizmo& g);
        * Ok
    * Use const_cast during assignment otherWidget = basicWidget;
        * NOk


``` cpp
#include <iostream>

struct Gizmo {
    int pressure, rpm;
    Gizmo(int p, int r) : pressure(p), rpm(r) {}
//    Gizmo(const int p, const int r) : pressure(p), rpm(r) {}
};

struct Widget {
    int temp, speed;
    Widget() : temp (68), speed(100) {}

//    Widget(Widget& w);
    Widget(const Widget& w); //ok

    Widget& operator=(Widget& rhs);
//    Widget& operator=(const Widget& rhs);

//    Widget(Gizmo& g);
    Widget(const Gizmo& g);
};

int main(int argc, char **argv)
{
    const Widget prototype;

    Widget basicWidget = prototype; // No matching constructor for initialization of 'Widget'

    Widget otherWidget;
    otherWidget = basicWidget;

    const Gizmo gadget(10, 100);

    Widget thirdWidget(gadget); // No matching constructor for initialization of 'Widget'

    return 1;
}
```

* Cual de las siguientes acciones son requeridas para lograr las especificaciones de la clase C++ que contendra alguna funcionalidad helper de proposito especial con los requerimientos de abajo?
   1) The functionality is used by more than one public member function in a given class.
   2) The functionality accesses private data members of the class.
   3) The functionality must be a separate function.
   4) The functionality must be available to derived classes but not available to users of the derived directly.

    * Put the functionality in a member function and make its access level private.
        * Nok
    * Put the functionality in a friend function of the given class.
        * Ok
    * Put the functionality in a member function and make its access level protected.
        * Ok
    * Put the functionality in a separate class and inherit from that class.
        * Ok
    * Put the functionality in a global function that is called by the class.
        * Nok

* En la clase Box de C++, el operator == esta sobrecargado en la que los boxes del mismo volumen son considerados iguales. Dado que 2 boxes de este tipo (llamados box1 y box2) comparison 1 y 2 deben de realizarse. Que se puede usar para implementar el tercero (comparison 3) mostrado abajo.

    * Implement a member operator== taking a Box and a double.
        * False, operator== debe de tener solamente el double y ese ya esta implementado.
    * Implement a global function called operator== which takes a double and a Box and makes it a friend of class Box.
        * Correcto
    * Modify one of the existing member operator== implementations so that it takes an additional parameter.
        * False
    * The existing overloaded operators already handle the 3rd comparison.
        * False
    * Implement a global functino called operator== which takes a double and a Box and have it call an existing member operator== implementation with conforming parameters.
        * False
