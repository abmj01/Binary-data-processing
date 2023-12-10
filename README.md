# Binary data processing

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
function that reads binary data from the `inFile`. If you remember back in the `serialize()` function, we
wrote the size of name ``` person.name_.size()``` into the output file created, see now we are retrieving that data to help adjust the
memory needed to decode the name.









