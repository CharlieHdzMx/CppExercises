#include "doggy.h"
#include <vector>
#include <iterator>

using namespace std;
Doggy::Doggy()
{

}

bool compare(Doggy& dog1, Doggy& dog2);
vector<int>::iterator change_val(int a, vector<int>::iterator it_a);
void changeArrat(int array[], int additionalValueWDefault = 20);
void changeTable(int array[][20], size_t sizeRow);
/* Syntax to return a Pointer To Array*/
int (*getPointerToArray())[20];
bool getResult(int (*a)[20] = getPointerToArray());

