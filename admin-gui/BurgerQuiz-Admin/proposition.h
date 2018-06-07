#ifndef PROPOSITION_H
#define PROPOSITION_H


#include <stdlib.h>
#include <iostream>

using namespace std;

class Proposition
{
public:
    Proposition();
    int getId();
    string getLibelleProposition();
    int getReponseProposition();
    int getActive();

    void setId(int id);
    void setLibelleProposition(string libelleProposition);
    void setReponseProposition(int reponseProposition);
    void setActive(int active);

private:
    int id;
    string libelleProposition;
    int reponseProposition;
    int active;
};

#endif // PROPOSITION_H
