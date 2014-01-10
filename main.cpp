#include <iostream>
#include "include/Parser.hh"
#include "include/Recuit.h"

using namespace std;

int main(int argc, char* argv[])
{
    Parser* p = new Parser();
    p->parse(argv[1]);
    Recuit* r = new Recuit(p->getProblem());
    r->recuit(0.5);
    r->drawSol(argv[2]);
    return 0;
}
