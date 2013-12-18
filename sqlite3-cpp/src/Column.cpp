/*
 * File:   Column.cpp
 * Author: a-campos
 *
 * Created on November 27, 2013, 11:03 PM
 */

#include "sqlite3-cpp/Column.hpp"

namespace sqlite {

    Column::Column(Statement& stm, int index) : m_Statement(stm), m_index(index) {
    }

    Column::~Column() {
    }

    std::string Column::getName() const throw () {
        return sqlite3_column_name(m_Statement.statement.get(), m_index);
    }

    std::string Column::getOriginName() const throw () {
        return sqlite3_column_origin_name(m_Statement.statement.get(), m_index);
    }

    ColumnType Column::getType(void) const throw () {
        return ColumnType(sqlite3_column_type(m_Statement.statement.get(), m_index));
    }

    std::string Column::getDecltype() const throw () {
        return sqlite3_column_decltype(m_Statement.statement.get(), m_index);
    }

    int Column::getBytes(void) const throw () {
        return sqlite3_column_bytes(m_Statement.statement.get(), m_index);
    }

    int Column::getValueInt() throw () {
        if (!m_Statement.isExecuted()) {
            m_Statement.step();
        }

        return sqlite3_column_int(m_Statement.statement.get(), m_index);
    }

    long long Column::getValueInt64() throw () {
        if (!m_Statement.isExecuted()) {
            m_Statement.step();
        }

        return sqlite3_column_int64(m_Statement.statement.get(), m_index);
    }

    double Column::getValueDouble() throw () {
        if (!m_Statement.isExecuted()) {
            m_Statement.step();
        }

        return sqlite3_column_double(m_Statement.statement.get(), m_index);
    }

    std::string Column::getValueText() throw () {
        if (!m_Statement.isExecuted()) {
            m_Statement.step();
        }

        if (m_Statement.isExecuted()) {
            const unsigned char * tmp = sqlite3_column_text(m_Statement.statement.get(), m_index);
            return std::string(reinterpret_cast<const char *> (tmp));
        }

        return "";
    }

    const void * Column::getValueBlob() throw () {
        if (!m_Statement.isExecuted()) {
            m_Statement.step();
        }

        return sqlite3_column_blob(m_Statement.statement.get(), m_index);
    }
}
