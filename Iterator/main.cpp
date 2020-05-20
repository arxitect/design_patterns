#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::vector;

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
        m_data_.push_back();
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
};

int main()
{
    return 0;
}