    * alignof(), retorna el mayor power de 2 con la que puedas alinear algo.
        * cout << "Alignment of char: " << alignof(char) << endl;
            * Alignment of char: 1
    * alignas(), forza el alignment de un tipo haca una instancia.
        * alignas(16) int a[4]; printf("%p\n", a);
            * 0xbfa493e0
        * alignas(1024) int b[4]; printf("%p", b);
            * 0xbfa49000
  * unique_ptr<>::reset destruye un objeto actualmente manejado por un unique_ptr (si hay alguno) y toma ownership de p.

