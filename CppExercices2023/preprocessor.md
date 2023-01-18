# Preprocessor
* Preprocessor maneja el programa antes de la compilacion.
* Si la ejecucion del procesador ve unos directivos que pueden ser reemplazados, se llama al preprocessador para que cambie esos directivos con sus valores especificos.
* #include, #ifdef, #ifndef, #define, ect.

* Hay 4 tipos principales de directivos de preprocesador.
    * Macros.
    * File inclusion.
    * Conditional Compilation
    * Other directives.

## Macros
* Macros son piezas de codigo que reemplaza el nombre por codigo. el #define se usa para definir macros.
* Macros con argumentos son como funciones. Es importante tener parenthesis.

## File inclusion
*  Inclusion de header mediante #include.

## Compilacion condicional.
* Directivos que ayudan al compilador a definir partes variantes del programa o el ignorar partes del codigo. Esto puede ser hecho mediante dos directivos, #ifdef y #ifndef.

```
#ifdef macro_name
    statement1;
    statement2;
    statement3;
    .
    .
    .
    statementN;
#endif

```

## Otros directivos
* #undef se usa para remover una definicion de un macro existente, normalmente usado dentro de ifdef o ifndef. Cada ifdef que use este macro siempre retornara false y no entrara al scope.

```
#undef LIMIT
```
* #pragma es un directivo que es usado para encender y apagar features. Este directivo es compiler dependent.


```
#include <bits/stdc++.h>
using namespace std;

void func1();
void func2();

/* startup sera llamado antes de que main() se llame porque depende del tooling del compilador para llamar estos primeros.*/
#pragma startup func1
/* exit sera llamado despues de que el control de main() haya acabado.*/
#pragma exit func2


void func1()
{
	cout << "Inside func1()\n";
}

void func2()
{
	cout << "Inside func2()\n";
}

int main()
{
	void func1();
	void func2();
	cout << "Inside main()\n";

	return 0;
}


```

* #pragma warn puede ser usado para ocultar warnings de compilacion.

* El scope de los macros son del ultimo encontrado como definido. Por ejemplo:

```
/* Este header incluye MAX como 50u.*/

/* Stdio define max como 50, por ejemplo.*/
#include <stdio.h>
/* Este sobreescribe la definicion de max de stdio*/
#define max 100
int main()
{
    /* Se imprimira 100.*/
	printf("max is %d", max);
	return 0;
}
```

* Macros de tipo funcion no hacen chequeo de tipos en los parametros.

* Los argumentos de un macro function no son evaluados antes de la expansion del macro, por ejemplo.

```
#include <stdio.h>
#define MULTIPLY(a, b) a* b
int main()
{
	// The macro is expanded as 2 + 3 * 3 + 5, not as 5*8
	printf("%d", MULTIPLY(2 + 3, 3 + 5));
	/* Para solucionar debe de ser #define MULTIPLY(a, b) (a)*(b) */
	return 0;
}
// Output: 16

```

```
#include <stdio.h>
#define merge(a, b) a##b
int main() { printf("%d ", merge(12, 34)); }

```
* Concatenacion de caracteres puede ser mediante ##.

* Para definir un string se usa un # antes del parametro.

```
#include <stdio.h>
#define get(a) #a
int main()
{
	// GeeksQuiz is changed to "GeeksQuiz"
	printf("%s", get(GeeksQuiz));
}
```

* Macros pueden ser escritos en multiples lineas usando \

* Tambien hay directivos #if, #elif, #else, que tienen que tener le #endif

```
#include <stdio.h>

int main()
{
    printf( "This code is on line %d, in file %s\n", __LINE__, __FILE__ );
#line 10
    printf( "This code is on line %d, in file %s\n", __LINE__, __FILE__ );
#line 20 "hello.cpp"
    printf( "This code is on line %d, in file %s\n", __LINE__, __FILE__ );
    printf( "This code is on line %d, in file %s\n", __LINE__, __FILE__ );
}
```
* #define makechar(x)  #@x es poner x como un character.
* Puedes definir macros variantes de la siguiente manera.

```
// variadic_macros.cpp
#include <stdio.h>
#define EMPTY

#define CHECK1(x, ...) if (!(x)) { printf(__VA_ARGS__); }
#define CHECK2(x, ...) if ((x)) { printf(__VA_ARGS__); }
#define CHECK3(...) { printf(__VA_ARGS__); }
#define MACRO(s, ...) printf(s, __VA_ARGS__)

int main() {
    CHECK1(0, "here %s %s %s", "are", "some", "varargs1(1)\n");
    CHECK1(1, "here %s %s %s", "are", "some", "varargs1(2)\n");   // won't print

    CHECK2(0, "here %s %s %s", "are", "some", "varargs2(3)\n");   // won't print
    CHECK2(1, "here %s %s %s", "are", "some", "varargs2(4)\n");

    // always invokes printf in the macro
    CHECK3("here %s %s %s", "are", "some", "varargs3(5)\n");

    MACRO("hello, world\n");

    MACRO("error\n", EMPTY); // would cause error C2059, except VC++
                             // suppresses the trailing comma
}
```
* Cual es el output de esto?
    * 5, porque por defecto, el X es definido como cero aun cuando no esta definido.
``` cpp
#include <stdio.h>
#if X == 3
    #define Y 3
#else
    #define Y 5
#endif

int main()
{
    printf("%d", Y);
    return 0;
}
```

* Cual es la salida de este codigo?
    * No puedes definir funciones funciones entre macros.
``` cpp
#include <stdio.h>
#define X 3
#if !X
    printf("Geeks");
#else
    printf("Quiz");

#endif
int main()
{
        return 0;
}
```

* Cual es la salida de este?
    * 36 porque no tiene parentesis entre los parametros y se pasa tal cual quedando 36/6*6.
``` cpp
#include <stdio.h>
#define square(x) x*x
int main()
{
  int x;
  x = 36/square(6);
  printf("%d", x);
  return 0;
}
```

* Despues de preprocesamiento se crea el archivo .i

* Pragma once indica al compilador que el header solamente se incluye una sola vez.

* Cual es el siguiente output?
    * Error de compilacion porque el MAX de int MAX es convertido como 1000 antes de que el compilador cheque la sintaxis, asi que queda como 1000 = 100;
``` cpp
#include <stdio.h>
#define MAX 1000
int main()
{
   int MAX = 100;
   printf("%d ", MAX);
   return 0;
}
```
