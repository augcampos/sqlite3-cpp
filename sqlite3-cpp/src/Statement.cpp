/* 
 * File:   Statement.cpp
 * Author: a-campos
 * 
 * Created on November 27, 2013, 10:47 PM
 */

#include <sqlite3.h>
#include <algorithm> 
#include "sqlite3-cpp/Statement.hpp"

namespace sqlite {

    ReturnColumn_t Statement::Run(Database& db, std::string sql) {
        Statement st(db, sql);
        return st.execValue();
    }

    Statement::Statement(Database& db, std::string sql, bool auto_prepare) : m_db(db), m_sql(sql), m_status(STATUS::CLOSED) {
        if (auto_prepare) {
            prepare();
        }
    }

    Statement::~Statement() {
        if (statement) {
            statement = NULL;
            m_status = STATUS::UNDEFINED;
            m_columns.clear();
        }
    }

    int Statement::prepare() {
        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(
                m_db.m_database.get(),
                m_sql.c_str(),
                static_cast<int> (m_sql.size()),
                &stmt,
                NULL);

        check(rc);

        auto stmtdeleter = [](sqlite3_stmt * stmt_del) {
            if (stmt_del != NULL)
                sqlite3_finalize(stmt_del);
        };
        statement = sqlite_stmt_ptr_t(stmt, stmtdeleter);

        m_columns.clear();
        for (int i = 0; i < sqlite3_column_count(statement.get()); i++) {
            m_columns.push_back(
                    Column(*this, i)
                    );
        }

        m_status = STATUS::PREPARED;
        return rc;
    }

    bool Statement::reset() {
        int rc = sqlite3_reset(statement.get());
        if (rc == SQLITE_OK)
            m_status = STATUS::PREPARED;
        return rc == SQLITE_OK;
    }

    bool Statement::isPrepared() const {
        return (m_status >= STATUS::PREPARED);
    }

    bool Statement::isExecuted() const {
        return (m_status == STATUS::EXECUTED);
    }

    bool Statement::step() {
        int ret = (!isPrepared()) ? prepare() : sqlite3_step(statement.get());
        if (SQLITE_DONE == ret) // the statement has finished executing successfully
        {
            m_status = STATUS::DONNE;
        } else if (SQLITE_ROW == ret) {
            m_status = STATUS::EXECUTED;
        } else {
            int err = sqlite3_errcode(m_db.m_database.get());
            if (err > 0) {
                m_status = STATUS::ERROR;
                throw Exception(m_db);
            } else {
                m_status = STATUS::DONNE;
            }

        }

        return isExecuted();
    }

    int Statement::exec() {
        step();
        return sqlite3_changes(m_db.m_database.get());
    }

    ReturnColumn_t Statement::execValue() {
        bool est = step();
        bool rt = true;
        if (!est) {
            if (m_status == STATUS::DONNE) {
                //throw Exception("NO rows returned!");
                rt = false;
            }
        }
        return ReturnColumn_t(rt, getColumn(0));
    }

    int Statement::getColumnCount() {
        if (!isPrepared())
            prepare();
        return m_columns.size();
    }

    const std::vector<Column>& Statement::getColumns() {
        if (!isPrepared())
            prepare();

        return m_columns;
    }

    const Row& Statement::getRow() {
        return (const Row&) m_columns;
    }

    Column& Statement::getColumn(int index) {
        if (!isPrepared())
            prepare();
        return m_columns[index];
    }

    Column& Statement::getColumn(const std::string& columnName) {
        auto rt = std::find_if(m_columns.begin(), m_columns.end(), [columnName](const Column & n) {
            return n.getName() == columnName;
        });

        return (*rt);
    }

    void Statement::bind(int idx, int value) {
        if (!isPrepared())
            prepare();
        int ret = sqlite3_bind_int(statement.get(), idx, value);
        check(ret);
    }

    void Statement::bind(int idx, double value) {
        if (!isPrepared())
            prepare();
        int ret = sqlite3_bind_double(statement.get(), idx, value);
        check(ret);
    }

    void Statement::bind(int idx, long long int value) {
        if (!isPrepared())
            prepare();
        int ret = sqlite3_bind_int64(statement.get(), idx, value);
        check(ret);
    }

    void Statement::bind(int idx, const std::string& value, bool fstatic) {
        if (!isPrepared())
            prepare();
        int ret = sqlite3_bind_text(statement.get(), idx, value.c_str(), value.size(), fstatic ? SQLITE_STATIC : SQLITE_TRANSIENT);
        check(ret);
    }

    void Statement::bind(int idx, const void* value, int n, bool fstatic) {
        if (!isPrepared())
            prepare();
        int ret = sqlite3_bind_blob(statement.get(), idx, value, n, fstatic ? SQLITE_STATIC : SQLITE_TRANSIENT);
        check(ret);
    }

    void Statement::bind(int idx) {
        if (!isPrepared())
            prepare();
        int ret = sqlite3_bind_null(statement.get(), idx);
        check(ret);
    }

    void Statement::bind(const char* name, int value) {
        int idx = getParameterIndex(name);
        return bind(idx, value);
    }

    void Statement::bind(char const* name, double value) {
        int idx = getParameterIndex(name);
        return bind(idx, value);
    }

    void Statement::bind(char const* name, long long int value) {
        if (!isPrepared())
            prepare();
        int idx = getParameterIndex(name);
        return bind(idx, value);
    }

    void Statement::bind(char const* name, const std::string& value, bool fstatic) {
        int idx = getParameterIndex(name);
        return bind(idx, value, fstatic);
    }

    void Statement::bind(char const* name, const void* value, int n, bool fstatic) {
        int idx = getParameterIndex(name);
        return bind(idx, value, n, fstatic);
    }

    void Statement::bind(char const* name) {
        int idx = getParameterIndex(name);
        return bind(idx);
    }

    void Statement::check(const int aRet) const { // throw(Exception)
        if (SQLITE_OK != aRet) {
            sqlite3_finalize(statement.get());
            throw Exception(m_db);
        }
    }

    int Statement::getParameterIndex(const char* name) {
        return sqlite3_bind_parameter_index(statement.get(), name);
    }

}