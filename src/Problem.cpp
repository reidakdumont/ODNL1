#include "../include/Problem.hh"

Problem::Problem()
{
    //ctor
}

Problem::~Problem()
{
    //dtor
}

std::vector<std::vector<int> > Problem::getData()
{
    return this->data_;
}

void Problem::setData(std::vector<std::vector<int> > v)
{
    this->data_ = v;
}

void Problem::print()
{
    for (int i = 0; i < this->data_.size(); i++)
    {
        for (int j = 0; j < this->data_.at(i).size(); j++)
        {
            std::cout << this->data_.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}
