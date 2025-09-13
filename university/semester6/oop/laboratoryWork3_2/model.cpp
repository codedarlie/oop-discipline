#include "model.h"

#include <QDebug>

// model::model(MainWindow* v, QObject* parent): view{v}, a{0}, b{50}, c{100} {
model::model(QObject* parent): a{0}, b{50}, c{100} {
    // connect(this, &model::updateView, view, &MainWindow::updateData);
    qDebug() << "model::model";
    // emit updateView(a,b,c);
}

void model::changeData(abc sl, int value)
{
    qDebug() << "changeData: " << QString::number(value);

    if (sl == abc::A) {
        if (value < 0) {
            qDebug() << "a, v < 0";
            a = 0;
        }
        else if (value > c) {
            qDebug() << "a, v > c";
            a = c;
            if (b < a) b = a;
        } else {
            a = value;
        }

        if (b < a) b = a;

    } else if (sl == abc::B) {
        if (value < a) {
            qDebug() << "b, v < a";
            b = a;
        } else if (value > c) {
            qDebug() << "b, v > c";
            b = c;
        } else {
            qDebug() << "b, a < b < c";
            b = value;
        }
    } else {
        if (value > 100) {
            qDebug() << "c, v > 100";
            c = 100;
        }
        else if (value < a) {
            qDebug() << "c, v < a";
            c = a;
            if (b > c) b = c;
        } else {
            c = value;
        }

        if (b > c) b = c;
    }

    qDebug() << "go to updateView";
    emit updateView(a, b, c);
}

void model::initializeSlot()
{
    emit updateView(a, b, c);
}
