//
// Created by ahmed on 07/12/2023.
//

#ifndef APC_BINARY_FILES_EXC_TEXTFILESERIALIZER_H
#define APC_BINARY_FILES_EXC_TEXTFILESERIALIZER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class TextFileSerializer {
public:
template <typename T>
static void Serialize(const std::vector<T> &data, const std::string &filename){
    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open())
        throw std::runtime_error("Error opening the file for writing");
    for (const auto &item: data)
        file << item << "\n";

    file.close();

    if (!file.good())
        throw std::invalid_argument("Error occurred in the writing time");
}

template<typename T>
static std::vector<T> Deserialize(const std::string& filename, const ifactory<T> factory){
    std::vector<T> data{};
    std::ifstream file{filename};

    if (!file)
        throw std::runtime_error("Error opening the file for reading");

    T* item{};
    
std::string line;
    while (std::getline(file , line))
        data.push_back(factory.construct_from_string(line));

    file.close();
    if(!file.good())
        throw std::runtime_error("Error occurred in reading the file");

    return data;
}

};


#endif //APC_BINARY_FILES_EXC_TEXTFILESERIALIZER_H
