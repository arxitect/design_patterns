#include <iostream>
#include <string>
#include <array>

using std::string;
using std::cout;
using std::array;

/* The Visitor interface declares a set of visiting methods that
 * correspond to component classes. The signature of the visit method
 * allows the visitor to determine the specific class of the component
 * with which he is dealing. */
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
public:
    virtual void visitConcreteComponentA(const ConcreteComponentA *element) const = 0;
    virtual void visitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

/* The Component interface declares an accept method,
 * which, as an argument, can be received by any object that
 * implements the visitor interface. */
class Component {
public:
    virtual ~Component() = default;
    virtual void accept(Visitor *visitor) const = 0;

};

/* Each ConcreteComponent must implement the accept method in
 * such a way that it invokes the visitor method corresponding to the component class. */
class ConcreteComponentA : public Component {

public:
    void accept(Visitor *visitor) const override {
        visitor->visitConcreteComponentA(this);
    }

    string exclusiveMethodOfConcreteComponentA() const {
        return "A";
    }
};

class ConcreteComponentB : public Component {
public:
    void accept(Visitor *visitor) const override {
        visitor->visitConcreteComponentB(this);
    }
    string specialMethodOfConcreteComponentB() const {
        return "B";
    }
};

/* Specific Visitors implement several versions of the same
 * algorithm that can work with all classes of specific components. */
class ConcreteVisitor1 : public Visitor {
public:
    void visitConcreteComponentA(const ConcreteComponentA *element) const override {
        cout << element->exclusiveMethodOfConcreteComponentA()
             << " + ConcreteVisitor1\n";
    }

    void visitConcreteComponentB(const ConcreteComponentB *element) const override {
        cout << element->specialMethodOfConcreteComponentB()
             << " + ConcreteVisitor1\n";
    }
};

class ConcreteVisitor2 : public Visitor {
public:
    void visitConcreteComponentA(const ConcreteComponentA *element) const override {
        cout << element->exclusiveMethodOfConcreteComponentA()
                  << " + ConcreteVisitor2\n";
    }
    void visitConcreteComponentB(const ConcreteComponentB *element) const override {
        cout << element->specialMethodOfConcreteComponentB()
             << " + ConcreteVisitor2\n";
    }
};

/* Client code can perform visitor operations on any set
 * of elements without figuring out their specific classes.
 * The accept operation directs the call to the corresponding
 * operation in the visitor's object. */
void ClientCode(array<const Component *, 2> components, Visitor *visitor) {
    for (const Component *comp : components) {
        comp->accept(visitor);
    }

}

int main() {
    array<const Component *, 2> components = {new ConcreteComponentA,
                                              new ConcreteComponentB};
    cout << "The client code works with all visitors via the base Visitor interface:\n";
    auto *visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    cout << "\n";
    cout << "It allows the same client code to work with different types of visitors:\n";
    auto *visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);

    for (const Component *comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;

    return 0;
}