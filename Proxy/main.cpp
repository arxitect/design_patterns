#include <iostream>
#include <string>

using std::string;
using std::cout;

class Subject {
public:
    virtual void Request() const = 0;
};

class RealSubject : public Subject {
public:
    void Request() const override {
        cout << "RealSubject: Handing request.\n";
    }
};

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

public:
    explicit Proxy(RealSubject *realSubject) : realSubject_(new RealSubject(*realSubject)) {}
    ~Proxy() {
        delete realSubject_;
    }

    void Request() const override {
        if(this->checkAccess()){
            this->realSubject_->Request();
            this->logAccess();
        }
    }
};

void ClientCode(const Subject &subject)
{
    subject.Request();
}

int main()
{
    cout << "Client: Executing the client code with a real subject:\n";
    RealSubject *realSubject = new RealSubject;
    ClientCode(*realSubject);
    cout << "\n";
    cout << "Client: Executing the same client code with a proxy:\n";
    Proxy *proxy = new Proxy(realSubject);
    ClientCode(*proxy);

    delete realSubject;
    delete proxy;
    return 0;
}