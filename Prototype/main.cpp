#include <iostream>
#include <unordered_map>

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

class Prototype {
protected:
    string prototypeName;
    float prototypeField;

public:
    Prototype() = default;
    explicit Prototype(string prototypeNameVal) : prototypeName(prototypeNameVal) {}
    virtual ~Prototype() = default;
    [[nodiscard]] virtual Prototype *Clone()const = 0;
    virtual void Method(float prototypeFieldval) {
        this->prototypeField = prototypeFieldval;
        cout << "Call method from: " << prototypeName << " with field: " << prototypeField << endl;
    }
};

class ConcretePrototype1 : public Prototype{
private:
    float concretePrototypeField;
public:
    ConcretePrototype1(string prototypeNameVal, float concretePrototypeFieldVal)
        : Prototype(prototypeNameVal), concretePrototypeField(concretePrototypeFieldVal){}

    [[nodiscard]] Prototype *Clone() const override {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype {
private:
    float concretePrototypeField2;

public:
    ConcretePrototype2(string prototypeNameVal, float concretePrototypeFieldVal)
            : Prototype(prototypeNameVal), concretePrototypeField2(concretePrototypeFieldVal) {
    }
    [[nodiscard]] Prototype *Clone() const override {
        return new ConcretePrototype2(*this);
    }
};

class PrototypeFactory {
private:
    std::unordered_map<Type, Prototype *, std::hash<int>> prototypes;

public:
    PrototypeFactory() {
        prototypes[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        prototypes[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }
    ~PrototypeFactory() {
        delete prototypes[Type::PROTOTYPE_1];
        delete prototypes[Type::PROTOTYPE_2];
    }
    Prototype *CreatePrototype(Type type) {
        return prototypes[type]->Clone();
    }
};

void Client(PrototypeFactory &prototype_factory) {
    std::cout << "Let's create a Prototype 1\n";

    Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;

    std::cout << "\n";

    std::cout << "Let's create a Prototype 2 \n";

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);

    delete prototype;
}

int main()
{
    PrototypeFactory *prototypeFactory = new PrototypeFactory();
    Client(*prototypeFactory);
    delete prototypeFactory;

    return 0;
}
