/*
 * File:   Transaction.cpp
 * Author: augcampos
 *
 * Created on November 27, 2013, 10:46 PM
 */

#include <sqlite3.h>
#include "sqlite3-cpp/Transaction.hpp"

namespace sqlite {

    Transaction::Transaction(Database& db, bool force_commit, bool force_reserve) : m_db(db), m_force_commit(force_commit) {
        if (m_db.execute(force_reserve ? "BEGIN IMMEDIATE" : "BEGIN") != SQLITE_OK) {
            throw Exception(m_db);
        }

        m_commited = false;
    }

    Transaction::~Transaction() {
        if (m_db.m_database && (false == m_commited)) {
            m_force_commit ? commit() : rollback();
        }
    }

    void Transaction::commit() {
        if (false == m_commited) {
            if (m_db.execute("COMMIT") != SQLITE_OK) {
                throw Exception(m_db);
            }
        }
    }

    void Transaction::rollback() {
        if (false == m_commited) {
            if (m_db.execute("ROLLBACK") != SQLITE_OK) {
                throw Exception(m_db);
            }
        }
    }
}
