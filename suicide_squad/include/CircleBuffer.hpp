#include <iostream>
#include <deque>

template <typename T>
class cique {
private:
    int size;
public:
    std::deque<T> elems;

    cique() = default;

    cique(int size) {
        this->size = size;
    }

    void setSize(int size) {
        this->size = size;
        elems.resize(size);
    }

    void push(T elem) {
        if (elems.size() < size) {
            elems.push_back(elem);
        }
        else {
            elems.pop_front();
            elems.push_back(elem);
        }
    }

    void pop() {
        T temp = elems.back();
        elems.pop_back();
        elems.push_front(temp);
    }

    T back() {
        return elems.back();
    }

    T front() {
        return elems.front();
    }
};