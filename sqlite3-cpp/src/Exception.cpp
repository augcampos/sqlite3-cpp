/*
 * File:   Exception.cpp
 * Author: augcampos
 *
 * Created on November 27, 2013, 10:52 PM
 */

#include <sqlite3.h>
#include "sqlite3-cpp/Exception.hpp"

namespace sqlite
{
    Exception::Exception(char const *msg):
        std::runtime_error(msg)
    {
    }

    Exception::Exception(Database & db):
        std::runtime_error(sqlite3_errmsg(db.m_database.get()))
    {
    }

    Exception::~Exception()
    {
    }
}
