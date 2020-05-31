#include <string>
#include <iostream>
#include <list>

using std::list;
using std::string;
using std::cout;

class IObserver {
    virtual ~IObserver() = default;
    virtual void update(const string &messageFromSubject) = 0;
};

int main()
{
    return 0;
}