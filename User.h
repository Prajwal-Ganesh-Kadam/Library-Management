#pragma once

#include <iostream>
#include "Role.h"
using namespace std;

class User
{
    public : 
    int Id;
    string FirstName;
    string LastName;
    string UserName;
    Role Role;

    bool operator==(const User &user) const
    {
        if (UserName.compare(user.UserName) == 0)
            return true;
        else
            return false;
    }
};