#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual string doAlgorithm(const vector<string> &data) const = 0;
};

int main()
{
    return 0;
}