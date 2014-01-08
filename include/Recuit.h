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
#include <utility>

using namespace std;

class Recuit
{
    public:
        Recuit();
        Recuit(Problem* p);
		void swp(int i, int j);
		double cost();
		void recuit(double tau0, int sizelist);
        virtual ~Recuit();
        void drawSol(char* filename);
    protected:
    private:
        double getInitialTemp(double tau0);
        void descente(double& best_cost,
                      std::default_random_engine generator,
                      std::uniform_int_distribution<int> distrib,
                      std::vector<std::pair<unsigned int, unsigned int> > listetabou,
                      double& T);
        void initializeLink();
        Problem* prob;
        std::vector<int> exit;
        std::vector<int> exitsol;
		vector<vector<int> > mat;
		vector<vector<int> > sol;

};

#endif // RECUIT_H
