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

