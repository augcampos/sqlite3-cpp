/* 
 * File:   Database.hpp
 * Author: a-campos
 *
 * Created on November 27, 2013, 10:37 PM
 */

#ifndef DATABASE_HPP
#define	DATABASE_HPP

#include <memory>
#include <vector>
#include <string>
#include "Transaction.hpp"
#include "Statement.hpp"
#include "Column.hpp"
#include "Exception.hpp"

namespace sqlite {

    /**
     * Class to handle the sqlite database
     */
    class Database {
        friend class Transaction;
        friend class Statement;
        friend class Exception;

    public:
        /**
         * Sqlite Database Factory creator
         * @param dbname path of sqlite database file
         * @return reference to a Sqlite Database object
         */
        static Database& factory(const char* dbname);

        /**
         * Database base contructor
         */
        Database();

        /**
         * Database copy constructor
         * @param orig
         */
        Database(const Database& orig);

        /**
         * Database constructor
         * @param filename path to sqlite database file
         */
        Database(const char* filename);

        /**
         * Database destructor
         */
        virtual ~Database();

        /**
         * Execute Sql on the database
         * @param sql to execute on the database
         * @return Number of records that has changed
         */
        int execute(char const* sql);

        /**
         * Execute formated sql on the database
         * @param sql formated sql string
         * @param ... Parameters list
         * @return  Number of records that has changed
         * @example executef("SELELCT * FROM users WHERE id > %d",21);
         */
        int executef(char const* sql, ...);

        /**
         * Opens the database 
         * @return true if process goes as expected
         */
        bool open();

        /**
         * Attache a new database
         * @param dbname new database file to attach
         * @param name of the new database
         * @return true if process goes as expected 
         */
        bool attach(char const* dbname, char const* name);

        /**
         * Detach a attached database 
         * @param name on the the attached database to detach
         * @return true if process goes as expected
         */
        bool detach(char const* name);

        /**
         * Close a open database
         */
        void close();
    private:
        typedef std::unique_ptr<sqlite3, std::function<void (sqlite3*)> >sqlite_db_ptr_t;
        sqlite_db_ptr_t m_database;
        std::string m_dbpath;

        /**
         * Execute Sql on the database
         * @param sql to execute on the database
         * @return Sqlite Result Code
         */

        int exec(char const* sql);

        /**
         * Execute formated sql on the database
         * @param sql formated sql string
         * @param ... Parameters list
         * @return  Sqlite Result Code
         * @example executef("SELELCT * FROM users WHERE id > %d",21);
         */
        int execf(char const* sql, ...);
    };
}
#endif	/* DATABASE_HPP */

