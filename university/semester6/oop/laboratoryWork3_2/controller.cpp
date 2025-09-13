#include "controller.h"

#include <QDebug>

controller::controller(model* mod, QObject* parent): m{mod} {
    connect(this, &controller::sendDataToModel, m, &model::changeData);
    connect(this, &controller::initializeSignal, m, &model::initializeSlot);
}

controller::~controller() {
    m = nullptr;
}

void controller::setModel(model *sm)
{
    m = sm;
}

void controller::receiveValue(abc sl, int value)
{
    qDebug() << "receiveValue: " << QString::number(value);
    // bool digit = true;
    // for (const auto& i: arg) {
        // if (!i.isDigit()) {
            // digit = false;
            // break;
        // }
    // }

    // if (digit) {
    // qDebug() << arg.toInt();
    // emit changeData(sl, arg.toInt());
    // } else {
    // emit changeData(sl, -1);
    // }
        // arg.toInt();

    // QMessageBox::information(, "Уведомление о нажатой кнопке", "awd");

    emit sendDataToModel(sl, value);
}

void controller::initializeSlot()
{
    emit initializeSignal();
}


