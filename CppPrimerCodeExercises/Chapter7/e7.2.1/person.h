#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

//Exercise 7.9: Add operations to read and print Person objects to the code
//you wrote for the exercises in § 7.1.2 (p. 260).

class Person{
    string name;
    string address;

public:
    Person()=default;
    Person(const string& n, const string& a):name(n),address(a){}
    string getName()const{return name;}
    string getAddress()const{return address;}
        void setName(string n){name=n;}
		void setAddress(string a){address=a;}
};

istream& read(istream& is,Person& rhs);
ostream& print(ostream& os,const Person& rhs);


#endif // PERSON_H
