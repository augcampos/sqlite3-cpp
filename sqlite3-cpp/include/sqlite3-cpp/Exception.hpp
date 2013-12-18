/*
 * File:   Exception.hpp
 * Author: augcampos
 *
 * Created on November 27, 2013, 10:52 PM
 */

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <cstddef>
#include <typeinfo>
#include <exception>
#include <stdexcept>
#include "Database.hpp"

namespace sqlite {

    /**
     * Class to handle the sqlite Sql Exceptions
     */
    class Exception : public std::runtime_error {
    public:
        /**
         * Constructor
         * @param msg String message
         */
        explicit Exception(char const *msg);
        
        /**
         * Constructor
         * @param db Database reference to discover the last error
         */
        explicit Exception(Database& db);

        /**
         * Destructor
         */
        virtual ~Exception();

    private:
    };
}
#endif   /* EXCEPTION_HPP */

