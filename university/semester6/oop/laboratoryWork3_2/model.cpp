#include "model.h"

model::model(QObject* parent): values{new QSettings("values", "app")} {
    a = values->value("valueA", 0).toInt();
    b = values->value("valueB", 50).toInt();
    c = values->value("valueC", 100).toInt();

    qDebug() << "model constructor.";
}

model::~model()
{
    delete values;
}

void model::changeData(abc sl, int value)
{
    if (sl == abc::A) {
        if (value < 0) a = 0;
        else if (value > c) {
            a = c;
            if (b < a) b = a;
        } else a = value;

        if (b < a) b = a;

    } else if (sl == abc::B) {
        if (value < a) b = a;
        else if (value > c) b = c;
        else b = value;

    } else {
        if (value > 100) c = 100;
        else if (value < a) {
            c = a;
            if (b > c) b = c;
        } else c = value;

        if (b > c) b = c;

    }

    values->setValue("valueA", a);
    values->setValue("valueB", b);
    values->setValue("valueC", c);

    emit updateView(a, b, c);
}

void model::initializeSlot()
{
    emit updateView(a, b, c);
}
