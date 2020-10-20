#include <iostream>

using std::cout;

/* An AbstractClass defines a template method containing the skeleton of
 * an algorithm consisting of calls to (usually) abstract primitive operations.
 * Concrete subclasses should implement these operations, but leave the template
 * method itself unchanged. */
class AbstractClass {
public:
    void templateMethod() const {
        this->baseOperation1();
        this->requiredOperations1();
        this->baseOperation2();
        this->hook1();
        this->requiredOperation2();
        this->baseOperation3();
        this->hook2();
    }
protected:
    void baseOperation1() const {
        cout << "AbstractClass says: I am doing the bulk of the work\n";
    }

    void baseOperation2() const {
        cout << "AbstractClass says: But I let subclasses override some operations\n";
    }

    void baseOperation3() const {
        cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
    }

    virtual void requiredOperations1() const = 0;
    virtual void requiredOperation2() const = 0;
    virtual void hook1() const {}
    virtual void hook2() const {}
};

/* Concrete classes must implement all the abstract
 * operations of the base class. They can also override some
 * operations with the default implementation. */
class ConcreteClass1 : public AbstractClass {
protected:
    void requiredOperations1() const override {
        cout << "ConcreteClass1 says: Implemented Operation1\n";
    }

    void requiredOperation2() const override {
        cout << "ConcreteClass1 says: Implemented Operation2\n";
    }
};

class ConcreteClass2 : public AbstractClass {
protected:
    void requiredOperations1() const override {
        cout << "ConcreteClass2 says: Implemented Operation1\n";
    }

    void requiredOperation2() const override {
        cout << "ConcreteClass2 says: Implemented Operation2\n";
    }

    void hook1() const override {
        cout << "ConcreteClass2 says: Overridden Hook1\n";
    }
};

/* ClientCode calls a template method to execute the algorithm.
 * ClientCode does not need to know the specific class of the object
 * that it works with, provided that it works with objects through the
 * interface of their base class. */
void ClientCode(AbstractClass *class_)
{
    class_->templateMethod();
}

int main()
{
    cout << "Same client code can work with different subclasses:\n";
    auto concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    cout << "\n";

    cout << "Same client code can work with different subclasses:\n";
    auto concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);

    delete concreteClass1;
    delete concreteClass2;

    return 0;
}