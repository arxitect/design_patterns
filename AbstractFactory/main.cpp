#include <iostream>
#include <string>

using std::string;

class AbstractWorkerA {
public:
    virtual ~AbstractWorkerA()= default;
    [[nodiscard]] virtual string UseFunctionA() const = 0;
};

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

    [[nodiscard]] string AnotherFunctionB(const AbstractWorkerA &collaborator) const override {
        const string result = collaborator.UseFunctionA();
        return "Result of the B1 collaborating with < " + result + " >";
    }
};

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

class AbstractFactory {
public:
    [[nodiscard]] virtual AbstractWorkerA *CreateWorkerA() const = 0;
    [[nodiscard]] virtual AbstractWorkerB *CreateWorkerB() const = 0;
};

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
