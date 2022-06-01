#include <iostream>
#include "person.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Person p;
    Person* pp= new Person();

    printPerson(cout,p);
    readPerson(cin,p);
    printPerson(cout,p);


    printPerson(cout,*pp);
    readPerson(cin,*pp);
    printPerson(cout,*pp);

    return 0;
}
