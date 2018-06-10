#ifndef USER_H
#define USER_H

#include <stdlib.h>
#include <iostream>
#include <QtWidgets>
#include "dbconnection.h"

using namespace std;

class User
{
public:
    User();

    int getId();
    string getUsername();
    string getPassword();
    int getAge();
    string getEmail();
    string getPhoto();

    void setId(int id);
    void setUsername(string username);
    void setPassword(string password, bool hashed = true);
    void setAge(int age);
    void setEmail(string email);
    void setPhoto(string photo);

    void updatePassword(string password);
    void updateAge(int age);
    void updateEmail(string email);
    void updatePhoto(string photo);

    void remove();

private:
    int id;
    string username;
    string password;
    int age;
    string email;
    string photo;
};

#endif // USER_H
