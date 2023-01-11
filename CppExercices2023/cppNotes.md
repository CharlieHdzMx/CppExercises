# CppPrimer

* **static_cast**, es usado cuando hay un tipo aritmetico mas grande y se convierte en un tipo aritmetico mas pequeño.
    * double scope = static_cast<double> (j/i);
* **const_cast**, es legal cuando la variable que le estamos quitando el const fue originalmente non-const.
* **reintepret_cast**, es usado para reintepretar el tipo a bajo nivel de una variable para otro nuevo.

## Statements
### Try blocks and exceptions.
* Normalmente usado cuando una parte del programa detecta un problema y no puede solucionarlo con la parte que detecta el problema.
    * **throw expression**, donde la parte que detecta la falla indica que encontro algo que no puede manejar.
    * **try blocks**, Un bloque de try inicia con un keyword de **try** y termina con clausuras de **catch**.
        * Constituye la logica normal de un programa.
        * Variables definidos en try se acaban cuando se cierra el scope.
    * **Clases de excepciones**, pasan informacion acerca de lo que paso en el throw expression y una clausura de catch.
        * Un catch contiene:
            * Keyword catch.
            * Declaration de un objeto en parentesis (talvez sin nombres).
            * Block.
    * Cuando usas el throw afuera de un try, el output es un error que termina el programa. Cuando tienes el throw en el try y tienes un catch que lo soporte, entonces el error puede dejar de terminar el programa y estaria haciendo algo diferente y personalizado. (ver cppExercises).
    * runtime.what() es una funcion que retorna el string del throw que sea de runtime. (ver cppExercises).
    * Si no hay un catch con un tipo de throw especifico que haya sido llamado, el programa terminara inmediatamente.
        * Esto es porque se transfiere el control a una funcion llamada terminate().
* Tipos de clases de errores:
    * exception,
    * runtime_error
    * range_error
    * overflow_error
    * underflow_error
    * logic_error
    * length_error
    * out_of_range

## Funciones
### Argumentos
* Referencias son diferentes nombres de una variable.
* A la hora de usar una referencia en una funcion, ayuda a no tener que definir un nuevo objeto (puntero) para ser posible de pasar un argumento de un objeto exterior a la funcion que queremos modificar en vez de tener una copia.
* Parametros de referencia que no son modificados adentro de la funcion deben de ser referenciado para ser const.
* int &r = i;
* References son una maner en la que podemos retornar diferentes outputs.

### Low level const and high level const
* Low level const es cuando el valor que se esta apuntando es const.
    * Referencias son low level const como este
        * const int & r = i; /* r es una referencia constante de i.*/
    * Punteros a un valor constante son low level const.
    * Variables constantes son low level const.
* High level const es cuando el puntero es const pero el valor es non const.
    * El high level const es ignorado cuando se llama como parametro de una funcion.

### Parametros
* Estas declaraciones son equivalentes.
    * void print(const int*);
    * void print(const int[]);
    * void print(const int[10u]);
* Para definir una referencia aun array con un tamaño especifico.
    * void print(int (&arr)[10u]);
* Pasar un arreglo multidimensional = pasar un puntero a un arreglo de 10 elementos.
    * void print(int (*matrix)[10u]);
    * void print(int matrix[][10u]);

### Funciones con parametros variantes.
* Aveces no podemos saber cuandos parametros una funcion puede necesitar. El nuevo estandar provee dos maneras que una funcion puede tomar variantes de numero de parametros.
    * Si todos los argumentos tienen el mismo tipo, podemos pasar un initializer_list.
    * Si los argumentos no tienen el mismo tipo entonces tenemos que usar un variadic template function.

### initializer_list parameter
* Es una representacion de un arreglo.
    * initializer_list<T> lst -> Initializacion por default.
    * initializer_list<T> lst {a,b,c,..}
    * initializer_list soporta los iteradores de begin() y end() y tambien size().
* A diferencia de otros contenedores, el initializer_list siempre tiene valores const.

### Ellipsis variant.
* Parametro ellipsis es la manera que Cpp permite       el uso de facilidades de la libreria de C de varargs
* Un parametro asi debe de encontrarse siempre al final.
    *  void foo(parm_list, ...);

### Trailing return type.
* En el nuevo standard, para simplificar la declaracion de  funciones  con un tipo de retorno dificil de entender es mediante el trailing.
    * auto func(int i) -> int(*)[10u];

### Default arguments.
* Podemos declarar un valor comun de los parametros de funciones que pueden ser omitidos en su llamada.
    * string screen(int sz = 24, int wid = 80);

### Inline
* El mecanismo de inline es utilizado para requerir el compilador de sustituir una llamada de la funcion sin tener que tener el overhead de cambio de contexto y de registros por la llamada de una funcion sencilla.

### constexpr functions.
* Funciones constexpr indican que una funcion contendra inputs que se pueden calcular en tiempo de compilacion.

### Pointer function
* int (*funcPtr)(uint8, uint8);

## Class
### Definicion
* Todas las funciones miembro deben de ser declarados adentro de la clase.
* Funciones miembro acceden al objeto en la que se estan llamando mediante un parametro implicito llamado **this**.

### const member functions
* void func() const;
* Objetos que son const, referencias y punteros a objetos const puede que solamente puedan llamar const functions.

### Default constructor
* Para pedirle al compilador que nos crea un contructor por defecto aun cuando tenemos varios constructores con argumentos, usamos el default asi:
* constructor() = default;

### Copy constructor, Assignment operator and destructor.
* Copy constructor tiene la syntaxis como:
    * ClassName(const ClassName& cpy);
    * Es una buena manera escribir la lista de inicializacion del constructor como el orden de la declaracion de las variables miembro. Tambien empezando con el constructor de la clase base.
    * Un constructor que llama funciones con argumentos por default puede omitir estos argumentos en la lista de inicializacion.
    * En practica es siempre bueno el proveer un constructor por defaul si otros constructores son definidos.
    * Constructors que solamente tienen un argumento y que hacen una conversion se les llama **conversion constructor**.
        * Cuando no quieres que un conversion constructor haga la conversion implicitamente, entonces defines el copy constructor como explicit.
            * explicit Class1(const string&);
* Assignment operator tiene la syntaxis como:
    * operator = (const ClassName& cpy);
* La sintaxis de un destructor como:
    * ~ClassName();

### Funciones amigas (Friend functions).
* Una clase puede permitir a otras funciones o clases el acceder sus miembros privatos.

### Mutable Data member.
* Si existe que tenemos una clase que tiene un dato miembro que podriamos querer modificar aun dentro de una funcion const, declaramos ese dato miembro como **mutable**.

### Inicializacion de datos miembro de clases.
* Con el nuevo estandar, es posible inicializar los datos miembros desde la declaracion de la clase.
    * vector<int> screen {0,1,2,3};

### Retornar *this desde una funcion miembro constante.
* Una funcion miembro constante que retorna *this como una referencia debera de tener un tipo de retorno que es una referencia a const.

### Constructor delegado.
* El nuevo estandar extiende el uso de inicializaciones de constructores para definir los delegate constructor. Delegate constructor usa otro constructor de su propia clase para realizar su inicializacion.
    * Class1():Class1(0,1,2){}

### Aggregate class
* Una clase agregada da acceso directo de sus miembros y tiene una sintaxis especial.

### Static class member.
* Static members existen afuera de cualquier objeto y contiene su valor independietemente de cualquier objeto de esa clase y con el scope de tal clase.
    * Static members no tienen ningun bound con cualquier objeto. No tienen un this pointer.
    * Tienes que definir e inicializar todas las variables estaticas en la declaracion de la clase.

## Sequential Container.
* Tipos de contenedores secuenciales.
    * **vector**, array de tamaño flexible.
    * **deque**, array de doble extremo.
    * **list**, doubly linked list, insert/delete rapido en cualquier lugar del contenedor.
    * **forward_list**, Singly linked list,
    * **array**,
    * **string**

## Assign function for contenedores
* Asigna nuevo contenido a un vector, reemplazando su contenido original, y modifica su size acordemente.
* Emplace() crea un elemento para insertar en el contenedor usando los argumentos para su constructor.
* push_back() toma un elemento ya construido para agregarlo al contenedor.
* insert() sirve para agregar un elemento en un lugar ( o iterador) especifico. Esta operacion es muy costosa. Este insert() retorna el iterador de donde se agrego el elemento (o el primer elemento en un rango de elementos insertados al contenedor).
* pop_back(), Remueve el ultimo elemento del contenedor. No retorna nada.
* erase() remueve el elemento en el iterador o posicion especifico.
* clear() limpia todo el contenedor.
* shrink_to_fit(), request  para reducir capacity() para igualar size().
* capacity(), numero de elementos c puede tener una realo
* reserve(), alocar espacio para al menos n elementos.

## String
* substr() retorna un string que es una copia de un string original. donde argumentos son la posicion donde empezaria y la cantidad de caracteres que tendra.
* find(), find_first_of(), find_last_of, find_first_not_of(), son funciones que pueden ser usado en string para encontrar caracteres.
* to_string(), pones como argumento un numero para ser transformado por un string.
* stoi(), string to int.
* stod(), string to double.
    * Si un string no se puede convertir, Estas operaciones tiran un invalid_argument exception.

## Container adaptors
* Stack
* Queue
* priority_queue, es una queue en la que determina que elemento es mas pequeño que el otro basado en una funcion comparison que se pone como argumento en la construccion del contenedor.

# Algoritmos
* Algoritmos estan en header algorithms y tambien numeric.
* Algoritmos genericos son independientes del tipo de contenedor y estan mas enfocados en iteradores y tambien en el tipo del elemento del contenedor (practicamente para comparar).
    * Algoritmos nuncan cambian el tamaño del contenedor.
## Simple find algoritmos.
* find(beg, end, val), retornar el primer iterator que el elemento es igual a val.
* find_if(beg, end, unaryPred), retorna el primer iterator en la que el elemento retorna TRUE en el unaryPred function.
* find_if_not(beg, end, unaryPred), retorna el primer iterator en la que el elementor retorna FALSE en el unaryPred function.
* count(beg, end, val), retorna el numero de tiempo en la que val sucede en beg y end.
* count_if(beg, end, unaryPred),  retorna el numero de tiempons en la que un elemento retorna TRUE al comparar el unaryPred.
* accumulate(), sum the values.
* Usualmente es mejor usar cbegin() y cend() para algoritmos que solamente leen. Pero si tienes pensado modificar el iterator que retorna, entonces requieres un begin() y end().
* equal() determina si una sequencia de un contenedor es igual a una secuencia de un segundo contenedor.
    * Los tipos de los contenedores no deben de ser los mismos pero deben de funcionar entre ellos a la hora de comparar con ==.

## Algorithms to Find One of Many Values
* Fill() llena un rango definido por iteradores con un valor especifico.
* fill_n() llena un rango definido por un size con un valor especifico iniciando en un iterator.

### Back inserter.
* Insert iterator es un iterator que agrega elementos a un contenedor.
* back_inserter es una funcion definida en iterator header, que toma una referencia a un contenedor y retorna un link de iterator de insercion de ese contenedor.
    * Usualmente se usa para crear un iterator como un destino de un algoritmo.

### Copy Algorithms
* copy(), copia los elementos de un rango de input dentro de los elementos del destino.
* replace(), Reemplaza los elementos x en un rango de un contenedor con un valor y.

### Reorden de contenedores de elementos.
* sort(), ordena los elementos en un rango de entrada para ordenarlos basado en criteria del operator < para saber cual es mayor que otro.

### Eliminar duplicados.
* unique(), ordena los elementos en un rango de entrada para eliminar los valores duplicados. El size del contenedor es mantenido.
* erase(), remove un elemento o un rango de elementos  reduciendo el tamaño del contenedor.

### Pasar una funcion a un algoritmo.
* **Predicados**, Un predicado es una expresion (funcion) que puede ser llamado y que retorna un valor que puede ser usado como condicion.
    * Hay predicados unarios o binarios.

### Stable sort
* stable_sort() ordena los elementos pero mantiene la posicion entre los elementos que son iguales.

## Iteradores
* Insert iteradores, enlazados a un contenedor e insertan elementos.
* Stream iterators, enlazado a streams de input y output y es usado para iterar a travez de un stream IO.
* Reverse iterators, se mueven backwards en vez de forwards.
    * Puedes usar la funcion del iterador reverse base() para transformar el iterator reverse a un iterador normal.

# Associative containers.
* Lookup eficiente basado en keys.
* map es una coleccion de pares de key-value. Las llaves deben de ser unicas.
* set es una collecion de keys. Las llaves deben de ser unicas.
* multimap es un map pero con llaves duplicadas.
* multiset es un set pero con llaves duplicadas.
* Debido a que los elementos de los contenedores asociativos son ordenados, se requiere que el tipo del elemento pueda ser comparado con assignment operators de inequalidad.
* A pair es un tipo de libreria que mantiene dos tipos de elementos.
    * make_pair() retorna un pair  inicializado de v1 y v2
    * p.first retorna el miembro de datos publico de key.
    * p.second retorna el miembro de datos publico de value.
* insert() agrega miembros en los contenedores asociativos.
* erase() tiene 3 versiones, una que elimina cada valor de k, otra que elimina el elemento denotado por un iterador, y otro de elimina el rango de elementos denotado entre dos iteradores.
* at() es usado en map y unordered_map, que retorna un iterador del elemento que tiene el key como indice.
* lower_bound(k), retorna un iterador al primer elemento que no menor que k.
* upper_bound(k), retorna un iterador al primer elemento con un valor mayor que k.
* equal_range(k), retorna un par de iteradores denotando los elementos con la llave k. Si k no esta, ambos son iteradores end().
* El nuevo standard, define 4 unordered containers
    * los contenedores asociativos unordered son una colleccion de buckets que cada uno contiene zero o mas elementos. Estos contenedores contienen un hash function para mapear los elementos a cada bucket. Para acceder un elemento, el contenedor primero calcula el codigo hash del elementos, que dice cual bucket deben de ser usados. Si el contenedor permite multiples elementos con una llave igual, todos estos elementos son puestos en el mismo bucket. Entonces la calidad de un contenedor unordered depende de la calidad de la funcion hash y el numero y tamaño de sus buckets.
        * bucket_count(), numero de buckets usados.
        * max_bucket_count(), la mayoria de buckets soportados.
        * bucket_size(n), numero de elementos en n bucket.
    * Por defecto, los contenedores unordered usan el operator == para comparar elementos.

## Dynamic memory.
* new, aloja e inicializa un objeto en memoria dinamica y retorna un puntero de ese objeto.
* delete, toma el puntero del objeto creado por new y destruye ese objeto y libera la memoria usada.
* smart pointers actuan como punteros regulares con una excepcion importante que se elimina automaticamente.
* **shared_ptr** permite multiples punteros  referir el mismo objeto.
    * shared_ptr<list<int>> pLst = make_shared<int>(42);
* **unique_ptr** que es el dueño del objeto que esta apuntando. Significa que si se referencia a un elemento ya apuntado, el puntero viejo deja de apuntar al elemento y solamente uno nuevo puede apuntar a este elemento.
* **weak_ptr**, que es una referencia deb#include<iostream> de un objeto manejado por un shared_ptr.
* Puedes hacer swap de pointers.

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

# Function overloading
* Cuando hay varias funciones con el mismo nombre pero con diferentes parametros, se le llamada function overloading.
*

### C Questions toptal

https://www.toptal.com/c/interview-questions

* Que es un void pointer? Puedes deferenciar un void pointer sin saber su tipo?
    * Void pointer es un puntero sin intepretacion de tipo, como no hay un tipo para saber como representarlo no se puede deferenciar sin hacer un cast. OK
* Cual es la diferencia entre #include "" y #include <>
    * #include "" es par header que son definidos personalizados y #include <> son definiciones estandares. Esto es para el preprocessaro para saber donde buscar los headers, si es <> solamente buscan en la carpeta de compilacion que es standard.
* Que es un dangling pointer y como son diferentes de leaks de memorias?
    * Dangling pointers son punteros que quedan sin apuntar a nada, esto puede suceder cuando tienes un puntero a una variable fuera de scope o que fue removido. son diferentes a memory leaks porque un memory leak es cuando no liberas un recurso de memoria y queda como consumido durante el proceso del programa. OK.
* Que esta siendo declarado en el siguiente statement?
    char(*x) (char*)?
    * un puntero a una funcion llamada x que tiene un parametro char* y un retorno char.
* Cual sera la salida del siguiente codigo
    #include <stdio.h>
    #define SQUARE(a) (a)*(a)

    int main() {
        printf("%d\n", SQUARE(4));
        int x = 3;
        printf("%d\n", SQUARE(++x));
    }
    * Es undefined bhavior porque depende del compilador de como se procesa el macro (++x)*(++x) alguns compiladores pueden ser 16 20 o 16 25
* Porque es mala idea usar gets() Sugiere un workaround.
    * Esta funcion no sae que tan grande es el buffer y sigue leyendo inclusive despues de haber salido de los rango del buffer. Alternativas es fgets().
* Cual es la diferencia entre struct y unions?
    * Structs son elementos juntos con diferentes localidades de memorias contiguas. Union usa sus elementos en la misma localidad de memoria y es usado para tener diferentes intepretaciones de una memoria.
* Este codigo convierte numeros de punto flotante a enteros usando casting
    float f = 1.0;

    int i1 = (int) f;
    int i2 = * (int *) &f;

    printf("%d\n, i1);
    printf("%d\n, i2);

    El siguiente output sucede,

    1
    1065353216

    Explica la diferencia
    * El primero convierte un puntero float a entero. La segunda conversion, hace un puntero int de una referencia de f y trata de deferenciar este puntero, en el momento de castear un float pointer a int pointer, el compilador trata raw values del float como si fueran enteros, causando este valor incorrecto (065353216 es un formato de IEEE para numeros flotantes).
* Cual es el resultado del siguiente codigo si se corre en un sistema de 32 bits?
    #include <stdio.h>
    int  main()
    {
    int a=-2;
    printf("%x",a>>3);
    }
    * a = -2, 10 01 10 1111 1111 1111 1110, 1111 1111 1111 1111, seria 0xFFFF.
### C++ toptal
https://www.toptal.com/c-plus-plus/interview-questions

* Hay una diferencia entre struct y class?
    * Si, los elementos del struct por defecto son public mientras que los de class son private.
* Que imprimiria la siguiente linea de codigo?
    #include <iostream>

    int main(int argc, char **argv)
    {
        std::cout << 25u - 50;
        return 0;
    }
    * Un numero positivo muy largo porque la operacion regresa un numero negativo pero porque es 25u se representa como entero si signo, asi que es un numero muy largo.
* Cual es el error del codigo de abajo y como deberia de ser corregido?
    my_struct_t *bar;
    /* ... do stuff, including setting bar to point to a defined my_struct_t object ... */
    memset(bar, 0, sizeof(bar));
    * Estas seteando una memoria del puntero de mystruct en vez de mystruct aqui solamente sera el espacio del puntero (32 bits o 16 bits) y si el my_struct es mas grande que eso tenemos un set de memoria insuficiente, esto se soluciona poniendo sizeof(my_struct).
* Que serian i y j despues de que el codigo de abajo sea ejcutado?
    int i = 5;
    int j = i++;
    * i seria 6 y j seria 5 porque la asignacion se hace antes del posfijo de i++, si se quisiera j ser igual que i, entonces tendria que ser prefijo ++i.
* Asumiendo buf es un puntero valido, cual es el problema en el codigo siguiente? Cual seria una alternativa para implementar que va a evitar el problema?
    size_t sz = buf->size();
    while ( --sz >= 0 )
    {
        /* do something */
    }
    * El sz es de tipo size_t asi que es unsigned int, el while siempre estara corriendo hasta el infinito porque (--0u >= 0) nunca sera negativo.
* Considera los siguientes codigos de dos abajo para imprimir un vector. Hay una ventaja entre unos o otras?
    Option 1
    vector vec;
    /* ... .. ... */
    for (auto itr = vec.begin(); itr != vec.end(); itr++) {
        itr->print();
    }
    Option 2
    vector vec;
    /* ... .. ... */
    for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
        itr->print();
    }
    * Creo que no hay una diferencia entre estos porque el prefijo y el postfijo en el for loop no diferencia entre ellos porque al final el statement se correra al mismo nivel.
* Implementa la funcion de template IsDerivedFrom() que toma clase C y clase P como un parametro de template. Este debe de retornar true cuando una clase C es derivada para clase B y false de otra manera.

    bool template<typename D, typename C>
    class IsDerivedFromHelper
    {
        class No{}
        class Yes{ No no[3]}

        static Yes Test{B*};
        static No Test{};

        public:
            enum { is = sizeof(Test(static_cast<D*>(0))) == sizeof(Yes)};
    };

    template<class C, class P>
    bool IsDerivedFrom()
    {
        return IsDerivedFromHelper<C,P>::Is;
    }

    * Tienes que identificar si el sizeof sea igual a D. Que si es igual que el de Yes es de B*.

* Es posible tener una funcion recursiva inline?
    * El compilador no los haria inline porque el compilador no puede saber cuantas veces va a entrar.
* Cual es la salida de este codigo?
    #include <iostream>

    class A {
    public:
        A() {}
        ~A() {
            throw 42;
        }
    };

    int main(int argc, const char * argv[]) {
        try {
            A a;
            throw 32;
        } catch(int a) {
            std::cout << a;
        }
    }
    * Va a retornar 32, pero tambien el destructor de a se va a llamar, y como es una excepcion doble no soportada, entonces se va a terminar el programa.
* Te han dado un programa como este:
    class Something {
    public:
        Something() {
            topSecretValue = 42;
        }
        bool somePublicBool;
        int somePublicInt;
        std::string somePublicString;
    private:
        int topSecretValue;
    };
    implementa un metodo para obtener el topSecretValue para cada objeto Something*. El metodo debe de ser compatible cross platform y no dependiente de sizeof(int,bool,string).

    * Crear una clase SomethingReplica con el mismo orden de los miembros pero publicos, tener una funcion para retornar topSecretValue y hacer una reintepretacion de classe Something a SomethingReplica, y de esta manera poder llamar la funcion de retorno de topSecretValue.

* Implementa una funcion void F() que toma punteros de dos arrays A y B y un size N. Asi llena B donde B[i] es el producto de todos los A[j] donde j != i. Por ejemplo A = {2, 1, 5, 9} y B es {45, 90, 18, 10}.

    *
