#include "paintbox.h"

// PaintBox::PaintBox(QWidget *parent): QWidget(parent), st {Storage<CCircle*>()} {
PaintBox::PaintBox(QWidget *parent):
    QWidget(parent),
    storage(Storage<CCircle>())
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    CCircle* cc1 = new CCircle(154, 333);
    storage.append(cc1);

    CCircle* cc2 = new CCircle(444, 111);
    storage.append(cc2);
}

void PaintBox::paintEvent(QPaintEvent *event)
{
    event;

    // не рисуем там где нельзя
    // size();

    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);

    for (int i = 0; i < storage.getSize(); ++i) {
        CCircle* c = storage.at(i);
        c->draw(painter);
    }
}

void PaintBox::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        qDebug() << "PaintBox::keyPressEvent: ctrl";
        ctrl = true;
    }
    if (event->key() == Qt::Key_Delete) {
        for (int i = storage.getSize()-1; i >= 0 ; --i) {
            if (storage.at(i)->getSelected()) {
                storage.remove(i);
            }
        }
    }

    update();
}

void PaintBox::resizeEvent(QResizeEvent *event)
{
    // event;
    QSize newSize = event->size();
    int w = newSize.width();
    int h = newSize.height();

    for (int i = 0; i < storage.getSize(); ++i) {
        CCircle* c = storage.at(i);
        if ((c->getX() + c->getRadius() > w) || (c->getY() + c->getRadius() > h)) c->setHide(true);
        else c->setHide(false);
    }

    qDebug() << "PaintBox::resizeEvent";

    QWidget::resizeEvent(event);

    update();
}

void PaintBox::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "PaintBox::mousePressEvent";

    int x = event->pos().x();
    int y = event->pos().y();

    bool selectAll {false};

    std::vector<int> selInd;

    if (event->button() == Qt::LeftButton) {
        bool hitButton {false};

        int stSize = storage.getSize();

        for (int i = 0; i < stSize; ++i) {
            auto* c = storage.at(i);
            if (c->containsPoint(x, y)) {
                hitButton = true;
                if (c->getSelected()) {
                    if (ctrl) {
                        c->setSelected(false);
                    } else {
                        for (int k = 0; k < stSize; ++k) {
                            storage.at(k)->setSelected(false);
                        }
                    }
                } else {
                    if (ctrl) {
                        c->setSelected(true);
                    } else {
                        if (selectAll) {
                            selInd.push_back(i);
                        }
                        for (int k = 0; k < stSize; ++k) {
                            storage.at(k)->setSelected(false);
                        }
                        if (selectAll) {
                            for (auto& h: selInd) {
                                storage.at(h)->setSelected(true);
                            }
                        } else {
                            c->setSelected(true);
                        }
                    }
                }
            }
        }

        // Создание
        if (!hitButton) {
            // todo: 20 как константу брать радиус откуда то
            if ((x + 20 > size().width()) || (y + 20 > size().height()) || (x < 20) || (y < 20)) {
                QMessageBox::warning(this, "Предупреждение!", "Нельзя создавать объекты на границах!");
                return;
            }

            for (int k = 0; k < stSize; ++k) {
                storage.at(k)->setSelected(false);
            }

            storage.append(new CCircle(x, y));
            storage.at(stSize)->setHovered(true);
        }

        update();
    }

}

void PaintBox::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    qDebug() << "PaintBox::mouseMoveEvent: " << x << " | " << y;

    for (int i = 0; i < storage.getSize(); ++i) {
        if (storage.at(i)->containsPoint(x, y)) {
            storage.at(i)->setHovered(true);
        } else {
            storage.at(i)->setHovered(false);
        }
    }
    update();
}

void PaintBox::keyReleaseEvent(QKeyEvent *event)
{    
    if (event->key() == Qt::Key_Control) {
        qDebug() << "PaintBox::keyReleaseEvent: ctrl";
        ctrl = false;
    }
}
