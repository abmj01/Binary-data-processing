#include <iostream>
#include <fstream>
#include <vector>

class Person{
public:
    Person();

    void serialize(Person & person, const std::string& filename);
    void deserialize(Person & person, const std::string& filename);

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
};