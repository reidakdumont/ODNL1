#ifndef PARSER_HH
#define PARSER_HH

#include "Problem.hh"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iostream>

class Parser
{
    public:
        Parser();
        virtual ~Parser();
        void parse(char* filename);
    protected:
    private:
        Problem prob_;
};

#endif // PARSER_HH
