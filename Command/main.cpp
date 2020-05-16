#include <iostream>
#include <string>

using std::string;
using std::cout;

class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() const = 0;
};

class SimpleCommand : public Command {
private:
    string payLoad_;
public:
    explicit SimpleCommand(string payLoad) : payLoad_(payLoad){}
    void Execute() const override {
        cout << "SimpleCommand: See, I can do simple things like printing (" << this->payLoad_ << ")\n";
    }
};

class Receiver {
public:
    void doSomething(const string &a) {
        cout << "Receiver: Working on (" << a << ".)\n";
    }
    void doSomethingElse(const string &b) {
        cout << "Receiver: Also working on (" << b << ".)\n";
    }
};

class ComplexCommand : public Command {
private:
    Receiver *receiver_;
    string a_;
    string b_;
public:
    ComplexCommand(Receiver *receiver, string a, string b) : receiver_(receiver), a_(a), b_(b) {}

    void Execute() const override {
        cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->receiver_->doSomething(this->a_);
        this->receiver_->doSomethingElse(this->b_);
    }
};

class Invoker {
private:
    Command *onStart_;
    Command *onFinish_;
public:
    ~Invoker() {
        delete onStart_;
        delete onFinish_;
    }

    void setOnStart(Command *command) {
        this->onStart_ = command;
    }

    void setOnFinish(Command *command) {
        this->onFinish_ = command;
    }

    void doSomethingImportant() {
        cout << "Invoker: Does anybody want something done before I begin?\n";
        if(this->onStart_)
            this->onStart_->Execute();
        cout << "Invoker: ...doing something really important...\n";
        cout << "Invoker: Does anybody want something done after I finish?\n";
        if(this->onFinish_)
            this->onFinish_->Execute();
    }
};
int main()
{
    Invoker *invoker = new Invoker;
    invoker->setOnStart(new SimpleCommand("Say Hi!"));
    Receiver *receiver = new Receiver;
    invoker->setOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
    invoker->doSomethingImportant();

    delete invoker;
    delete receiver;
    return 0;
}

