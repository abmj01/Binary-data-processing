#include <iostream>
#include "person.h"

//// to display the hexadecimal value of a binary file "hexdump -C name_of_your_binary_file.bin" in linux


// Function to identify the endianness of a certain device
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


