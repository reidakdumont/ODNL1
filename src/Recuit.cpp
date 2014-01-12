#include "../include/Recuit.h"

#define T_INIT 6666666
#define T_STEP 0.9
#define T_STOP 0.000000001

bool find(std::vector<int> vect, int f)
{
    for (unsigned int i = 0; i < vect.size(); i++)
        if (vect.at(i) == f)
            return true;
    return false;
}

Recuit::Recuit()
{
}

Recuit::Recuit(Problem* p)
{
    this->prob = p;
    this->mat = p->getData();
    for (int i = 0; i < this->mat.size(); i++)
        this->exit.push_back(i+1);
}

Recuit::~Recuit()
{
}

std::vector<std::vector<int> > changeOrientation(std::vector<std::vector<int> > orig)
{
    std::vector<std::vector<int> > res;
    for (int i = 0; i < orig.at(0).size(); i++)
    {
        std::vector<int> temp;
        for (int j = 0; j < orig.size(); j++)
        {
            temp.push_back(orig.at(j).at(i));
        }
        res.push_back(temp);
    }
    return res;
}

double max(double a, double b)
{
    if (a < b)
        return b;
    return a;
}

double Recuit::cost()
{
    std::vector<std::vector<int> > matrice;
    matrice = changeOrientation(this->mat);
    std::vector<std::vector<int> > res;
    std::vector<int> temp;
    temp.push_back(matrice.at(0).at(0));
    for (int j = 1; j < matrice.at(0).size(); j++)
    {
        int val = matrice.at(0).at(j) + temp.at(j-1);
        temp.push_back(val);
    }
    res.push_back(temp);
	for (int i = 1; i < matrice.size(); i++)
    {
        std::vector<int> temp;
        temp.push_back(res.at(i-1).at(0)+matrice.at(i).at(0));
        for (int j = 1; j < matrice.at(i).size(); j++)
        {
            int val = matrice.at(i).at(j) + max(temp.at(j-1),res.at(i-1).at(j));
            temp.push_back(val);
        }
        res.push_back(temp);
    }
    return res.at(res.size()-1).at(res.at(0).size()-1);
}
void Recuit::swp(int i, int j)
{
	std::vector<int> temp = this->mat.at(i);
	this->mat.at(i) = this->mat.at(j);
	this->mat.at(j) = temp;
	int temppos = this->exit.at(i);
	this->exit.at(i) = this->exit.at(j);
	this->exit.at(j) = temppos;
}

double Recuit::getInitialTemp(double tau0)
{
    double res = 0;
    int probsize = this->mat.size();
    std::uniform_int_distribution<int> distrib(0,probsize-1);
    std::default_random_engine generator;
    for (int i = 0; i < 4*probsize; i++)
    {
        int r1 = distrib(generator);
        int r2 = 0;
        do
        {
            r2 = distrib(generator);
        }
        while (r1 == r2) ;
        double firstcost = this->cost();
        this->swp(r1,r2);
        double secondcost = this->cost();
        res = res + abs(firstcost-secondcost);
    }
    res = res / (4*probsize);
    double T0 = - res / log(tau0);
    std::cout << "res = " << res << " , log = " << 100 * log(tau0) << std::endl;
    return T0;
}

double fact(double n)
{
    if (n <= 1)
        return 1;
    else
        return n * fact(n-1);
}

double combinatoire(double n, double h)
{
    double res = fact(n) / (fact(h)*fact(n-h));
    return res;
}

void Recuit::recuit(double tau0)
{
    double best_cost = 0;
    best_cost = this->cost();
    this->sol = this->mat;
    int probsize = this->mat.size();
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    std::uniform_int_distribution<int> distrib(0,probsize-1);
    double best_T = 0;
    bool changeInBest = false;
    std::vector<std::pair<unsigned int, unsigned int> > listetabou;
    double sizelist = combinatoire(probsize,2);
    std::uniform_int_distribution<int> dist(0,sizelist/2-1);
    time_t begintime = time(NULL);
    for(int h=0; h < 5; h++)
    //while (difftime(time(NULL), begintime) <= 900)
    {
        double T = getInitialTemp(tau0);
        std::cout << "T = " << T << std::endl;
        unsigned int t = 0, nbiter = 0 ;
        double cost_i, cost_j;
        int delta;
        unsigned int i, j;
        srand (time(NULL));
        bool cont = true;
        int accept = 0;
        int acceptdelta = 0;
        int palierSansAccept = 0;
        double rnd = 0;
        while (T > T_STOP && cont)
        {
            while (t != 100*probsize && (accept+acceptdelta) != 12*probsize && cont)
            {
                t++ ;
                nbiter++ ;
                //Compute inititial cost
                cost_i = cost();
                //Pick up two aleatory pieces
                do
                {
                    i = distrib(generator);
                    do
                    {
                        j = distrib(generator);
                    }
                    while (i == j) ;
                }while(std::find(listetabou.begin(), listetabou.end(), std::pair<unsigned int, unsigned int>(i,j)) != listetabou.end() && std::find(listetabou.begin(), listetabou.end(), std::pair<unsigned int, unsigned int>(j,i)) != listetabou.end());
                listetabou.push_back(std::pair<unsigned int, unsigned int>(i,j));
                if (listetabou.size() > sizelist/2)
                    listetabou.erase(listetabou.begin() + dist(generator));
                swp(i, j);
                //Compute new cost
                cost_j = cost();
                if (cost_j < best_cost)
                {
                    best_T = T;
                    best_cost = cost_j;
                    this->sol = this->mat;
                    this->exitsol = this->exit;
                    changeInBest = true;
                }
                // Back up best solution
                delta = cost_j - cost_i;
                if (delta < 0)
                {
                    //std::cout << "accept" << std::endl;
                    accept++; //Accept the swap
                    //std::cout << delta << " " << cost_j << " " << cost_i << " " << best_cost << " T = " << T << std::endl;
                }
                else if (delta > 0)
                {
                    double p = distribution(generator);
                    double e = exp(-delta / T);
                    rnd = rnd + e;
                    if (p < e)
                    {
                        //std::cout << "accept" << std::endl;
                        acceptdelta++; //Accept the swap
                        //std::cout << delta << " " << cost_j << " " << cost_i << " " << best_cost << " T = " << T << std::endl;
                    }
                    else
                        this->swp(i,j); //Refuse the swap, so we reput the last conﬁguration
                }
            }
            /*if (!changeInBest)
                descente(best_cost, generator, distrib, listetabou, T);*/
            std::cout << "T : " << T << " , t : " << t << " , nbiter : " << nbiter << " , accept : " << accept << " , acceptdelta : " << acceptdelta << " , moyrnd : " << rnd/(t-accept) << " , best_cost : " << best_cost << std::endl;
            changeInBest = false;
            if (accept+acceptdelta == 0)
                palierSansAccept++;
            else
                palierSansAccept = 0;
            T *= T_STEP ;
            t = 0 ;
            accept = 0;
            acceptdelta = 0;
            rnd = 0;
            if (palierSansAccept == 5)
                cont = false;
        }
        if (cont)
            std::cout << best_cost << " true" << std::endl;
        else
            std::cout << best_cost << " false" << std::endl;
    }
    this->mat = this->sol;
    this->exit = this->exitsol;
    this->prob->setData(this->mat);
}

void Recuit::descente(double& best_cost,
                      std::default_random_engine generator,
                      std::uniform_int_distribution<int> distrib,
                      std::vector<std::pair<unsigned int, unsigned int> > listetabou,
                      double& T)
{
    std::cout << "descente" << std::endl;
    unsigned int i,j;
    int probsize = this->mat.size();
    double sizelist = combinatoire(probsize,2);
    std::uniform_int_distribution<int> dist(0,sizelist/2-1);
    for (int h=0; h < probsize; h++)
    {
        double c = 0;
        double cost_j = 0;
        do
        {
            do
            {
                i = distrib(generator);
                do
                {
                    j = distrib(generator);
                }
                while (i == j) ;
            }while(std::find(listetabou.begin(), listetabou.end(), std::pair<unsigned int, unsigned int>(i,j)) != listetabou.end() && std::find(listetabou.begin(), listetabou.end(), std::pair<unsigned int, unsigned int>(i,j)) != listetabou.end());
            listetabou.push_back(std::pair<unsigned int, unsigned int>(i,j));
            if (listetabou.size() > sizelist/2)
                listetabou.erase(listetabou.begin() + dist(generator));
            swp(i, j);

            //Compute new cost
            cost_j = cost();
            c++;
            if (c >= sizelist)
                break;
            if (best_cost < cost_j)
                swp(i,j);
        }while (best_cost < cost_j);

        if (best_cost >= cost_j)
        {
            best_cost = cost_j;
            this->sol = this->mat;
            this->exitsol = this->exit;
        }
    }
}

void Recuit::drawSol(char* filename)
{
    std::ofstream fichier(filename, ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

    if(fichier)
    {
        for (int i = 0; i < this->exit.size(); i++)
            fichier << this->exit.at(i) << " ";
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}
