#ifndef STORAGE_H
#define STORAGE_H

#include <QList>

#include <QDebug>
#include <QPainter>

#include "ccircle.h"

template <typename T>
class Storage {
private:
    QList<T*> l;

public:
    Storage() = default;

    void append(T* t) {
        l.append(t);
    }

    // void insert(int, T*);

    T* at(int index) {
        return l.at(index);
    }

    // void set(int, T*);

    int getSize() const {
        return l.size();
    }

    void remove(int index) {
        l.remove(index);
    }

    ~Storage() {
        qDebug() << "~Storage";
        for (auto& i: l) {
            delete i;
        }
    }
};

#endif // STORAGE_H
