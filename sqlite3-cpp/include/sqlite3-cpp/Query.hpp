/*
 * File:   Query.hpp
 * Author: augcampos
 *
 * Created on December 6, 2013, 2:46 PM
 */

#ifndef QUERY_HPP
#define QUERY_HPP

#include "Statement.hpp"

namespace sqlite {
    class Query;

    /**
     * Class for the Query row iterator
     */
    class Query_Iterator {
    public:
        /**
         * Constructor copy
         * @param p_vec Query_Iterator to be cloned
         */
        Query_Iterator(const Query* p_vec);

        /**
         * != Operator overload
         * @param other other Query_Iterator reference
         * @return true if not equal
         */
        bool operator !=(const Query_Iterator& other) const;

        /**
         * Dereference (*) operator overload
         * @return Current Row
         * @see Row
         */
        const Row & operator *() const;

        /**
         * Increment (++) operator overload
         * @return 
         */
        const Query_Iterator& operator ++();

        /**
         * Step 1 row
         * @return true if no error in the operation
         */
        bool step();

    private:
        int m_pos;
        const Query* m_query;
    };

    /**
     * Class for Query
     */
    class Query : public Statement {
        friend Query_Iterator;

    public:
        /**
         * Constructor
         * @param db Database reference
         * @param sql String to execute
         * @param auto_prepare prepare the state om creation
         */
        Query(Database& db, std::string sql, bool auto_prepare = false);

        /**
         * Destructor
         */
        virtual ~Query();

        /**
         * Method begin (used in for loops)
         * @return 
         */
        Query_Iterator begin();

        /**
         * Method end (used in for loops)
         * @return 
         */
        Query_Iterator end();

    private:
    };
}
#endif   /* QUERY_HPP */
