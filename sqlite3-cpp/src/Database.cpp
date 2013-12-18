/* 
 * File:   Database.cpp
 * Author: a-campos
 * 
 * Created on November 27, 2013, 10:37 PM
 */
#include <iostream>

#include <sqlite3.h>
#include "sqlite3-cpp/Database.hpp"

using namespace std;

namespace sqlite {

    Database& Database::factory(const char* dbname) {
        return *(new Database(dbname));
    }

    Database::Database(const char* filename) : m_dbpath(filename) {
        m_database = NULL;
        open();
    }

    Database::~Database() {
        close();
    }

    bool Database::open() {
        sqlite3 *p;
        if (sqlite3_open(m_dbpath.c_str(), &p) != SQLITE_OK) {
            cout << "FAIL TO OPEN DB :" << m_dbpath << "ERROR: " << sqlite3_errmsg(p) << endl;
            return false;
        }
        cout << "OPEN DB :" << m_dbpath << endl;

        auto dbdeleter = [](sqlite3 * p_del) {
            if (p_del != NULL)
                sqlite3_close_v2(p_del);
        };
        m_database = sqlite_db_ptr_t(p, dbdeleter);

        return true;

    }

    bool Database::attach(char const* dbname, char const* name) {
        int ret = execf("ATTACH '%s' AS '%s'", dbname, name);
        return (ret == SQLITE_OK);
    }

    bool Database::detach(char const* name) {
        int ret = execf("DETACH '%s'", name);
        return (ret == SQLITE_OK);
    }

    void Database::close() {
        if (m_database) {
            m_database = NULL;
            cout << "CLOSE DB :" << m_dbpath << endl;
        }
    }

    int Database::execute(char const* sql) {
        int ret = exec(sql);
        if (ret != SQLITE_OK)
            throw Exception(*this);
        return sqlite3_changes(m_database.get());
    }

    int Database::executef(char const* sql, ...) {
        va_list ap;
        va_start(ap, sql);
        char *zSQL = sqlite3_vmprintf(sql, ap);
        int rv = execute(zSQL);
        va_end(ap);
        sqlite3_free(zSQL);

        return rv;
    }

    int Database::exec(char const* sql) {
        return sqlite3_exec(m_database.get(), sql, NULL, NULL, NULL);
    }

    int Database::execf(char const* sql, ...) {
        va_list ap;
        va_start(ap, sql);
        char *zSQL = sqlite3_vmprintf(sql, ap);
        int rv = exec(zSQL);
        va_end(ap);
        sqlite3_free(zSQL);

        return rv;
    }

}