
# General
* getline(stream, string) lee una linea de entrada desde un dado istream dentro de un string. Se detiene cuando detecta un brinco de linea.
* No es valido copiar o asignar IO objetos
    * istream, entrada cin.
    * ostream, salida cout.
* s.clear() reset los valores de condiciones en el stream s para validar el estado. Return void.
* endl(), writes, newline and flush the buffer.
* flush(), writes, and flush, no agrega datos.
* ends(), write, null, flush.
* Tie, es attach un input stream y un output stream, asi que cualquier lectura de stream input va a limpiar el buffer con el stream output.
* Read(s,n), Copia un bloque de datos sin checar su contenido ni agregando ningun caracter null al final.
    * S es un puntero  donde se van a guardar los caracteres extraidos.
    * n es el numero de caracteres a extraer.
* get() lee un caracter del stream.

# File Input and Output
* ifstream, escribe en un archivo.
* ofstream, escribe en un archivo.
* fstrm.open(s, mode), abre el archivo s y lo junta con fstrm. El modo de archivo por defecto depende del tipo de fstream.
* fstrm.close() cierra el archivo.
* fstrm.is_open(), retorna boolean indicando si el archivo asociado esta abierto o no.
* Files mode
    * in Open for input.
    * out open for output, los datos ya agregados son tirados.
    * app, busca el final antes de cada escritura. Mantiene los datos.
    * ate, busca el final inmediatamente despues de abrir.
    * trunc, trunca el archivo.
    * binary, haz operaciones de IO en modo binario.

## String stream
* sstream define tres tipos para soportar IO en memoria. estos tipos de lectura o escritura de stringsson como IO stream.
* ostringstream es usado cuando quieres construir una salida de caracteres pero todavia no lo quieres imprimir.
