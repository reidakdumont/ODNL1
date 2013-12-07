#include "../include/Parser.hh"

Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}

std::vector<int> split(std::string &s, char delim)
{
    std::vector<int> elems;
    std::string temp = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s.at(i) == delim)
        {
            if (temp.size() != 0)
                elems.push_back(atoi(temp.c_str()));
            temp = "";
        }
        else
        {
            temp.push_back(s.at(i));
        }
    }
    if (temp.size() != 0)
        elems.push_back(atoi(temp.c_str()));
    return elems;
}

std::vector<std::vector<int> > changeOrient(std::vector<std::vector<int> > orig)
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

void Parser::parse(char* filename)
{
    std::ifstream fichier(filename, std::ios::in);  // on ouvre en lecture
    Problem* p = new Problem();
    std::vector<std::vector<int> > temprob;
    if(fichier)  // si l'ouverture a fonctionné
    {
        int compteur = 0;
        std::string ligne;  // déclaration d'une chaîne qui contiendra la ligne lue
        while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        {
            compteur++;
            if (compteur > 3 && ligne.size() > 0)
            {
                std::vector<int> vect = split(ligne,' ');
                temprob.push_back(vect);
            }
        }
        p->setData(changeOrient(temprob));
        fichier.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    p->print();
}
