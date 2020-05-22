#include <iostream>
#include <string>

using std::string;
using std::cout;

class BaseComponent;
class Mediator {
public:
    virtual void Notify(BaseComponent *sender, string event) const = 0;
};

int main()
{
    return 0;
}