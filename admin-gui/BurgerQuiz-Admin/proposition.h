#ifndef PROPOSITION_H
#define PROPOSITION_H


#include <stdlib.h>
#include <iostream>

#include <QtWidgets>

#include "dbconnection.h"

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

    void disable();
    void remove();
    void updateLibelleProposition(string libelleProposition);
    void updateReponseProposition(int reponseProposition);
    void enable();

private:
    int id;
    string libelleProposition;
    int reponseProposition;
    int active;
};

#endif // PROPOSITION_H
