#include <string>
#include <iostream>
#include <unordered_map>
#include <initializer_list>
#include <utility>

using std::cout;
using std::string;
using std::ostream;
using std::unordered_map;
using std::initializer_list;
using std::make_pair;
using std::pair;

/* Purpose: Allows you to accommodate a larger number of objects in the allocated RAM.
 * Flyweight saves memory by sharing the general state of objects among themselves,
 * instead of storing the same data in each object. */
struct SharedState
{
    string brand_;
    string model_;
    string color_;
    SharedState(const string &brand,const string &model, const string &color)
    : brand_(brand), model_(model), color_(color){}

    friend ostream &operator<<(ostream &os, const SharedState &ss) {
        return os << "[ " << ss.brand_ << ", " << ss.model_ << ", " << ss.color_ << " ]";
    }
};

struct UniqueState
{
    string owner_;
    string plates_;

    UniqueState(const string &owner, const string &plates) : owner_(owner), plates_(plates){}

    friend ostream &operator<<(ostream &os, const UniqueState &us)
    {
        return os << "[ " << us.owner_ << " , " << us.plates_ << " ]";
    }
};

/* Flyweight stores a common part of the state (also called internal state)
 * that belongs to several real business objects. The Flyweight accepts the
 * remainder of the state (an external state unique to each object) through its method parameters. */
class Flyweight
{
private:
    SharedState *sharedState_;
public:
    explicit Flyweight(const SharedState *sharedState) : sharedState_(new SharedState(*sharedState)) {}
    Flyweight(const Flyweight &other) : sharedState_(new SharedState(*other.sharedState_)) {}
    ~Flyweight() {
        delete sharedState_;
    };

    [[nodiscard]] SharedState *sharedState() const {
        return sharedState_;
    }
    void Operation(const UniqueState &uniqueState) const {
        cout << "Flyweight: Displaying shared (" << *sharedState_ << ") and unique ("
             << uniqueState << ") state.\n";
    }
};

/* The FlyweightFactory creates and manages Lightweight objects.
 * It provides the correct separation of flyweights. When a client
 * requests a flyweight, the factory either returns an existing
 * instance or creates a new one if it does not already exist. */
class FlyweightFactory
{
private:
    unordered_map<string , Flyweight> flyweights;

    /* Returns the hash of the Flyweight string for the given state. */
    string GetKey(const SharedState &sharedState) const {
        return sharedState.brand_ + "_" + sharedState.model_ + "_" + sharedState.color_;
    }

public:
    FlyweightFactory(initializer_list<SharedState> shareStates){
        for(const SharedState &sharedState : shareStates){
            this->flyweights.insert(make_pair<string, Flyweight>
                                        (this->GetKey(sharedState), Flyweight(&sharedState)));
        }
    }
    /* Returns an existing Flyweight with the specified state or creates a new one. */
    Flyweight GetFlyweight(const SharedState &sharedState){
        string key = this->GetKey(sharedState);
        if(this->flyweights.find(key) == this->flyweights.end()) {
            cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
            this->flyweights.insert(make_pair(key, Flyweight(&sharedState)));
        }else {
            cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }

        return this->flyweights.at(key);
    }

    void listFlyweights() const {
        size_t count = this->flyweights.size();
        cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
        for(pair<string, Flyweight> pair : this->flyweights) {
            cout << pair.first << "\n";
        }
    }
};

void addCarToPoliceDatabase(FlyweightFactory &ff, const string &plates, const string &owner,
                            const string &brand, const string &model, const string &color)
{
    cout << "\nClient: Adding a car to database.\n";
    const Flyweight &flyweight = ff.GetFlyweight({brand, model, color});
    flyweight.Operation({plates, owner});
}

int main()
{
    auto factory = new FlyweightFactory({
        {"Chevrolet", "Camaro2018", "pink"},
        {"Mercedes Benz", "C300", "black"},
        {"Mercedes Benz", "C500", "red"},
        {"BMW", "M5", "red"},
        {"BMW", "X6", "white"}
    });

    factory->listFlyweights();

    addCarToPoliceDatabase(*factory,
                           "CL234IR",
                           "James Doe",
                           "BMW",
                           "M5",
                           "red");

    addCarToPoliceDatabase(*factory,
                           "CL234IR",
                           "James Doe",
                           "BMW",
                           "X1",
                           "red");

    factory->listFlyweights();
    delete factory;
    return 0;
}