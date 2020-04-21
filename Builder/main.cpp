#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class SuperBot {
public:
    vector<string> parts;
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
    SuperBotBuilder() {
        this->Reset();
    }

    ~SuperBotBuilder() override {
        delete superBot;
    }

    void Reset() {
        this->superBot = new SuperBot();
    }

    void ProducePartA() const override {
        this->superBot->parts.emplace_back("PartA1");
    }

    void ProducePartB() const override {
        this->superBot->parts.emplace_back("PartB1");
    }

    void ProducePartC() const override {
        this->superBot->parts.emplace_back("PartC1");
    }

    SuperBot* GetSuperBot() {
       SuperBot* result = this->superBot;
       this->Reset();
       return result;
    }
};

class Director {
private:
    Builder *builder;
public:
    void setBuilder(Builder *builder) {
        this->builder = builder;
    }

    void BuildMinimalViableSuperBot() {
        this->builder->ProducePartA();
    }

    void BuildFullFeaturedSuperBot() {
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};

void ClientCode(Director &director)
{
    SuperBotBuilder* builder = new SuperBotBuilder();
    director.setBuilder(builder);
    cout << "Basic bot: \n";
    director.BuildMinimalViableSuperBot();

    SuperBot *superBot = builder->GetSuperBot();
    superBot->partsList();
    delete superBot;

    cout << "Full superbot build:\n";
    director.BuildFullFeaturedSuperBot();

    superBot = builder->GetSuperBot();
    superBot->partsList();
    delete superBot;
    delete builder;
}

int main()
{
    Director *director = new Director;
    ClientCode(*director);
    delete director;
    return 0;
}

