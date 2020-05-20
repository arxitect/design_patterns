#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

template<typename T, typename U>
class Iterator {
public:
    typedef typename vector<T>::iterator iter_type;
    Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data) {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void First() {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void Next() {
        m_it_++;
    }

    bool IsDone() {
        return (m_it_ == m_p_data_->m_data_.end());
    }

    iter_type Current() {
        return m_it_;
    }

private:
    U *m_p_data_;
    iter_type m_it_;
};

template <class T>
class Container {
    friend class Iterator<T, Container>;
private:
    vector<T> m_data_;
public:
    void Add(T a) {
        m_data_.push_back(a);
    };
    Iterator<T, Container> *createIterator() {
        return new Iterator<T, Container>(this);
    }
};

class Data {
private:
    int m_data_;
public:
    Data(int a = 0) : m_data_(a) {}

    void setData(int a) {
        m_data_ = a;
    }
    int data() {
        return m_data_;
    }
};

void ClientCode()
{
    cout <<  "________________Iterator with int______________________________________" << endl;
    Container<int> cont;

    for(int i = 0;i < 10;i++)
        cont.Add(i);

    Iterator<int, Container<int>> *it = cont.createIterator();
    for(it->First(); !it->IsDone(); it->Next())
        cout << *it->Current() << endl;

    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.Add(a);
    cont2.Add(b);
    cont2.Add(c);

    cout << "________________Iterator with custom Class______________________________" << endl;

    Iterator<Data, Container<Data>> *it2 = cont2.createIterator();
    for (it2->First(); !it2->IsDone(); it2->Next())
        cout << it2->Current()->data() << endl;
}

int main()
{
    ClientCode();
    return 0;
}