 * alignof(), retorna el mayor power de 2 con la que puedas alinear algo.
     * cout << "Alignment of char: " << alignof(char) << endl;
         * Alignment of char: 1
 * alignas(), forza el alignment de un tipo haca una instancia.
     * alignas(16) int a[4]; printf("%p\n", a);
         * 0xbfa493e0
     * alignas(1024) int b[4]; printf("%p", b);
            * 0xbfa49000
  * unique_ptr<>::reset destruye un objeto actualmente manejado por un unique_ptr (si hay alguno) y toma ownership de p.

* new and delete. new[] y delete[]
    * Para arreglos, int *pia = new int[24];
        * Nuevo standard, int* pia = new int[10]{0,1,2,3,4,5,6};
    * Para arreglos delete pia;
* Smart pointers son templates, por eso tienes que definir entre <> el tipo que va a puntar el smart pointer.
    * shared_ptr<string> p1;

* todos los smart pointers estan definidos en header memory.

## Auto_ptr
* auto_ptr es deprecable en C++11.
    * Maneja un objeto obtenido por una expression nueva y elimina el objeto cuando el puntero es destruido.

## Unique_ptr
* Unique_ptr maneja un objeto obtenido por una expresion nueva y elimina el objeto cuando el puntero es destruido, solamente permite un ownership de puntero cambiando cuando hay una asignacion nueva con un .get()
    * Get(), retorna el puntero en p.

## shared_ptr
* Es un contenedor de punteros que se basa en un modelo de ownership  de contar referencias. Un contador se incrementa cada vez que un nuevo puntero apunta al recurso y decrementa cada vez que el destructor del puntero se llama. Al llegar el contador a cero, el recurso es liberado.

## weak_ptr
* Es una copia de un shared_ptr que no participa en el conteo de referencia de shared_ptrs, significa que el objeto referenciado puede ser leido pero no hay ningun ownership en el. Un weak_ptr pierde la referencia del recurso cuando el contador de shared_ptrs llega a cero.

* make_shared<T>(args) retorna un shared_ptr apuntando para un objeto T alojado dinamicamente. Usa args para inicializar el objeto.
* p.unique() retorna true si el objeto solamente tiene una referencia apuntando a el y false si no lo es.
* p.use_count() retorna el contador de punteros apuntando al recurso.

* Punteros smart se destruyen cuando se va el scope de su lifetime.

# Otros
* En el nuevo standard puedes inicializar punteros con un initializer_list.
    * vector<int>* pv = new vector<int>{0,1,2,3,4,5};
* Si un smart pointer no puede alocarse en memoria mandara un bad_alloc throw exception.

* Poner nothrow, decimos a una funcion que no queremos que haga un throw, y manejar el error sin parar la ejecucion.

* Reset() actualiza el conteo de referencias y elimina el objeto que apunta p.

* Allocate() aloja memoria raw sin construir para contener n objetos de tipo T.


