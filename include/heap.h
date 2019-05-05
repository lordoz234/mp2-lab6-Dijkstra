#ifndef _INCLUDE_HEAP_H
#define _INCLUDE_HEAP_H

#include <iostream>
#include <vector>

template <class T>
class Heap {
private:
    std::vector <T> v;
    int size;
    int k;
public:
    Heap(int r);
    void insert(T a);
    void shiftdown(int i);
    void shiftup(int i);
    T minimum();
    int getsize();
};

template <class T>
Heap<T>::Heap(int r) {
    size = 0;
    k = r;
}

template <class T>
int Heap<T>::getsize() {
    return size;
}

template <class T>
void Heap<T>::insert(T a) {
    v.push_back(a);
    ++size;
    shiftup(size - 1);
}

template <class T>
T Heap<T>::minimum() {
    T mini = v[0];
    if (size - 1 != 0) {
        v[0] = v[size - 1];
    }
    v.erase(v.begin() + size - 1, v.begin() + size);
    --size;
    shiftdown(0);
    return mini;
}

template <class T>
void Heap<T>::shiftup (int i) {
    int p = (i - 1)/k;
    while ( i != 0 && v[i] < v[p]) {
        swap(v[i], v[p]);
        i = p;
        p = (i - 1)/k;
    }
}

template <class T>
void Heap<T>::shiftdown (int i) {
    while (2*i + 1 < size) {
        T mini = v[i];
        int j1 = i;
        for (int j = 1; j <= k; j++) {
            if (2*i + j < size && mini > v[2*i + j]) {
                mini = v[2*i + j];
                j1 = 2*i + j;
            }
        }
        if (j1 == i) {
            break;
        }
        swap(v[j1], v[i]);
        i = j1;
    }
}

#endif //_INCLUDE_HEAP_H