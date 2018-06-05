#ifndef QUESTION_H
#define QUESTION_H

#include <stdlib.h>
#include <iostream>

using namespace std;

class Question
{
public:
    Question();
    int getId();
    int getActive();
    string getLibelle1();
    string getLibelle2();

    void setId(int id);
    void setActive(int active);
    void setLibelle1(string libelle1);
    void setLibelle2(string libelle2);

    //QVector<Propositions> getPropositions();

private:
    int id;
    string libelle1, libelle2;
    int active;
};

#endif // QUESTION_H
