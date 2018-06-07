#include "proposition.h"

Proposition::Proposition()
{

}

int Proposition::getId()
{
    return this->id;
}

string Proposition::getLibelleProposition()
{
    return this->libelleProposition;
}

int Proposition::getReponseProposition()
{
    return this->reponseProposition;
}

int Proposition::getActive()
{
    return this->active;
}

void Proposition::setId(int id)
{
    this->id = id;
}

void Proposition::setLibelleProposition(string libelleProposition)
{
    this->libelleProposition = libelleProposition;
}

void Proposition::setReponseProposition(int reponseProposition)
{
    this->reponseProposition = reponseProposition;
}

void Proposition::setActive(int active)
{
    this->active = active;
}
