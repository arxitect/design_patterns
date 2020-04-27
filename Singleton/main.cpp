#include <string>
#include <iostream>

using std::string;
using std::cout;

class Singleton
{
protected:
    string value;
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