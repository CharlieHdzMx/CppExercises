#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Write a function that takes and returns an istream&. The
//function should read the stream until it hits end-of-file. The function should
//print what it reads to the standard output. Reset the stream so that it is valid
//before returning the stream.
istream& readNPrint(istream& is)
{
    string buffer = "";
    while((is>>buffer) && (!is.eof()))
    {
        cout<<buffer<<ends;
    }
    return is;
}

//Write a function to open a file for input and read its contents
//into a vector of strings, storing each line as a separate element in the
//vector
vector<string> readFileToVector(string fileName)
{
    std::ifstream inFile(fileName,ios_base::in);
    vector<string> vString;
    string buffer = "";

    vString.clear();

    if(inFile)
    {
        while(inFile.good())
        {
            getline(inFile,buffer,'\n');
            vString.push_back(buffer);
        }
    }
    return vString;
}

vector<string> readFileToVectorWord(string fileName)
{
    std::ifstream inFile(fileName,ios_base::in);
    vector<string> vString;
    string buffer = "";

    vString.clear();

    if(inFile)
    {
        while(inFile.good())
        {
            getline(inFile,buffer,' ');
            vString.push_back(buffer);
        }
    }
    return vString;
}

//Exercise 8.10: Write a program to store each line from a file in a
//vector<string>. Now use an istringstream to read each element from
//the vector a word at a time.
void separateVectorToString(vector<string> v)
{
    string name = "";

    for(const string& s:v)
    {
        istringstream is(s);
        is>>name;
        cout<<name<<endl;
    }
}

int main()
{
    vector<string> vString;
//    istream& is = readNPrint(cin);
    cout << "Hello World!" << endl;

    vString = readFileToVector("file.txt");
    separateVectorToString(vString);

    return 0;
}
