#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::vector;

/* The Handler interface declares a method for constructing a chain of handlers.
 * It also declares a method to execute the request. */
class Handler {
public:
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual string Handle(string request) = 0;
};

/* The default chain behavior can be implemented
 * inside the base class of the handler. */
class AbstractHandler : public Handler {
private:
    Handler *next_handler_;
public:
    AbstractHandler() : next_handler_(nullptr) {}
    Handler *SetNext(Handler *handler) override {
        this->next_handler_ = handler;
        //Returning the handler from here will allow the handlers to be linked in a simple way,
        //like this:
        // monkey->setNext(squirrel)->setNext(dog);
        return handler;
    }
    string Handle(string request) override {
        if (this->next_handler_)
            return this->next_handler_->Handle(request);
        return {};
    }
};

/* All Concrete Handlers either process the request or pass
 * it on to the next handler in the chain. */
class MonkeyHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

class SquirrelHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Nut")
            return "Squirrel: I'll eat the " + request + ".\n";
        else
            return AbstractHandler::Handle(request);
    }
};

class DogHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "MeatBall")
            return "Dog: I'll eat the " + request + ".\n";
        else
            return AbstractHandler::Handle(request);
    }
};

/* Typically, client code is designed to work with a single handler.
 * In most cases, the client does not even know that this handler
 * is part of the chain. */
void ClientCode(Handler &handler)
{
    vector<string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const string &f : food) {
        cout << "Client: Who wants a " << f << "?\n";
        const string result = handler.Handle(f);
        if (!result.empty())
            cout << "  " << result;
        else
            cout << "  " << f << " was left untouched.\n";
    }
}

/* Another part of the client code creates the chain itself. */
int main() {
    MonkeyHandler *monkey = new MonkeyHandler;
    SquirrelHandler *squirrel = new SquirrelHandler;
    DogHandler *dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);

    //The client should be able to send a request to any handler
    cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    cout << "\n";
    cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;

    return 0;
}