#include <iostream>
#include "student.h"
#include <fstream>
#include "person.h"
#include <vector>

/*
int main() {
    const std::string &fname{"student.dot"};
    std::ofstream wf{fname, std::ios::out | std::ios::binary};
    if (!wf) {
        throw std::invalid_argument("cCannot open file");
    }
    Student wstu[3];
    wstu[0].roll_no = 1;
    wstu[0].name = "Ram";
    wstu[1].roll_no = 2;
    wstu[1].name = "Shyam";
    wstu[2].roll_no = 3;
    wstu[2].name = "Madhu";

    for (auto & i : wstu)
        wf.write((char *) &i, sizeof(Student));
    wf.close();

    if (!wf.good())
        throw std::invalid_argument("Error occurred at writing time!");

    std::ifstream rf(fname, std::ios::out | std::ios::binary);

    if (!rf)
        throw std::invalid_argument("Cannot open the input file stream");

    Student rstu[3];
    for (auto i{0}; i < 3; i++)
        rf.read((char *) &rstu[i], sizeof(Student));

    rf.close();
    if (!rf.good())
        throw std::invalid_argument("Error occurred at reading time");


    std::cout << "Student details:" << std::endl;
    for (auto i{0}; i < 3; i++) {
        std::cout << "Roll No: " << wstu[i].roll_no << std::endl;
        std::cout << "Name: " << wstu[i].name << std::endl;
        std::cout << std::endl;
    }


    return 0;
}
*/

//// to display the hexadecimal value of a binary file "hexdump -C name_of_your_binary_file.bin" in linux

void check_for_endianness()
{
    unsigned int x = 1;

    // Declare a pointer to a character and assign it the address of x.
    char *c = (char*) &x;

    // Return the integer value of the first byte pointed to by c.
    // If the architecture is little-endian, the value will be 1; otherwise, it will be 0.
    if ((int)*c == 1){
        std::cout << "This system is a Little endian" << std::endl;
    } else{
        std::cout << "This system is a Big endian" << std::endl;
    }
}

int main(){
    Person Ahmed;
    Ahmed.set_name("Ahmed Al-Ganad");
    Ahmed.set_age(22);
    Ahmed.set_height(175.67);

    Ahmed.serialize(Ahmed, "person7.bin");
   std::cout << sizeof(Ahmed) << std::endl;

    Person loadedPerson;
    loadedPerson.deserialize(loadedPerson, "person7.bin");

    std::cout << "Loaded Person: " << loadedPerson.name() << ", " << loadedPerson.age() << " years old, "
    << loadedPerson.height() << "m tall" <<std::endl;

    check_for_endianness();

}

/*#include "TextFileSerializer.h"
#include "vector_of_string_factory.h"

int main() {
    std::vector<std::string> originalData = {"Hello", "World", "Serialization", "Deserialization"};
    const std::string filename = "example.txt";

    TextFileSerializer::Serialize(originalData, filename);

    // Instantiate the factory
    vector_of_string_factory<std::vector<std::string>> factory;

    // Use the correct static call for Deserialize
    std::vector<std::string> loadedData = TextFileSerializer::Deserialize(filename, factory);

    for (const auto &item : loadedData) {
        std::cout << item << std::endl;
    }

    return 0;
}*/
