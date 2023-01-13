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
