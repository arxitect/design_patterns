#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/* The Product Interface announces the operations
 * that all specific products must perform. */
class Product {
public:
    virtual ~Product() = default;
    [[nodiscard]] virtual string Operation() const = 0;
};

/* Specific Products provides various
 * implementations of the Product interface. */
class ConcreteProduct1 : public Product {
public:
    [[nodiscard]] string Operation() const override {
        return "{result of the ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product {
    [[nodiscard]] string Operation() const override {
        return "{result of the ConcreteProduct2}";
    }
};

/* The Creator class declares a factory method
 * that should return an object of the Product class.
 * Creator subclasses typically provide an implementation
 * of this method. */
class Creator {
public:
    virtual ~Creator()= default;
    [[nodiscard]] virtual Product* FactoryMethod() const = 0;

    [[nodiscard]] string SomeOperation() const {
        Product *product = this->FactoryMethod();
        string result = "Creator: the same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }

};

/* Concrete Creators redefine the factory method
 * in order to change the type of resultant product. */
class ConcreteCreator1 : public Creator {
public:
    [[nodiscard]] Product* FactoryMethod() const override {
        return new ConcreteProduct1;
    }
};

class ConcreteCreator2 : public Creator {
public:
    [[nodiscard]] Product* FactoryMethod() const override {
        return new ConcreteProduct2;
    }
};

/* Client code works with an instance of a specific creator,
 * although through its basic interface.
 * While the client continues to work with the creator
 * through the base interface, you can pass any
 * subclass of the creator to it. */
void ClientCode(const Creator &creator)
{
    cout << "Client: i'm not aware of the creator's class, but it still works\n"
         << creator.SomeOperation() << endl;
}

/* The application selects the type of creator
 * depending on the configuration or environment. */
int main()
{
    cout << "App: Launched with ConcreteCreator 1.\n";
    Creator *creator = new ConcreteCreator1();
    ClientCode(*creator);
    cout << endl;

    cout << "App: Launched with ConcreteCreator 2.\n";
    Creator *creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;
    return 0;
}