#include <iostream>
#include <string>

using std::string;
using std::cout;

/* The component's basic interface defines behavior that is changed by decorators. */
class Component {
public:
    virtual ~Component() = default;
    [[nodiscard]] virtual string Operation() const = 0;
};

/* Concrete Components provide default behavior implementations.
 * There may be several variations of these classes. */
class ConcreteComponent : public Component {
public:
    [[nodiscard]] string Operation() const override {
        return "ConcreteComponent";
    }
};

/* The Decorator base class follows the same interface as the other components.
 * The main goal of this class is to define a wrapper interface for all specific decorators. */
class Decorator : public Component {
protected:
    Component *component_;
public:
    explicit Decorator(Component *component) : component_(component) {};
    // The decorator delegates all the work to the wrapped component.
    [[nodiscard]] string Operation() const override {
        return this->component_->Operation();
    }
};

/* Concrete Decorators call a wrapped object
 * and modify its result in some way. */
class ConcreteDecoratorA : public Decorator {
public:
    explicit ConcreteDecoratorA(Component* component) : Decorator(component) {}

    [[nodiscard]] string Operation() const override {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    explicit ConcreteDecoratorB(Component* component) : Decorator(component) {}

    [[nodiscard]] string Operation() const override {
        return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
    }
};

/* Client code works with all objects using the Component interface. */
void ClientCode(Component* component)
{
    cout << "RESULT: " << component->Operation();
}

int main()
{
    Component* simple = new ConcreteComponent;
    cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    cout << "\n\n";

    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1);
    cout << "Client: Now I've got a decorated component:\n";
    ClientCode(decorator2);
    cout << "\n";

    delete simple;
    delete decorator1;
    delete decorator2;

    return 0;
}