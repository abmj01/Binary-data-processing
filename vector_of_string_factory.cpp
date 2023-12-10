//
// Created by ahmed on 08/12/2023.
//

#include "vector_of_string_factory.h"

template<typename T>
T vector_of_string_factory<T>::construct_from_string(const std::string& s){
    T result;
    size_t start = 0;
    size_t end = s.find(',');
    while (end != std::string::npos){
        result.push_back(s.substr(start, end - start));
        start = end + 1;
        end = s.find(',', start);
    }
    result.push_back(s.substr(start));

    return result;
}

template<typename T>
T vector_of_string_factory<T>::construct_from_stream(std::istream &is) {
    T result;
    std::string line;
    while(std::getline(is, line, ',')){
        result.push_back(line);
    }
    return result;
}