#include "person.h"


Person::Person() :
        name{},
        age{},
        height{} {
}

void Person::serialize(Person &person, const std::string &filename) {
    std::ofstream outFile{filename, std::ios::binary};
    if (!outFile)
        throw std::invalid_argument("Error opening file for writing");

        auto nameSize = person.name.size();
        outFile.write(reinterpret_cast<const char *>(&nameSize), sizeof(size_t));
        outFile.write(person.name.c_str(), nameSize);

        outFile.write(reinterpret_cast<const char *>(&person.age), sizeof(int));
        outFile.write(reinterpret_cast<const char *>(&person.height), sizeof(double));

        outFile.close();
        if (!outFile.good())
            throw std::invalid_argument("Error occurred in the writing time");

}


void Person::deserialize(Person & person, const std::string& filename) {
    std::ifstream inFile{filename, std::ios::binary};
    if (!inFile)
        throw std::invalid_argument("error reading the file");
    // Read the name
    size_t nameSize{};
    inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
    auto nameBuffer = new char[nameSize];
    inFile.read(nameBuffer, nameSize);
    delete[] nameBuffer;

    // Read the age and the height
    inFile.read(reinterpret_cast<char*>(&person.age), sizeof(int));
    inFile.read(reinterpret_cast<char*> (&person.height), sizeof(double));

    inFile.close();

    if(!inFile.good())
        throw std::invalid_argument("error occurred in the reading time");


}


