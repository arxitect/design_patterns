#include <iostream>
#include <string>

using std::string;

/* Each individual worker in the worker family must have a basic interface.
All worker variations must implement this interface. */
class AbstractWorkerA {
public:
    virtual ~AbstractWorkerA()= default;
    [[nodiscard]] virtual string UseFunctionA() const = 0;
};

/* Concrete workers are created by concrete factories */
class ConcreteWorkerA1 : public AbstractWorkerA {
public:
    [[nodiscard]] string UseFunctionA() const override {
        return "Result of the worker A1";
    }
};

class ConcreteWorkerA2 : public AbstractWorkerA {
    [[nodiscard]] string UseFunctionA() const override {
        return "Result of the worker A2";
    }
};

/* The base interface of another worker. All workers can interact with
 * each other, but the correct interaction is possible only between workers of the same variation*/
class AbstractWorkerB {
public:
    virtual ~AbstractWorkerB() = default;
    [[nodiscard]] virtual string UseFunctionB() const = 0;
    [[nodiscard]] virtual string AnotherFunctionB(const AbstractWorkerA &collaborator) const = 0;
};

class ConcreteWorkerB1 : public AbstractWorkerB {
public:
    [[nodiscard]] string UseFunctionB() const override {
        return "The result of the worker B1";
    }

    /*Worker B can interact with Workers A same variation.
     * AbstractFactory ensures that all workers it creates have same variation and are therefore compatible*/
    [[nodiscard]] string AnotherFunctionB(const AbstractWorkerA &collaborator) const override {
        const string result = collaborator.UseFunctionA();
        return "Result of the B1 collaborating with < " + result + " >";
    }
};

/* Concrete workers are created by concrete factories */
class ConcreteWorkerB2 : public AbstractWorkerB {
public:
    [[nodiscard]] string UseFunctionB() const override {
        return "Result of the worker B2";
    }

    [[nodiscard]] string AnotherFunctionB(const AbstractWorkerA &collaborator) const override {
        const string result = collaborator.UseFunctionA();
        return "The result of the B2 collaborating with < " + result + " >";
    }
};

/* AbstactFactory interface announced a set of methods that returns various abstract workers */
class AbstractFactory {
public:
    [[nodiscard]] virtual AbstractWorkerA *CreateWorkerA() const = 0;
    [[nodiscard]] virtual AbstractWorkerB *CreateWorkerB() const = 0;
};

/* A concrete factory produces a family of workers of the same variation. */
class ConcreteFactory1 : public AbstractFactory {
public:
    [[nodiscard]] AbstractWorkerA *CreateWorkerA() const override {
        return new ConcreteWorkerA1;
    }
    [[nodiscard]] AbstractWorkerB *CreateWorkerB() const override {
        return new ConcreteWorkerB1;
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    [[nodiscard]] AbstractWorkerA *CreateWorkerA() const override {
        return new ConcreteWorkerA2;
    }
    [[nodiscard]] AbstractWorkerB *CreateWorkerB() const override {
        return new ConcreteWorkerB2;
    }
};

using std::cout;
using std::endl;

/* Client code only works with factories and products through abstract types */
void ClientCode(const AbstractFactory &factory) {
    const AbstractWorkerA *workerA = factory.CreateWorkerA();
    const AbstractWorkerB *workerB = factory.CreateWorkerB();
    cout << workerB->UseFunctionB() << endl;
    cout << workerB->AnotherFunctionB(*workerA) << endl;
    delete workerA;
    delete workerB;
}

int main()
{
    cout << "Testing client with the first factory type:" << endl;
    ConcreteFactory1 *f1 = new ConcreteFactory1;
    ClientCode(*f1);
    delete f1;
    cout << endl;
    cout << "Testing the same client code with second factory type: " << endl;
    ConcreteFactory2 *f2 = new ConcreteFactory2;
    ClientCode(*f2);
    delete f2;
    return 0;
}
