/* 
 * File:   Statement.hpp
 * Author: augcampos
 *
 * Created on November 27, 2013, 10:47 PM
 */

#ifndef STATEMENT_HPP
#define	STATEMENT_HPP

#include <sqlite3.h>
#include <vector>
#include <memory>
#include "Database.hpp"
#include "Column.hpp"
#include "Row.hpp"

namespace sqlite {


    class Database; //forward declaration
    class Column; //forward declaration
    class Row; //forward declaration

    /**
     * Type for returning Columns
     * bool true is the columns is valid
     * Column reference to the column
     */
    typedef const std::tuple<bool, Column&> ReturnColumn_t;

    /**
     * Class Statement
     */
    class Statement {
        friend Column;
    public:

        /**
         * Enumerator class Status
         */
        enum class STATUS : short {
            UNDEFINED, CLOSED, PREPARED, EXECUTED, DONNE, ERROR
        };

        /**
         * Run Sql in db and return first column of the first row
         * @param db Database reference
         * @param sql Sql to execute
         * @return column of the first row value
         * @see ReturnColumn_t
         */
        static ReturnColumn_t Run(Database& db, std::string sql);

        /**
         * Constructor
         * @param db Database reference 
         * @param sql string to execute
         * @param auto_prepare prepare statement on creation
         */
        Statement(Database& db, std::string sql, bool auto_prepare = false);

        /**
         * Destructor
         */
        virtual ~Statement();

        /**
         * Prepare the Sql Statement
         * @return Sqlite int code return
         */
        int prepare();

        /**
         * Step to next row (if exists)
         * @return true id success
         */
        bool step();

        /**
         * Resets the statement
         */
        bool reset();

        /**
         * Check if the statement is prepared
         * @return True is prepared
         */
        bool isPrepared() const;

        /**
         * Check if the statement was executed
         * @return True if was executed
         */
        bool isExecuted() const;

        /**
         * Execute the statement
         * @return  Return the number of rows modified by those SQL statements (INSERT, UPDATE or DELETE only) 
         */
        int exec();

        /**
         * Execute state get first column int he fist row
         * @return  column of the first row value
         * @see ReturnColumn_t
         */
        ReturnColumn_t execValue();

        /**
         * GEt the number of columns returned by this statement
         * @return number of columns
         */
        int getColumnCount();

        /**
         * Get the Vector with all columns
         * @return vector
         */
        const std::vector<Column>& getColumns();

        /**
         * Get column reference 
         * @param index of the column
         * @return Column reference
         */
        Column& getColumn(int index);

        /**
         * Get column reference 
         * @param columnName of the column
         * @return Column reference
         */
        Column& getColumn(const std::string& columnName);

        /**
         * Get current row reference
         * @return Row reference
         */
        const Row& getRow();

        /**
         * Bind Integer Value
         * @param idx marker index
         * @param value 
         */
        void bind(int idx, int value);

        /**
         * Bind Double Value
         * @param idx marker index
         * @param value 
         */
        void bind(int idx, double value);

        /**
         * Bind Long Long Value
         * @param idx marker index
         * @param value 
         */
        void bind(int idx, long long int value);

        /**
         * Bind String Value
         * @param idx marker index
         * @param value
         * @param fstatic true for STATIC; false for TRANSIENT 
         */
        void bind(int idx, const std::string& value, bool fstatic = false);

        /**
         * Bind Blob void* Value
         * @param idx marker index
         * @param value 
         * @param n Size in bytes of value
         * @param fstatic true for STATIC; false for TRANSIENT 
         */
        void bind(int idx, const void* value, int n, bool fstatic);

        /**
         * Bind NULL Value
         * @param idx marker index
         */
        void bind(int idx);
        
        /**
         * Bind Integer Value
         * @param name of the column
         * @param value
         */
        void bind(const char* name, int value);
        
        /**
         * Bind Double Value
         * @param name of the column
         * @param value
         */
        void bind(char const* name, double value);
        
        /**
         * Bind Long Long Value
         * @param name of the column
         * @param value
         */
        void bind(char const* name, long long int value);
       
        /**
         * Bind String Value
         * @param name of the column
         * @param value
         * @param n Size in bytes of value
         * @param fstatic true for STATIC; false for TRANSIENT 
         */
        void bind(char const* name, const std::string& value, bool fstatic = false);
        
        /**
         * Bind Blob void* Value
         * @param name of the column
         * @param value
         * @param n Size in bytes of value
         * @param fstatic true for STATIC; false for TRANSIENT 
         */
        void bind(char const* name, const void* value, int n, bool fstatic = false);
        
        /**
         * Bind NULL Value
         * @param name of the column
         */
        void bind(char const* name);

    protected:
        typedef std::unique_ptr<sqlite3_stmt, std::function<void (sqlite3_stmt*)> >sqlite_stmt_ptr_t;
        sqlite_stmt_ptr_t statement;
        Database& m_db;
        std::string m_sql;
        STATUS m_status;
        std::vector<Column> m_columns;

        void check(const int aRet) const;
        int getParameterIndex(const char* name);
    };

}
#endif	/* STATEMENT_HPP */

