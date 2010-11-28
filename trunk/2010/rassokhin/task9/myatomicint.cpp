#include "myatomicint.h"

MyAtomicInt::MyAtomicInt() {
}

int MyAtomicInt::get() {
    mutex.lock();
    int ret = value;
    mutex.unlock();
    return ret;
}

void MyAtomicInt::set(int newValue) {
    mutex.lock();
    value = newValue;
    mutex.unlock();
    emit changed(value);
}

void MyAtomicInt::inc() {
    mutex.lock();
    value++;
    mutex.unlock();
    emit changed(value);
}

