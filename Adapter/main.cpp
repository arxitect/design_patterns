#include <string>
#include <algorithm>
#include <iostream>

using std::string;
using std::cout;

/* The target class declares an interface
 * with which client code can work. */
class Target {
public:
    virtual ~Target() = default;

    [[nodiscard]] virtual string Request() const {
        return "Target: the default targets's behavior";
    }
};

/* An adaptable class contains some useful behavior,
 * but its interface is incompatible with existing client code.
 * The adaptable class needs some refinement
 * before the client code can use it. */
class Adaptee {
public:
    static string SpecificRequest() {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/* The Adapter makes the Adaptable Class interface
 * compatible with the target interface. */
class Adapter : public Target {
private:
    Adaptee *adaptee;
public:
    explicit Adapter(Adaptee *adaptee1) : adaptee(adaptee1) {}
    [[nodiscard]] string Request() const override {
        string toReverse = this->adaptee->SpecificRequest();
        std::reverse(toReverse.begin(), toReverse.end());
        return "Adapter: (TRANSLATED)" + toReverse;
    }
};

/*  Клиентский код поддерживает все классы, использующие целевой интерфейс. */
void ClientCode(const Target *target) {
    cout << target->Request();
}

int main()
{
    cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    cout << "\n\n";
    Adaptee *adaptee = new Adaptee;
    cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    cout << "Adaptee: " << adaptee->SpecificRequest();
    cout << "\n\n";
    cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);
    cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;
    return 0;
}
