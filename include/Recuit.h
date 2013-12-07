#ifndef RECUIT_H
#define RECUIT_H

#include "Problem.hh"

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Recuit
{
    public:
        Recuit();
        Recuit(Problem* p);
		void swp(int i, int j);
		double cost();
		void recuit(double tau0);
        virtual ~Recuit();
    protected:
    private:
        double getInitialTemp(double tau0);
        void initializeLink();
        Problem* prob;
		vector<vector<int> > mat;
		vector<vector<int> > sol;

};

#endif // RECUIT_H
