/*
 * File:   Query.cpp
 * Author: augcampos
 *
 * Created on December 6, 2013, 2:46 PM
 */

#include "sqlite3-cpp/Query.hpp"

namespace sqlite {

    Query::Query(Database & db, std::string sql, bool auto_prepare) : Statement(db, sql, auto_prepare) {
    }

    Query::~Query() {
    }

    Query_Iterator Query::begin() {
        if (!isPrepared()) {
            prepare();
        }

        return Query_Iterator(this);
    }

    Query_Iterator Query::end() {
        return Query_Iterator(this);
    }

    Query_Iterator::Query_Iterator(const Query * query) :    m_query(query),    m_pos(0) {
    }

    bool Query_Iterator::operator !=(const Query_Iterator & other) const {
        return ((m_query == other.m_query) && (m_query -> m_status != Statement::STATUS::DONNE));
    }

    const Row & Query_Iterator::operator *() const {
        return ((Statement *) m_query) -> getRow();
    }

    const Query_Iterator & Query_Iterator::operator ++() {
        m_pos++;
        ((Statement *) m_query) -> step();

        return *this;
    }
}
