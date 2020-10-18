#include <string>
#include <iostream>

using std::string;
using std::cout;

/* The implementation establishes an interface for all implementation classes.
 * It must not match the Abstraction interface. */
class Implementation {
public:
    virtual ~Implementation() = default;
    [[nodiscard]] virtual string OperationImplementation() const = 0;
};

/* Each Specific Implementation corresponds to a specific platform and implements
 * the Implementation interface using the API of that platform. */
class ConcreteImplementationA : public Implementation {
public:
    [[nodiscard]] string OperationImplementation() const override {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};

class ConcreteImplementationB : public Implementation {
public:
    [[nodiscard]] string OperationImplementation() const override {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};

/* Abstraction establishes an interface for the "control" part of two class hierarchies.
 * It contains a reference to an object from the hierarchy of Implementation and delegates to it all the real work. */
class Abstraction {
protected:
    Implementation* implementation_;
public:
    explicit Abstraction(Implementation* implementation) : implementation_(implementation) {}

    virtual ~Abstraction() = default;

    [[nodiscard]] virtual string Operation() const {
        return "Abstraction: Base operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};

/* You can extend the Abstraction without changing the implementation classes. */
class ExtendedAbstraction : public Abstraction {
public:
    explicit ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) {}

    [[nodiscard]] string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" + this->implementation_->OperationImplementation();
    }
};

void ClientCode(const Abstraction& abstraction)
{
    cout << abstraction.Operation();
}

/* Client code must work with any pre-configured
 * combination of abstraction and implementation. */
int main()
{
    Implementation* implementation = new ConcreteImplementationA;
    auto abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    cout << "\n";
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    return 0;
}