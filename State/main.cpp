#include <iostream>

using std::cout;

class Context;

/* The Base State class declares methods that all Concrete States
 * must implement, and also provides a reference back to the Context
 * object associated with the State. This backtrack can be used
 * by States to transfer Context to another State. */
class State {
protected:
    Context *context_;

public:
    virtual ~State() = default;

    void setContext(Context *context) {
        this->context_ = context;
    }

    virtual void Handle1() = 0;
    virtual void Handle2() = 0;
};

/* Context defines an interface of interest to customers.
 * It also stores a reference to an instance of the Status
 * subclass that displays the current state of the Context. */
class Context {
private:
    State *state_;

public:
    explicit Context(State *state) : state_(nullptr) {
        this->TransitionTo(state);
    }

    ~Context() {
        delete state_;
    }

    /* Context allows you to modify the State object at run time. */
    void TransitionTo(State *state) {
        cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        delete this->state_;
        this->state_ = state;
        this->state_->setContext(this);
    }

    void Request1() {
        this->state_->Handle1();
    }

    void Request2() {
        this->state_->Handle2();
    }
};

/* Concrete States implement various behaviors
 * related to the Context state. */
class ConcreteStateA : public State {
public:
    void Handle1() override;

    void Handle2() override {
        cout << "ConcreteStateA handles request2.\n";
    }
};

class ConcreteStateB : public State {
public:
    void Handle1() override {
        cout << "ConcreteStateB handles request1.\n";
    }

    void Handle2() override {
        cout << "ConcreteStateB handles request2.\n";
        cout << "ConcreteStateB wants to change the state of the context.\n";

        this->context_->TransitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::Handle1() {
    cout << "ConcreteStateA handles request1.\n";
    cout << "ConcreteStateA wants to change the state of the context.\n";

    this->context_->TransitionTo(new ConcreteStateB);
}

/* Client code */
void ClientCode()
{
    auto *context = new Context(new ConcreteStateA);
    context->Request1();
    context->Request2();
    delete context;
}

int main()
{
    ClientCode();
    return 0;
}