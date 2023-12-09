//
// Created by ahmed on 08/12/2023.
//

#ifndef APC_BINARY_FILES_EXC_VECTOR_OF_STRING_FACTORY_H
#define APC_BINARY_FILES_EXC_VECTOR_OF_STRING_FACTORY_H
#include "ifactory.h"

template<typename T>
class vector_of_string_factory : public ifactory<std::vector<std::string>> {
    T construct_from_string(const std::string& s) override;
    T construct_from_stream(std::istream & is) override;
};

#endif //APC_BINARY_FILES_EXC_VECTOR_OF_STRING_FACTORY_H
