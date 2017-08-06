#ifndef CVector_H
#define CVector_H
#pragma once

template <class T>
class  CVector {
public:

    typedef T* Iterator;

    CVector();
    CVector(unsigned int size);
    CVector(unsigned int size, const T & initial);
    CVector(const CVector<T>& v);
    ~CVector();

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;
    Iterator begin();
    Iterator end();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();

    void reserve(unsigned int capacity);
    void resize(unsigned int size);

    T & operator[](unsigned int index);
    CVector<T> & operator = (const CVector<T> &);
    void clear();
private:
    unsigned int _size;
    unsigned int _capacity;
    unsigned int Log;
    T* buffer;
};


#endif
