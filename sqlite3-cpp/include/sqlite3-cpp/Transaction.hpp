/*
 * File:   Transaction.hpp
 * Author: a-campos
 *
 * Created on November 27, 2013, 10:46 PM
 */

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "Database.hpp"

namespace sqlite {
    class Database;

    /**
     * Class to handle the sqlite transactions
     */
    class Transaction {
        /**
         * Constructor
         * @param db Database reference
         * @param force_commit Force commit on object destruction
         * @param force_reserve set to true to use BEGIN IMMEDIATE
         * @note On creation the transaction starts
         */
        explicit Transaction(Database& db, bool force_commit, bool force_reserve);
        virtual ~Transaction();

        /**
         * Commits the transaction
         */
        void commit();

        /**
         * Rollback the transaction
         */
        void rollback();

    private:
        Database & m_db;
        bool m_force_commit;
        bool m_commited;
    };
}
#endif   /* TRANSACTION_HPP */
