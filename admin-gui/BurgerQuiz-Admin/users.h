#ifndef USERS_H
#define USERS_H

#include <QVector>
#include "user.h"
#include <QtWidgets>
#include "dbconnection.h"

class Users
{
public:
    Users();

    QVector<User> fetchUsers();
    void createUser(User &user);
};

#endif // USERS_H
