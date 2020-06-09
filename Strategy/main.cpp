#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual string doAlgorithm(const vector<string> &data) const = 0;
};


class Context
{

private:
    Strategy *strategy_;

public:
    Context(Strategy *strategy = nullptr) : strategy_(strategy){}
    ~Context(){
        delete this->strategy_;
    }

    void setStrategy(Strategy *strategy) {
        delete this->strategy_;
        this->strategy_ = strategy;
    }

    void doSomeBusinessLogic() const {
        cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
        string result = this->strategy_->doAlgorithm(vector<string>{"a", "e", "c", "b", "d"});
        cout << result << "\n";
    }
};


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
    string doAlgorithm(const vector<string> &data) const override {
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

void ClientCode()
{
    auto *context = new Context(new ConcreteStrategyA);
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