* Sintaxis.
    * template <typename T> int comp(const T& v1, const T& v2);

* Compilador deducira el tipo de T al hacer un llamado de la funcion con parametros especificos, por eso la entrada es muy importante y si la salida no esta relacionada con la entrada, no se puede definir al menos que hagamos esto:

``` cpp
    template<typename T, typename U>
U largest_elem(const T number_set, size_t len)
{
    U largest = number_set[0];
    for(size_t index = 0; index < len; ++index)
        if (number_set[index] > largest)
            largest = number_set[index];
    return largest;
}
```

* Se define un typename de U para el retorno del template.
    * Y se hace una llamada asi, en la que entre <> especificamos que tipo se van a usar para T y para U, double l = largest_elem<double [], double>(numbers, 10);

* No hay distincion entre typename y class durante el uso de template. Pueden usarse de la misma manera
    * template <typename T, class U> calc (const T&, const U&);

* Si tienes parametros, entonces el compilador puede deducirlo por el tipo del argumento que se paso. Por ejemplo
    * cal<int>(a,b) // Ok, segundo parametro U es implicitamente deducido por b.
    * cal<int>(a); //No ok, segundo parametro no se puede deducir, falta parametro.
    * cal<int, double> (a) // No ok, falta parametro, falla de sintaxis.

* Tambien puedes usar el traling para definir un retorno.
    template <typename It> auto fcn(It beg, It end) -> decltype(*beg);

* Cuando inicializamos un puntero a una funcion con un template, entonces se deducen los tipos de la declaracion del puntero de funcion.
    * template <typename T> int compare(const T&, const T&);
        int (*pf1)(const int&, const int&) = compare;

# Template class
* Como las funciones, los template class son usados para definir una class independiente de su tipo de datos.
    * template<typename T> class Array
    {
        public:
            Array(T& a[],int s);
    }

template <typename T> Array<T>::Array(T& a[], int s);

template <typename T> void Array<T>:: print();

* Como ves la sintaxis de una clase template contiene primero el template <typename T>, luego el retorno y siempre el prefijo de clase<T>.

* Si hay mas de un typename en la declaracion del template class, cada instancia debe de tener el mismo numero de templates y el orden.

``` cpp
#include <iostream>
using namespace std;

/* Nota que hay 2 typename*/
template <typename T, typename U> class A {
	T x;
	U y;

public:
	A() { cout << "Constructor Called" << endl; }
};

int main()
{
    /* Definir siempre entre <> y en correcto orden los tipos usados en esa instancia. */
	A<char, char> a;
	A<int, double> b;
	return 0;
}
```
* Cuando hay un signature de una funcion template y una funcion non-template, siempre se prefiere la funcion non-template.

* Puedes usar variadic parameters con template sintaxis.
    * template <typename T, typename... Args>
        void foo(const T &t, const Args& ... rest);
* Como no puedes definir facilmente el numero de argumentos en <>, se prefiere definir los parametros entre () y permitir el compilador deducir los tipos.
    * foo(i, s, 42, d); // Nota que no hay <> en esta instancia.
* Puedes definir tipos especificos de un template para poder implementarlos de otra manera diferente a lo que tienes en el template general.
    * template<size_t N, size_t M>
        int compare(const char (&)[N], const char (&)[M]);
            * Aqui se ve que se especializan los parametros de template y los parametros de la funcion.
    * template <>
        int compare(const char* const &p1, const char* const &p2)
        {
        return strcmp(p1, p2);
        }

* Lvalues son referencias u objetos que pueden ser usados para copiar, la referencia es T&
* Rvalues son costantes u objetos con doble referencia para move, T&&.

* std::forward  sirve para indicar al compilador a usar rvalue en vez de deducir un lvalue por defecto cuando tienes 2 template overloaded functions.
    * Rvalue entonces puede mover (en vez de copiar) un elemento de un contenedor optimamente.



