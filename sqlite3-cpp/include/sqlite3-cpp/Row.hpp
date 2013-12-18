/*
 * File:   Row.hpp
 * Author: augcampos
 *
 * Created on November 28, 2013, 1:12 AM
 */

#ifndef ROW_HPP
#define ROW_HPP

#include "Column.hpp"

namespace sqlite {
    class Column;

    /**
     * Class Row
     * @extends std::vector<Column>
     */
    class Row : public std::vector<Column> {
    public:
        /**
         * Destructor
         */
        virtual ~Row();

        /**
         * Get Columns by index
         * @param index of the column
         * @return Column reference
         */
        Column& getColumn(int index);
        
        /**
         * Get Column by name
         * @param columnName name if the column
         * @return Column reference
         */
        Column& getColumn(const std::string & columnName);
    };
}
#endif   /* ROW_HPP */
