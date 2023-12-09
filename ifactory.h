//
// Created by ahmed on 08/12/2023.
//

#ifndef APC_BINARY_FILES_EXC_IFACTORY_H
#define APC_BINARY_FILES_EXC_IFACTORY_H
#include <iostream>
#include <vector>

template<typename T>
struct ifactory {
public:
    virtual T construct_from_string(const std::string& s) = 0;
    virtual T construct_from_stream( std::istream & is) = 0;
    virtual ~ifactory() = default;
};

// generic
#endif //APC_BINARY_FILES_EXC_IFACTORY_H
