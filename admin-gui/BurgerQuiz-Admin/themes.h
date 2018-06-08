#ifndef THEMES_H
#define THEMES_H

#include "dbconnection.h"
#include "theme.h"
#include <QVector>
#include <QtWidgets>

class Themes
{
public:
    Themes();

    QVector<Theme> fetchThemes();
    void createTheme(Theme &theme);
};

#endif // THEMES_H
