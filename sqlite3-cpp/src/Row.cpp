/* 
 * File:   Row.cpp
 * Author: a-campos
 * 
 * Created on November 28, 2013, 1:12 AM
 */

#include <algorithm> 
#include "sqlite3-cpp/Row.hpp"


namespace sqlite {

    Row::~Row() {
    }

    Column& Row::getColumn(int index) {
        return at(index);
    }

    Column& Row::getColumn(const std::string & columnName) {
        auto rt = std::find_if(begin(), end(), [columnName](const Column & n) {
            return n.getName() == columnName;
        });

        return (*rt);
    }

}