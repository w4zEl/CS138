#include <string>
#include "a5p1.h"
Animal::Animal(std::string name) : name(name) {}
Animal::~Animal() {}
std::string Animal::getName() const {
    return name;
}
Dog::Dog(std::string name) : Animal(name) {}
Dog::~Dog() {}
std::string Dog::speak() const {
    return "    Dog " + getName() + " says \"woof\".";
}
Sheep::Sheep(std::string name) : Animal(name) {};
Sheep::~Sheep() {}
std::string Sheep::speak() const {
    return "    Sheep " + getName() + " says \"baaa\".";
}
Flock::Flock(std::string dogName) : dog(new Dog(dogName)) {}
Flock::~Flock() {
    delete dog;
    for (auto s : sheepList) delete s;
}
void Flock::addSheep(std::string name) {
    sheepList.push_back(new Sheep(name));
}
std::string Flock::soundOff() const {
    std::string res("The flock of " + std::to_string(sheepList.size()) + " sheep speaks!\n" + dog->speak() + '\n');
    for (auto s : sheepList) res += s->speak() + '\n';
    return res;
}