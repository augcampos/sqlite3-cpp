/*
 * File:   Column.hpp
 * Author: a-campos
 *
 * Created on November 27, 2013, 11:03 PM
 */

#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <string>
#include "Statement.hpp"

namespace sqlite {
    class Statement;

    /**
     * Columns type class enumerator
     */
    enum class ColumnType {
        INTEGER = 1, FLOAT = 2, TEXT = 3, BLOB = 4, ISNULL = 5
    };

    /**
     * Class representative of sqlite column
     */
    class Column {
    public:
        /**
         * Constructor
         * @param stm Statement reference  
         * @param index Index if the column
         */
        Column(Statement& stm, int index);

        /**
         * Destructor
         */
        virtual ~Column();

        /**
         * Get the columns Name
         * @return column name
         */
        std::string getName(void) const throw ();

        /**
         * Get the column original name
         * @return the original nams
         * @example SELECT id as noteid FROM... getOriginName = "id";  getName() = "noteid"
         */
        std::string getOriginName(void) const throw ();

        /**
         * Get Column type
         * @return type on the column
         * @see ColumnType
         */
        ColumnType getType(void) const throw ();

        /**
         * Get the size in byte in the column
         * @return size in bytes
         */
        int getBytes(void) const throw ();

        /**
         * Get declared type
         * @return the string of the representation of type of the column
         */
        std::string getDecltype() const throw ();

        /**
         * Get value as Integer
         * @return value
         */
        int getValueInt(void) throw ();

        /**
         * Get value as Long Long
         * @return  value
         */
        long long getValueInt64(void) throw ();

        /**
         * Bet value as Double
         * @return value
         */
        double getValueDouble(void) throw ();

        /**
         * Get value as string/text
         * @return value
         */
        std::string getValueText(void) throw ();

        /**
         * Get Value as Blob
         * @return 
         */
        const void* getValueBlob(void) throw ();
    private:
        Statement& m_Statement;
        int m_index;
    };
}
#endif   /* COLUMN_HPP */

