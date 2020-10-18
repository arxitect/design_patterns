#include <iostream>

using std::cout;

/* The Subject Interface announces general
 * operations for both the Real Subject and the Proxy.*/
class Subject {
public:
    virtual void Request() const = 0;
};

/* The real Subject contains some basic business logic. */
class RealSubject : public Subject {
public:
    void Request() const override {
        cout << "RealSubject: Handing request.\n";
    }
};

/* The Proxy interface is identical to the Real Subject interface. */
class Proxy : public Subject {
private:
    RealSubject *realSubject_;

    bool checkAccess() const {
        cout << "Proxy: checking access prior to firing a real request.\n";
        return true;
    }

    void logAccess() const {
        cout << "Proxy: logging the time of request.\n";
    }

    /* The substitute stores a reference to an object of the RealSubject class.
     * The client can either lazily download it or transfer it to the Proxy. */
public:
    explicit Proxy(RealSubject *realSubject) : realSubject_(new RealSubject(*realSubject)) {}
    ~Proxy() {
        delete realSubject_;
    }

    /* The most common uses for the Proxy pattern are lazy loading,
     * caching, access control, logging, etc. */
    void Request() const override {
        if(this->checkAccess()){
            this->realSubject_->Request();
            this->logAccess();
        }
    }
};

/* Client code must work with all objects (both real and alternate) through
 * the Subject's interface in order to support both real entities and alternates. */
void ClientCode(const Subject &subject)
{
    subject.Request();
}

int main()
{
    cout << "Client: Executing the client code with a real subject:\n";
    auto realSubject = new RealSubject;
    ClientCode(*realSubject);
    cout << "\n";

    cout << "Client: Executing the same client code with a proxy:\n";
    auto proxy = new Proxy(realSubject);
    ClientCode(*proxy);

    delete realSubject;
    delete proxy;
    return 0;
}