#include <string>
#include <iostream>

using std::string;
using std::cout;

class Implementation {
public:
    virtual ~Implementation() = default;
    [[nodiscard]] virtual string OperationImplementation() const = 0;
};

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

class ExtendedAbstraction : public Abstraction {
public:
    explicit ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) {
    }
    [[nodiscard]] string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" + this->implementation_->OperationImplementation();
    }
};

void ClientCode(const Abstraction& abstraction) {
    cout << abstraction.Operation();
}

int main() {
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
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