#include <iostream>
#include "student.h"
#include <fstream>
#include "person.h"

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

int main(){
    Person Ahmed;
    Ahmed.name = "Ahmed Al-Ganad";
    Ahmed.age = 22;
    Ahmed.height = 175.4;

    Ahmed.serialize(Ahmed, "person.bin");
   std::cout << sizeof(Ahmed) << std::endl;

    Person loadedPerson;
    loadedPerson.deserialize(loadedPerson, "person.bin");

    std::cout << "Loaded Person: " << loadedPerson.name << ", " << loadedPerson.age << " years old, "
    << loadedPerson.height << "m tall" <<std::endl;

}

