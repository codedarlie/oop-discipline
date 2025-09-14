#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "abc.h"

#include <QObject>
#include <QDebug>

class controller: public QObject
{
    Q_OBJECT
public:
    controller(model* mod, QObject* parent = nullptr);
    virtual ~controller();

    void setModel(model* sm);
private:
    model* m;

public slots:
    void receiveValue(abc, int);
    void initializeSlot();

signals:
    void sendDataToModel(abc, int);
    void initializeSignal();
};

#endif // CONTROLLER_H
