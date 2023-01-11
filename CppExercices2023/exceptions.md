# Exceptions
## Statements
### Try blocks and exceptions.

https://www.geeksforgeeks.org/cpp-exception-handling-interview-questions-and-answers/?ref=rp

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

```
#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
using namespace std;

class Server {
private:
    static int load;
public:
    static int compute(long long A, long long B) {
        load += 1;
        if(A < 0) {
            throw std::invalid_argument("A is negative");
        }
        vector<int> v(A, 0);
        int real = -1, cmplx = sqrt(-1);
        if(B == 0) throw 0;
        real = (A/B)*real;
        int ans = v.at(B);
        return real + A - B*ans;
    }
    static int getLoad() {
        return load;
    }
};
int Server::load = 0;

int main() {
    int T; cin >> T;
    while(T--) {
        long long A, B;
        cin >> A >> B;

        /* Compute puede tener una exception, asi que se pone dentro del try, y si esta dentro del try podemos cacharlo y procesarlo como queremos.
           Si hay un throw fuera del try entonces por defecto, el programa se detendra.*/
        try
        {
            Server s;
            cout<<s.compute(A,B)<<endl;;
        }
        /* Estos son catch de los diferentes tipos de errores que podenmos tener.*/
        catch (std::bad_alloc& e)
        {
            cout<<"Not enough memory"<<endl;
        }
        catch (std::exception& e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }
        /* Este es el catch por defecto para cualquier otra exception que se haya disparado dentro del try.*/
        catch(int e)
        {
            cout<<"Other Exception"<<endl;
        }

    }
    cout << Server::getLoad() << endl;
    return 0;
}

```

* Que es una exception?
    * Condiciones responsables que crean errores durante la ejecucion del programa que el software no sabe como resolver en la parte que corre.
* Explica exception synch y exception asynch.
    * Exceptiones sincronizados son disparados por un statement throw.
    * Excepciones asincronizacos son errores que no son controlados por el software.

* **Try** statement define codigo que son probados por errores mientras se ejecutan (se espera un throw).
* **throw** statement es disparado cuando se encuentra un error, que nos deja actuar sobre el.
* **catch** statement define el bloque de codigo que es ejecutado cuando un error especifico paso en try().

* Reglas
    * El catch puede ser ejecutado en diferentes maneras basado en el argumento thrown.
    * Puede haber diferentes catch() pero solo un try en un bloque de codigo.
    * Si throw pasa pero no hay catch para manejarlo, se llama terminate().

* unexpected() se llama cuando una excepcion pasa que no esta enlistado en las specs. unexpected() por default llama a terminate().

* Explica el concepto de rethrowing exceptions.
    * Un rethrowing exception es cuando hacemos un throw desde un catch para que otro catch lo maneje.

```
#include <iostream>
using namespace std;

void help()
{
	try {
		throw 10;
	}
	catch (...) {
		cout << "First throw called\n";
		throw;
	}
}

int main()
{

	try {
		help();
	}
	catch (...) {
		cout << "Rethrowing throw called\n";
	}

	return 0;
}
```

* Puedes usar catch(...) para cachar todas las exceptions que haya en un try.

```
#include <iostream>
using namespace std;

int main()
{
	try {
		throw 10;
	}
	/* Del try de arriba, no entrara porque no se puede intepretar el 10 como un char*.*/
	catch (char* excp) {
		cout << "Caught " << excp;
	}
	catch (...) {
		cout << "Default Exception\n";
	}
	return 0;
}
```

```
#include <iostream>
using namespace std;
int main()
{
	int x = -10;
	try {
        /* Primero*/
		cout << "Before Error\n";
		if (x < 0) {
            /* Segundo*/
			throw x;
			/* Este se omite porque el throw manda el control al catch directamente.*/
			cout << "After Error\n";
		}
	}
	catch (int x) {
        /* Tercero*/
		cout << "Exception Caught \n";
	}
	/* Cuarto, como no se llama terminate(), el control flow continua como deberia.*/
	cout << "After catch \n";
	return 0;
}

```
* Cuando el hay un throw de una clase derivada puede suceder esto:
```
#include<iostream>
using namespace std;

class Base {};
class Derived: public Base {};
int main()
{
Derived d;
try {
	throw d;
}
catch(Base b) {
        /* Debido a que la clase derivada tiene la parte de la clase base
         entonces el catch de la base siempre entrara antes de la de la clase derivada.*/
		cout<<"Caught Base Exception";
}
catch(Derived d) {
		cout<<"Caught Derived Exception";
}
return 0;
}
```

```
#include <iostream>
using namespace std;

int main()
{
	try {
		throw 10;
	}
	/* Este es por defecto, el programa pensara que no hay ningun otro catch y entrara a este automaticamente, asi este catch(...) debe de estar siempre al final.*/
	catch (...) {
		cout << "default exception \n";
	}
	catch (int param) {
		cout << "integer exception \n";
	}

	return 0;
}

```
* El catch(...) debe de ser el ultimo si no, no habra otro catch que va a poder entrar.


```
#include <iostream>
using namespace std;

int main()
{
	try {
		try {
			throw 10;
		}
		catch (int n) {
            /* Primero */
			cout << "Inner Catch\n";
			throw;
		}
	}
	catch (int x) {
        /* Segundo */
		cout << "Outer Catch\n";
	}
	return 0;
}

```

* Basado en el rethrowing, se puede anidar try clauses.

* Catch() solamente pueden tener un argumento que es la clase de exception que se manejara.
