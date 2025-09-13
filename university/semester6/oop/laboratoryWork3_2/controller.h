#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "model.h"

#include "abc.h"

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
