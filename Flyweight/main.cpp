#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::ostream;

struct SharedState {
    string brand_;
    string model_;
    string color_;
    SharedState(const string &brand,const string &model,const string &color)
    : brand_(brand), model_(model), color_(color){}

    friend ostream &operator<<(ostream &os, const SharedState &ss) {
        return os << "[ " << ss.brand_ << ", " << ss.model_ << ", " << ss.color_ << " ]";
    }
};

struct UniqueState
{
    string owner_;
    string plates_;

    UniqueState(const string &owner, const string &plates)
    : owner_(owner), plates_(plates){}

    friend ostream &operator<<(ostream &os, const UniqueState &us)
    {
        return os << "[ " << us.owner_ << " , " << us.plates_ << " ]";
    }
};
int main()
{
    return 0;
}