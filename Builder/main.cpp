#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class SuperBot {
public:
    string parts;
    void partsList() const {
        cout << "SuperBot parts: ";
        for(size_t i = 0; i < parts.size(); ++i) {
            if(parts[i] == parts.back())
                cout << parts[i];
            else
                cout << parts[i] << ", ";
        }

        cout << endl << endl;
    }
};

class Builder {
public:
    virtual ~Builder()= default;;
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};

class SuperBotBuilder : public Builder {
private:
    SuperBot* superBot;
public:

};

int main()
{

}

