# Algoritmos
* iota() rellena un rango con incrementos secuenciales.
  * Primer y segundo, indican el rango a usar.
  * Tercer argumento indica que tanto se acumula, si es 1, se acumula 1++ por ejemplo.

### numeric_limits
* La clase template de numeric_limit provee una manera estandarizada para tener varias propiedades  de tipos aritmeticos.

``` cpp
#include <limits>
#include <iostream>


int main() 
{
    std::cout
        << "type\t│ lowest()\t│ min()\t\t│ max()\n"
        << "bool\t│ "
        << std::numeric_limits<bool>::lowest() << "\t\t│ "
        << std::numeric_limits<bool>::min() << "\t\t│ "
        << std::numeric_limits<bool>::max() << '\n'
        << "uchar\t│ "
        << +std::numeric_limits<unsigned char>::lowest() << "\t\t│ "
        << +std::numeric_limits<unsigned char>::min() << "\t\t│ "
        << +std::numeric_limits<unsigned char>::max() << '\n'
        << "int\t│ "
        << std::numeric_limits<int>::lowest() << "\t│ "
        << std::numeric_limits<int>::min() << "\t│ "
        << std::numeric_limits<int>::max() << '\n'
        << "float\t│ "
        << std::numeric_limits<float>::lowest() << "\t│ "
        << std::numeric_limits<float>::min() << "\t│ "
        << std::numeric_limits<float>::max() << '\n'
        << "double\t│ "
        << std::numeric_limits<double>::lowest() << "\t│ "
        << std::numeric_limits<double>::min() << "\t│ "
        << std::numeric_limits<double>::max() << '\n';
}
```
