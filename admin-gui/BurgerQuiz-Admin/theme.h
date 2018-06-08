#ifndef THEME_H
#define THEME_H

#include <stdlib.h>
#include <iostream>
#include "dbconnection.h"
#include <QtWidgets>

using namespace std;

class Theme
{
public:
    Theme();

    int getId();
    string getLibelle();
    string getPhoto();

    void setId(int id);
    void setLibelle(string libelle);
    void setPhoto(string photo);

    void updateLibelle(string libelle);
    void updatePhoto(string photo);
    void remove();

private:
    int id;
    string libelle;
    string photo;
};

#endif // THEME_H
