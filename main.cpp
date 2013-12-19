#include <iostream>
#include "include/Parser.hh"
#include "include/Recuit.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Parser* p = new Parser();
    p->parse("PB100x10_1.txt");
    Recuit* r = new Recuit(p->getProblem());
    r->recuit(0.5);
    r->drawSol("test.txt");
    return 0;
}
