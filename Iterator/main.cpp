#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

/* C++ has its own implementation of iterator that works with a different
 * generics containers defined by the standard library. */

template<typename T, typename U>
class Iterator {
public:
    typedef typename vector<T>::iterator iter_type;
    explicit Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data) {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void first() {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void next() {
        m_it_++;
    }

    bool isDone() {
        return (m_it_ == m_p_data_->m_data_.end());
    }

    iter_type current() {
        return m_it_;
    }

private:
    U *m_p_data_;
    iter_type m_it_;
};

/* Specific Collections provide one or more methods for obtaining
 * new iterator instances that are compatible with the collection class. */
template <class T>
class Container {
    friend class Iterator<T, Container>;
private:
    vector<T> m_data_;
public:
    void add(T a) {
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
    explicit Data(int a = 0) : m_data_(a) {}

    void setData(int a) {
        m_data_ = a;
    }

    int data() {
        return m_data_;
    }
};

/*  The client code may or may not know about the
 * Concrete Iterator or Collection classes, for this
 * implementation the container is generic so you can
 * used with an int or with a custom class. */
void ClientCode()
{
    cout <<  "________________Iterator with int______________________________________" << endl;
    Container<int> cont;

    for(int i = 0;i < 10;i++)
        cont.add(i);

    Iterator<int, Container<int>> *it = cont.createIterator();
    for(it->first(); !it->isDone(); it->next())
        cout << *it->current() << endl;

    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.add(a);
    cont2.add(b);
    cont2.add(c);

    cout << "________________Iterator with custom Class______________________________" << endl;

    Iterator<Data, Container<Data>> *it2 = cont2.createIterator();
    for (it2->first(); !it2->isDone(); it2->next())
        cout << it2->current()->data() << endl;
}

int main()
{
    ClientCode();
    return 0;
}