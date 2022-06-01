#include "person.h"

Person::Person(string s):name(s),address(s)
{

}

Person::Person():name("Default"),address("Default")
{
}

Person::Person(string n, string a):name(n),address(a)
{

}

istream &readPerson(istream &is, Person& person)
{
    string holder = "";

    is>>holder;
    person.setName(holder);

    is>>holder;
    person.setAddress(holder);

    return is;
}
ostream &printPerson(ostream &os, Person& person)
{
    os<<person.getName()<<endl;
    os<<person.getAddress()<<endl;

    return os;
}
