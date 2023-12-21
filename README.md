# Binary data processing


Made by:
Ahmed Al-Ganad: ` 528820`
Saif Ba Madhaf: `527028`


In this project we will help you understand:
* What binary data processing mean?
* What is it used for?
* Why is it essential?
* How to implement a program in C++ that process data?
* * Serializing data.
* * Deserializing data.
* Explanation of the endianness concept.


### What is binary data processing?

Binary data processing is simply the act of encoding a data such as ASCII, Unicode, or UTF-8, ect. .
to binary format that the computer understand 1s and 0s. It also refers to the act of decoding that binary data to a legit data type.

### What is it used for?

Binary data processing is used for:
* File I/O Operation which is reading and writing binary files.
* Network communications which is transmitting data in binary form through computers.
* Data compression which is encoding data efficiently to store or transfer data.
* Data Encryption which is applying cryptographic algorithms to binary data.
* Low-Level System Operations or direct manipulation of hardware or system-level data.

There is more and more application of binary data processing, but we will suffice with that.

### Why is it essential?

I guess that the applications part somehow answered this question. However, Binary data processing is essential for the computers
to manipulate and represent data in low levels. It also is essential for storage, communication through network, and system-level operation.


### How to implement a program in C++ that process data?

#### We will start of with encoding or serializing files which is writing the data into binary format.

We will start of with a simple class called Person:

```cpp
class Person{
public:
    Person();
    //setters
    void set_name(const std::string & name);
    void set_age(int age);
    void set_height(float height);
    //getters
    const std::string& name() const;
    double height() const;
    int age() const;
private:
    std::string name_;
    int age_;
    double height_;
}
```

Nothing wierd a person has a name, an age, and a height. And a constructor `Person` to create an instance. And some setters and getters for the private members.

As you can see the name is a data type `string` ,  age `int`, and height `double`.

We will start of with a function that serializes or encodes the data to a binary file called 
`serialize`.

```c++
void serialize(Person & person, const std::string& filename);
```
The function does not return anything, it has two parameter a Person object passed by reference and a file name to create a
file to output the binary data.

Let's thrive into the function to help explain how to encode the data given.

```c++
std::ofstream outFile{filename, std::ios::binary};
```

First we initialize an output file stream [std::ofstream](https://en.cppreference.com/w/cpp/io/basic_ofstream/basic_ofstream). `std::ios::binary` sets a flag that
the file should be treated as a binary file. It is a mode that specifies that the data writen or read
is in raw binary format.

```c++
 if (!outFile){
        throw std::invalid_argument("Error opening file for writing");
    }
```

We proceed to check if everything is going alright with the file creation. If not we throw to stop the program and
we add an argument `"Error opening file for writing"`to help us debug the program.

After that we will start writing to the output file stream.
```c++
auto nameSize = person.name_.size();
outFile.write(reinterpret_cast<const char *>(&nameSize), sizeof(size_t));
```

As you can see `nameSize` variable has the size of the name. After that we write the name size inside the file.
We do that because including the variable length in the serialization provides a structured way to store and deserialize data.
This is commonly done to handle strings and other dynamic data during the serializing process.
We use `reinterpret_cast<const char *>(&nameSize)` to type cast the address of nameSize from an unsigned int or `size_t`
to a constant character `const char *`. This is like telling the compiler I know that `nameSize` is a `size_t` but treat the emory as a sequence of characters `const char *`. 
The reason this is done is because of the arguments of the `write()` function [std::basic_ostream<CharT,Traits>::write](https://en.cppreference.com/w/cpp/io/basic_ostream/write)
of the std::ofstream, it expects a const char * in the first argument. This is because `write()` is designed to write raw binary data,
and `const char *` is a common way to represent a sequence of bytes in C++.


```c++
outFile.write(person.name_.c_str(), nameSize);
```

We proceed to write each character with the defined nameSize to the help of the [c_str](https://en.cppreference.com/w/cpp/string/basic_string/c_str)
which is of a type `const char *` .


```c++
 outFile.write(reinterpret_cast<const char *>(&person.age_), sizeof(int));
 outFile.write(reinterpret_cast<const char *>(&person.height_), sizeof(double));
```


We write the data for both the person `int` age and the `double` height.
We also assign the size of a single int and a double using the function `sizeof()`.



```c++
outFile.close();

        if (!outFile.good()){
            throw std::invalid_argument("Error occurred in the writing time");
        }

```
Following, after writing all the data we close the file using the [close()](https://en.cppreference.com/w/cpp/io/basic_ofstream/close) function and check if the 
file is not [good()](https://en.cppreference.com/w/cpp/io/basic_ios/good) we throw to stop the program and identify the issue `Error occurred in the writing time`.


#### Implementing the `serialize` function in main:

```c++
int main(){
  Person Ahmed;
    Ahmed.set_name("Ahmed Al-Ganad");
    Ahmed.set_age(22);
    Ahmed.set_height(175.67);
```

We simply create an object variable. In this case `Ahmed` and initialize the class members. Then we use the function member
`serialilze` and adjust the parameters which is the object `Ahmed` and the name of the file to be created.

That's it for writing binary files!

### Deserializing or decoding data from binary format to data


```c++
void Person::deserialize(Person & person, const std::string& filename) 
```
The function does not return anything, it has two parameter a Person object passed by reference and a file name to read a
binary file to output data.

```c++
std::ifstream inFile{filename, std::ios::binary};
```

We declare a [std::ifstream](https://en.cppreference.com/w/cpp/io/basic_ifstream) that reads a created file. 
And similar to the previous declaration `std::ofstream` in the `serilaize()` function.
`std::ios::binary` sets a flag that the file should be treated as a binary file.

```c++
 if (!inFile){
        throw std::invalid_argument("error reading the file"); }
```
We then check if the file is good to go, if not we throw an `"error reading the file"`.

```c++
    // Read the name
    size_t nameSize{};
    inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t));
```

Starting of, we declare a variable `size_t nameSize`. And then we will use the [read()](https://en.cppreference.com/w/cpp/io/basic_istream/read)
function that reads binary data from the input file `inFile`.

If you remember back in the `serialize()` function, we
wrote the size of name ``` person.name_.size()``` into the output file created, see now we are retrieving that data to help adjust the
memory needed to decode the name.


```c++
  std::vector<char> nameBuffer(nameSize);
  inFile.read(nameBuffer.data(), nameSize);
```

We then declare a variable vector of characters `nameBuffer` and assign it's size with the nameSize we have gotten from
the previous read function `inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(size_t))`.

Following, we read or retrieve every bit using the [data()](https://en.cppreference.com/w/cpp/container/vector/data) that
returns each character inside the `std::vector<char> nameBuffer(nameSize)`. And we initialize the `n` number of element
to be assigned.

```c++
person.name_.assign(nameBuffer.data(), nameSize);
```
After that we assign the value initialized using the read value to the `name_` member type.

```c++
    // Read the age and the height
    inFile.read(reinterpret_cast<char*>(&person.age_), sizeof(int));
    inFile.read(reinterpret_cast<char*> (&person.height_), sizeof(double));
```

Now, we read the data  of the persons age and height, again using `read()` function.

```c++
inFile.close();

    if(!inFile.good())
        throw std::invalid_argument("error occurred in the reading time");
```

After that we also close the file using the [close()](https://en.cppreference.com/w/cpp/io/basic_ofstream/close) function.
And then check if the file did not face an issue during the process of reading the file.


#### Implementation in the main
```c++
    Person loadedPerson;
    loadedPerson.deserialize(loadedPerson, "person.bin");

    std::cout << "Loaded Person: " << loadedPerson.name() << ", " << loadedPerson.age() << " years old, "
    << loadedPerson.height() << "m tall" <<std::endl;
```

We create a new object variable `loadedPerson`. Then we call the member function
`deserialilze` and adjust the parameters which is the object `loadedPerson` and the name of the file to read the binary data 
from. At the end we can print the results in the console.

#### how can I look to the values of the binary files

Looking at the values of the binary file is not that simple because clion or Visual Studio does not let you see the 
binary data easily. You can use a simple command in linux to display the result of the binary data. 
```commandline
hexdump -C name_of_your_binary_file.bin
```

This will output something like this in our instance in the main:
```commandline
00000000  0e 00 00 00 00 00 00 00  41 68 6d 65 64 20 41 6c  |........Ahmed Al|
00000010  2d 47 61 6e 61 64 16 00  00 00 00 00 00 a0 70 f5  |-Ganad........p.|
00000020  65 40                                             |e@|
00000022
```
As you can see, 41 represent the letter 'A' in ASCII format, 68 represent 'l' and so on.


That's it for deserializing!


#### Explanation of the endianness concept.

[Endianness](https://en.wikipedia.org/wiki/Endianness) is a term used to describe the order in which 
bytes are stored in computer memory or data communication.

To simplify this out. The is two main types of endian `Big-Endian` and `Small-Endian`.

The Big-Endian is a term used to say that a certain system stores the memory of the most significant bit
in the lowest memory. 

In contrast, the Small-Endian is a system that stores the least significant bit in the lowest memory.

This image will help you further understand the difference between big and small endianness.
![Endianness Image](https://www.baeldung.com/wp-content/uploads/sites/4/2022/10/endianness-1024x317.png)

--------------------------------------------------------------------------------------------------------------------

### Examples in code to differentiate between big and small endianness

```c++
void check_for_endianness()
{
    // Declare an unsigned integer variable and initialize it to 1.
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
```
To check the endian the function `check_for_endian()` starts of with simple declaration of an `unsigned int x = 1`


After that `char *c = (char*) &x;` we declare a pointer to a char `c` and assigns it the address of the integer variable x.
This allows us to access the individual bytes of the integer.

Finally, we check `(int)*c` this returns an integer value of the first byte pointed
to by `c`, by referencing it using `*c`. We retrieve the value stored at the memory location pointed
to by `c`. The cast `(int)` is used to convert the character value to integer.

In Little-endian systems, the least significant byte is stored first, so the value at the first byte `*c` will be 1. 
In Big-endian systems, the most significant byte is stored first, so the value at the first byte will be 0.


That's it for this project hope you enjoyed and everything was clear.












