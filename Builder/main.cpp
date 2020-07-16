#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

/* Builders can produce unrelated elements */
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

/* Builder Interface declares creating methods for various parts of objects */
class Builder {
public:
    virtual ~Builder()= default;;
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};

/* The concrete Builder classes follow the Builder interface
 * and provide concrete implementations of the building steps. */
class SuperBotBuilder : public Builder {
private:
    SuperBot* superBot;
    /* A new instance of the builder must contain an empty object,
     * which is used in further assembly. */
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

/* The director is only responsible for completing
 * the construction steps in a specific sequence. */
class Director {
private:
    Builder *builder;
public:
    void setBuilder(Builder *pBuilder) {
        this->builder = pBuilder;
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

/* The client code creates the builder object, passes it to the director,
 * and then initiates the construction process.
 * The final result is extracted from the builder. */
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

