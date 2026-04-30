#include "controller.h"

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
    emit sendDataToModel(sl, value);
}

void controller::initializeSlot()
{
    emit initializeSignal();
}


