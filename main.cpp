#include <iostream>
#include "include/Parser.hh"
#include "include/Recuit.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Parser* p = new Parser();
    p->parse("PB50x10_1.txt");
    Recuit* r = new Recuit(p->getProblem());
    r->recuit(10);
    return 0;
}
