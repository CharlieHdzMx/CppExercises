#include "person.h"

istream& read(istream& is,Person& rhs){
    string name,address;
    is>>name>>address;
    rhs.setName(name);
    rhs.setAddress(address);
    return is;
}

ostream& print(ostream& os,const Person& rhs){
    os<<rhs.getName()<<rhs.getAddress()<<endl;
    return os;
}
