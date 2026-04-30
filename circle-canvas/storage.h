#ifndef STORAGE_H
#define STORAGE_H

#include <QList>
#include <QDebug>
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

    T* at(int index) {
        return l.at(index);
    }

    int getSize() const {
        return l.size();
    }

    void remove(int index) {
        if (index >= 0 && index < l.size()) {
            delete l.at(index);
            l.remove(index);
        }
    }

    ~Storage() {
        qDebug() << "~Storage";
        for (auto& i: l) {
            delete i;
        }
    }
};

#endif // STORAGE_H
