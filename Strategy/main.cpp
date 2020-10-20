#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;

/* The Strategy interface announces operations
 * common to all supported versions of a certain algorithm. */
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual string doAlgorithm(const vector<string> &data) const = 0;
};


/* Context defines an interface of interest to client. */
class Context
{
    // The Context stores a link to one of the Strategy objects.
    // The Context does not know a specific class of Strategy.
    // He must work with all Strategies through the Strategy interface.
private:
    Strategy *strategy_;

public:
    explicit Context(Strategy *strategy = nullptr) : strategy_(strategy){}
    ~Context(){
        delete this->strategy_;
    }

     // Usually, a Context allows you to replace
     // a Strategy object at run time.
    void setStrategy(Strategy *strategy) {
        delete this->strategy_;
        this->strategy_ = strategy;
    }

     // Instead of independently implementing multiple versions
     // of the algorithm, Context delegates some work
     // to the Strategy object.
    void doSomeBusinessLogic() const {
        cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
        string result = this->strategy_->doAlgorithm(vector<string>{"a", "e", "c", "b", "d"});
        cout << result << "\n";
    }
};

/* Concrete Strategies implement the algorithm following
 * the basic interface of the Strategy. */
class ConcreteStrategyA : public Strategy
{
public:
    string doAlgorithm(const vector<std::string> &data) const override {
        string result;

        for_each(data.begin(), data.end(), [&result](const string &letter) {
            result += letter;
        });

        sort(result.begin(), result.end());

        return result;
    }
};

class ConcreteStrategyB : public Strategy
{
    [[nodiscard]] string doAlgorithm(const vector<string> &data) const override {
        string result;

        for_each(data.begin(), data.end(), [&result](const string &letter) {
            result += letter;
        });

        sort(result.begin(), result.end());
        for (int i = 0; i < result.size() / 2; i++) {
            std::swap(result[i], result[result.size() - i - 1]);
        }

        return result;
    }
};

/* Client code selects a specific strategy
 * and passes it into context. */
void ClientCode()
{
    auto context = new Context(new ConcreteStrategyA);
    cout << "Client: Strategy is set to normal sorting.\n";
    context->doSomeBusinessLogic();
    cout << "\n";

    cout << "Client: Strategy is set to reverse sorting.\n";
    context->setStrategy(new ConcreteStrategyB);
    context->doSomeBusinessLogic();

    delete context;
}

int main()
{
    ClientCode();
    return 0;
}