#include <iostream>
#include <fstream>


struct Person{
    std::string name;
    int age;
    double height;

    Person();

    void serialize(Person & person, const std::string& filename);
    void deserialize(Person & person, const std::string& filename);

};