#include <string>
#include <iostream>

using std::string;
using std::cout;

/* The Singleton class provides the `GetInstance` method, which behaves like
 * an alternative constructor and allows clients to receive
 * the same instance of the class with every call. */
class Singleton
{
protected:
    string value;
    /* The Singleton constructor should always be hidden to prevent
     * the creation of an object through the new operator. */
    explicit Singleton(const string value) : value(value){}
    static Singleton *singleton;
public:
    /* Singletons should not be cloned. */
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;

    static Singleton *getInstance(const string &value);

    [[nodiscard]] string getValue() const {
        return value;
    }
};

Singleton* Singleton::singleton = nullptr;

// Static methods should be defined outside the class.
Singleton *Singleton::getInstance(const string &value) {
    if(singleton == nullptr)
        singleton = new Singleton(value);
    return singleton;
}

int main()
{
    Singleton* singleton = Singleton::getInstance("Some string");
    cout << singleton->getValue() << "\n";
    return 0;
}