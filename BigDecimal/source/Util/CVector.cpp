#include "CVector.h"

template<class T>
CVector<T>::CVector() {
    _capacity = 0;
    _size = 0;
    buffer = 0;
    Log = 0;
}

template<class T>
CVector<T>::CVector(const CVector<T> & v) {
    _size = v._size;
    Log = v.Log;
    _capacity = v._capacity;
    buffer = new T[_size];
    for (unsigned int i = 0; i < _size; i++)
        buffer[i] = v.buffer[i];
}

template<class T>
CVector<T>::CVector(unsigned int size) {
    _size = size;
    Log = ceil(log((double) size) / log(2.0));
    _capacity = 1 << Log;
    buffer = new T[_capacity];
}

template <class T>
bool CVector<T>:: empty() const {
    return _size == 0;
}

template<class T>
CVector<T>::CVector(unsigned int size, const T& initial) {
    _size = size;
    Log = ceil(log((double) size) / log(2.0));
    _capacity = 1 << Log;
    buffer = new T [_capacity];
    for (unsigned int i = 0; i < size; i++)
        buffer[i] = initial;
}

template<class T>
CVector<T>& CVector<T>::operator = (const CVector<T> & v) {
    delete[] buffer;
    _size = v._size;
    Log = v.Log;
    _capacity = v._capacity;
    buffer = new T [_capacity];
    for (unsigned int i = 0; i < _size; i++)
        buffer[i] = v.buffer[i];
    return *this;
}

template<class T>
typename CVector<T>::Iterator CVector<T>::begin() {
    return buffer;
}

template<class T>
typename CVector<T>::Iterator CVector<T>::end() {
    return buffer + size();
}

template<class T>
T& CVector<T>::front() {
    return buffer[0];
}

template<class T>
T& CVector<T>::back() {
    return buffer[_size - 1];
}

template<class T>
void CVector<T>::push_back(const T & v) {
    /*
        Incidentally, one common way of regrowing an array is to double the size as needed.
        This is so that if you are inserting n items at most only O(log n) regrowths are performed
        and at most O(n) space is wasted.
    */
    if (_size >= _capacity) {
        reserve(1 << Log);
        Log++;
    }
    buffer [_size++] = v;
}

template<class T>
void CVector<T>::pop_back() {
    _size--;
}

template<class T>
void CVector<T>::reserve(unsigned int capacity) {
    T * newBuffer = new T[capacity];

    for (unsigned int i = 0; i < _size; i++)
        newBuffer[i] = buffer[i];

    _capacity = capacity;
    delete[] buffer;
    buffer = newBuffer;
}

template<class T>
unsigned int CVector<T>::size() const {
    return _size;
}

template<class T>
void CVector<T>::resize(unsigned int size) {
    Log = ceil(log((double) size) / log(2.0));
    reserve(1 << Log);
    _size = size;
}

template<class T>
T& CVector<T>::operator[](unsigned int index) {
    return buffer[index];
}

template<class T>
unsigned int CVector<T>::capacity()const {
    return _capacity;
}

template<class T>
CVector<T>::~CVector() {
    delete[] buffer;
}

template <class T>
void CVector<T>::clear() {
    _capacity = 0;
    _size = 0;
    buffer = 0;
    Log = 0;
}