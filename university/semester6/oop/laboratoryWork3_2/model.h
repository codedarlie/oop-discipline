#ifndef MODEL_H
#define MODEL_H

#include "abc.h"

#include <QObject>
#include <QSettings>
#include <QDebug>

class model: public QObject
{
    Q_OBJECT
public:
    model(QObject* parent = nullptr);

    virtual ~model();

private:
    int a;
    int b;
    int c;

    QSettings* values;

public slots:
    void changeData(abc, int);
    void initializeSlot();

signals:
    void updateView(int, int, int);
};

#endif // MODEL_H
