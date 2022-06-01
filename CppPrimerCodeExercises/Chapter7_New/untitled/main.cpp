#include <iostream>
#include <string>

using namespace std;

void ComposedTypes()
{
    int i = 0;
    int& ref = i;

    int* pi = &i;

    cout<<pi<<endl;
    cout<<*pi<<endl;
    cout<<&pi<<endl;

    i = 2u;
    int j =3;
    int k =4;

    cout<<*pi<<endl;

    pi = nullptr;

    int** ppi = &pi;

    cout<<ppi<<endl;
    cout<<ppi[1]<<endl;
    cout<<ppi[2]<<endl;
    cout<<ref<<endl;
}

unsigned int absInt(int param)
{
    return abs(param);
}

//Write a function that returns 0 when it is first called and then
//generates numbers in sequence each time it is called again.
int incremental()
{
    static unsigned temp = 0;

    return temp++;
}

void reset(int& i)
{
    i = 0;
}

//Write a function to determine whether a string contains
//any capital letters.
bool hasCapitalLetters(const string& s)
{
    const unsigned int capitalLetterLowLimitRange = 40u;
    const unsigned int capitalLetterHighLimitRange = 91u;

    for(auto it = s.begin(); it != s.end(); ++it)
    {
        if((*it > capitalLetterLowLimitRange) && (*it < capitalLetterHighLimitRange))
        {
            return true;
        }
    }
    return false;
}

//Write a function to change a string to all lowercase. Do
//the parameters you used in these functions have the same type? If so, why?
//If not, why not?
void lowCaseChange(string& s)
{
    const unsigned int capitalLetterLowLimitRange = 0x40u;
    const unsigned int capitalLetterHighLimitRange = 0x5Au;
    const unsigned int asciiRangeLowCase = 0x20u;

    for(auto it = s.begin(); it != s.end(); ++it)
    {
        if((*it > capitalLetterLowLimitRange) && (*it < capitalLetterHighLimitRange))
        {
            *it += asciiRangeLowCase;
        }
    }
}

//Write a function that takes an int and a pointer to an int
//and returns the larger of the int value or the value to which the pointer
//points. What type should you use for the pointer
int compareIntPointerInt(const int i, const int* pi)
{
   return (i>*pi)?i:*pi;
}

void swap(int* pa,int* pb)
{
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void swapPointers(int* &pa, int* &pb)
{
    int* tempP = pa;
    pa = pb;
    pb = tempP;
}

int main()
{

    //ComposedTypes();
    /* Absolute value from parameter*/
    //cout<<absInt(-10)<<endl;

    cout<< incremental() <<endl;
    cout<< incremental() <<endl;
    cout<< incremental() <<endl;
    cout<< incremental() <<endl;
    cout<< incremental() <<endl;

    int a =10;
    int b =20;

    int* pa = &a;
    int* pb = &b;

    cout<<*pa<<endl;
    cout<<*pb<<endl;

    swap(pa,pb);

    cout<<*pa<<endl;
    cout<<*pb<<endl;

    reset(a);

    cout<<*pa<<endl;
    cout<<*pb<<endl;

    cout<<pa<<endl;
    cout<<pb<<endl;

    swapPointers(pa,pb);

    cout<<pa<<endl;
    cout<<pb<<endl;

    string s = "I Have Capitals";
    cout<<"S has capitals? "<< hasCapitalLetters(s) <<endl;

    lowCaseChange(s);

    cout<<"S has capitals after lowCaseChange()? "<< hasCapitalLetters(s) <<endl;

    cout<<compareIntPointerInt(a,pb)<<endl;

    unsigned int (*pf)(int param);

    pf = &absInt;

    cout<<pf(-20)<<endl;


    return 0;
}
