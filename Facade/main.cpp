#include <iostream>
#include <string>

using std::cout;
using std::string;

/* The subsystem can accept requests either from the
 * facade or from the client directly.
 * In any case, for the Subsystem, the Facade is another client,
 * and it is not part of the Subsystem.*/
class Subsystem1 {
public:
    [[nodiscard]] string Operation1() const {
        return "Subsystem1: Ready!\n";
    }
    [[nodiscard]] string OperationN() const {
        return "Subsystem1: Go!\n";
    }
};

class Subsystem2 {
public:
    [[nodiscard]] string Operation1() const {
        return "Subsystem2: Get Ready!\n";
    }
    [[nodiscard]] string OperationZ() const {
        return "Subsystem2: Fire!\n";
    }
};

/* The Facade class provides a simple interface
 * for the complex logic of one or more subsystems.
 * The facade delegates client requests to appropriate
 * objects within the subsystem. The facade is also
 * responsible for managing their life cycle. */
class Facade {
protected:
    Subsystem1 *subsystem1_;
    Subsystem2 *subsystem2_;
public:
    explicit Facade(Subsystem1 *subsystem1 = nullptr, Subsystem2 *subsystem2 = nullptr) {
        this->subsystem1_ = subsystem1 ?: new Subsystem1;
        this->subsystem2_ = subsystem2 ?: new Subsystem2;
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }
    string Operation() {
        string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

/* Client code works with complex subsystems
 * through a simple interface provided by the Facade. */
void ClientCode(Facade *facade)
{
    cout << facade->Operation();
}

/* In the client code, some subsystem objects may already be created.
 * In this case, it may be appropriate to initialize the Facade with
 * these objects instead of allowing the Facade to create new instances. */
int main()
{
    Subsystem1 *subsystem1 = new Subsystem1;
    Subsystem2 *subsystem2 = new Subsystem2;
    Facade *facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);
    delete facade;

    return 0;
}