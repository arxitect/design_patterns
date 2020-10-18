#include <string>
#include <iostream>
#include <list>

using std::list;
using std::string;
using std::cout;


class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const string &messageFromSubject) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
    virtual void notify() = 0;
};

/* The Subject owns some important status and notifies observers of its changes. */
class Subject : public ISubject {
private:
    list<IObserver *> listObserver_;
    string message_;
public:
    ~Subject() override {
        cout << "Goodbye, I was the Subject.\n";
    }

    // Subscription Management Methods.
    void observerAmount() {
        cout << "There are " << listObserver_.size() << " observers in the list.\n";
    }

    void attach(IObserver *observer) override {
        listObserver_.push_back(observer);
    }

    void detach(IObserver *observer) override {
        listObserver_.remove(observer);
    }

    void notify() override {
        auto iterator = listObserver_.begin();
        observerAmount();
        while (iterator != listObserver_.end()){
            (*iterator)->update(message_);
            ++iterator;
        }
    }

    void createMessage(string message = "Empty") {
        this->message_ = message;
        notify();
    }

    void someBusinessLogic() {
        this->message_ = "change message message";
        notify();
        cout << "I'm about to do something important\n";
    }
};

class Observer : IObserver {
private:
    string messageFromSubject_;
    Subject &subject_;
    static int staticNumber_;
    int number_;
public:
    explicit Observer(Subject &subject) : subject_(subject) {
        this->subject_.attach(this);
        cout << "Hi, I'm the Observer \"" << ++Observer::staticNumber_ << "\".\n";
        this->number_ = Observer::staticNumber_;
    }
    ~Observer() override{
        cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }

    void printInfo() {
        cout << "Observer \""
             << this->number_
             << "\": a new message is available --> "
             << this->messageFromSubject_ << "\n";
    }

    void update(const string &messageFromSubject) override {
        messageFromSubject_ = messageFromSubject;
        printInfo();
    }

    void removeMeFromList() {
        subject_.detach(this);
        cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
};

int Observer::staticNumber_ = 0;

void ClientCode()
{
    auto subject = new Subject;
    auto observer1 = new Observer(*subject);
    auto observer2 = new Observer(*subject);
    auto observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;

    subject->createMessage("Hello World! :D");
    observer3->removeMeFromList();

    subject->createMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->removeMeFromList();
    observer5 = new Observer(*subject);

    subject->createMessage("My new car is great! ;)");
    observer5->removeMeFromList();

    observer4->removeMeFromList();
    observer1->removeMeFromList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main()
{
    ClientCode();
    return 0;
}