#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using std::string;
using std::cout;
using std::vector;
using std::time_t;

/* The Memento interface provides a way to retrieve Memento metadata,
 * such as the date it was created or the name. However, he does not reveal the condition of the Creator. */
class Memento {
public:
    virtual string getName() const = 0;
    virtual string date() const = 0;
    virtual string state() const = 0;
};

/* A ConcreteMemento contains the infrastructure for storing the state of the Originator. */
class ConcreteMemento : public Memento {
private:
    string state_;
    string date_;
public:
    explicit ConcreteMemento(string state) : state_(state) {
        this->state_ = state;
        time_t now = std::time(0);
        this->date_ = std::ctime(&now);
    }
    /* The Originator uses this method when restoring his state. */
    string state() const override {
        return this->state_;
    }
    /* Other methods are used by the Caretaker to display metadata. */
    string getName() const override {
        return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
    }
    string date() const override {
        return this->date_;
    }
};

/* The Originator contains some important condition that can change over time. */
class Originator {
private:
    string state_;

    string GenerateRandomString(int length = 10) {
        const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        int stringLength = sizeof(alphanum) - 1;

        string random_string;
        for (int i = 0; i < length; i++) {
            random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }

public:
    Originator(string state) : state_(state) {
        cout << "Originator: My initial state is: " << this->state_ << "\n";
    }

    /* Originator business logic can affect its internal state. Therefore, the client must back up the
     * state using the save method before running the business logic methods. */
    void DoSomething() {
        cout << "Originator: I'm doing something important.\n";
        this->state_ = this->GenerateRandomString(30);
        cout << "Originator: and my state has changed to: " << this->state_ << "\n";
    }

    /* Saves the current state */
    Memento *Save() {
        return new ConcreteMemento(this->state_);
    }

    /* Restores Originator state */
    void Restore(Memento *memento) {
        this->state_ = memento->state();
        cout << "Originator: My state has changed to: " << this->state_ << "\n";
    }
};

/* The Caretaker does not depend on the class of a particular Memento. Thus, he does not have access to the state of
 * the creator stored inside the Memento. It works with all Memento through the Memento's basic interface. */
class Caretaker {
private:
    vector<Memento *> mementos_;
    Originator *originator_;
public:
    explicit Caretaker(Originator *originator) : originator_(originator) {
        this->originator_ = originator;
    }

    void Backup() {
        cout << "\nCaretaker: Saving Originator's state...\n";
        this->mementos_.push_back(this->originator_->Save());
    }
    void Undo() {
        if (!this->mementos_.size()) {
            return;
        }
        Memento *memento = this->mementos_.back();
        this->mementos_.pop_back();
        cout << "Caretaker: Restoring state to: " << memento->getName() << "\n";
        try {
            this->originator_->Restore(memento);
        } catch (...) {
            this->Undo();
        }
    }
    void ShowHistory() const {
        cout << "Caretaker: Here's the list of mementos:\n";
        for (Memento *memento : this->mementos_) {
            std::cout << memento->getName() << "\n";
        }
    }
};

/* Client code */
void ClientCode() {
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    cout << "\n";
    caretaker->ShowHistory();
    cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->Undo();
    cout << "\nClient: Once more!\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    ClientCode();
    return 0;
}