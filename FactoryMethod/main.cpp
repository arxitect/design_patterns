#include <iostream>

using std::cout;
using std::endl;

class Product {

};

class ConcreteProduct1 {

};

class ConcreteProduct2 {

};

class Creator {
public:
    virtual ~Creator()= default;
    [[nodiscard]] virtual Product* FactoryMethod() const = 0;

};

class ConcreteCreator1 {

};

void ClientCode(const Creator &creator)
{

}

int main()
{
    return 0;
}