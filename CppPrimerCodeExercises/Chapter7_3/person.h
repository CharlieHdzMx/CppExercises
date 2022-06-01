#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <istream>
#include <ostream>

using namespace std;

string Nationality_Code= "Iran";

class Person
{
private:
    string name;
    string address;
    /*Asociation with all the Persons and not with an instance*/
    static string Nationality_Code;
public:
    /*Avoid implicit conversion from other types rather than Person.*/
    explicit Person(string n);
    Person();
    Person(string n, string a);
    inline string getName()const{ return name;}
    inline string getAddress()const{return address;}
    inline void setName(string s){name =s;}
    inline void setAddress(string s){address =s;}
    /*Can access private members*/
    static inline string getNationality_Code(){return Nationality_Code;}
};

istream &readPerson(istream &is, Person& person);
ostream &printPerson(ostream &os, Person& person);


#endif // PERSON_H
