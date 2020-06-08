#include <iostream>

using std::cout;

class Context;

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
    void TransitionTo(State *state) {
        cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->state_ != nullptr)
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
    {
        cout << "ConcreteStateA handles request1.\n";
        cout << "ConcreteStateA wants to change the state of the context.\n";

        this->context_->TransitionTo(new ConcreteStateB);
    }
}

void ClientCode() {
    auto *context = new Context(new ConcreteStateA);
    context->Request1();
    context->Request2();
    delete context;
}

int main() {
    ClientCode();
    return 0;
}