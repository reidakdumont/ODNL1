#include <iostream>
#include "include/Parser.hh"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Parser* p = new Parser();
    p->parse("PB20x5_1.txt");
    return 0;
}
