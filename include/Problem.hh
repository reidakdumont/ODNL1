#ifndef PROBLEM_HH
#define PROBLEM_HH

#include <vector>
#include <iostream>

class Problem
{
    public:
        Problem();
        virtual ~Problem();
        std::vector<std::vector<int> > getData();
        void setData(std::vector<std::vector<int> >);
        void print();
    protected:
    private:
        std::vector<std::vector<int> > data_;
};

#endif // PROBLEM_HH
