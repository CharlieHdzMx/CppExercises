#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

//Write a function that takes a pair of iterators to a
//vector<int> and an int value. Look for that value in the range and return
//a bool indicating whether it was found.
bool foundValue(vector<int>::iterator itBegin,vector<int>::iterator itEnd, int value)
{
    while(itBegin != itEnd)
    {
        if(*itBegin == value)
            return true;
        itBegin++;
    }
    return false;
}

int main()
{
    cout << "Hello World!" << endl;
    vector<int> v{0,1,2,3,4,5,6,7,8,9,10};

    cout<<foundValue(v.begin(),v.end(), 10);

    return 0;
}
