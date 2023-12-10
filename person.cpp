#include "person.h"


Person::Person() :
        name_{},
        age_{},
        height_{} {
}



// ascci to binary
void Person::serialize(Person &person, const std::string &filename){
    std::ofstream outFile{filename, std::ios::binary};

    if (!outFile){
        throw std::invalid_argument("Error opening file for writing");
    }

        auto nameSize = person.name_.size();
        outFile.write(reinterpret_cast<const char *>(&nameSize), sizeof(size_t));
        outFile.write(person.name_.c_str(), nameSize);

        outFile.write(reinterpret_cast<const char *>(&person.age_), sizeof(int));
        outFile.write(reinterpret_cast<const char *>(&person.height_), sizeof(double));

        outFile.close();

        if (!outFile.good()){
            throw std::invalid_argument("Error occurred in the writing time");
        }
}

//binary to ascii
void Person::deserialize(Person & person, const std::string& filename) {
    std::ifstream inFile{filename, std::ios::binary};
    if (!inFile) {
        throw std::invalid_argument("error reading the file"); }

    // Read the name
    size_t nameSize{};
    inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));

    std::vector<char> nameBuffer(nameSize);
    inFile.read(nameBuffer.data(), nameSize);

    person.name_.assign(nameBuffer.data(), nameSize);

    // Read the age and the height
    inFile.read(reinterpret_cast<char*>(&person.age_), sizeof(int));
    inFile.read(reinterpret_cast<char*> (&person.height_), sizeof(double));

    inFile.close();

    if(!inFile.good())
        throw std::invalid_argument("error occurred in the reading time");
}


void Person::set_name(const std::string& name){
    name_ = name;
}
void Person::set_age(int age){
    age_ = age;
}
void Person::set_height(float height){
    height_ = height;
}


const std::string& Person::name() const{
    return name_;
}
double Person::height() const{
    return height_;
}
int Person::age() const{
    return age_;
}