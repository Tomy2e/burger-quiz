#include "question.h"

Question::Question()
{

}


int Question::getId()
{
    return this->id;
}

int Question::getActive()
{
    return this->active;
}

string Question::getLibelle1()
{
    return this->libelle1;
}

string Question::getLibelle2()
{
    return this->libelle2;
}

void Question::setId(int id)
{
    this->id = id;
}

void Question::setActive(int active)
{
    this->active = active;
}

void Question::setLibelle1(string libelle1)
{
    this->libelle1 = libelle1;
}

void Question::setLibelle2(string libelle2)
{
    this->libelle2 = libelle2;
}
