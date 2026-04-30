#include "paintbox.h"

PaintBox::PaintBox(QWidget *parent):
    QWidget(parent),
    storage(Storage<CCircle>())
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

void PaintBox::paintEvent(QPaintEvent *event)
{
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
        qDebug() << "keyPressEvent: ctrl";
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

void PaintBox::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        qDebug() << "keyReleaseEvent: ctrl";
        ctrl = false;
    }
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

    qDebug() << "resizeEvent";

    QWidget::resizeEvent(event);

    update();
}

void PaintBox::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";

    int x = event->pos().x();
    int y = event->pos().y();

    bool selectAll {true};

    if (event->button() == Qt::LeftButton) {
        bool hitButton {false};

        int stSize = storage.getSize();

        bool hitForSelect {false};

        std::vector<int> indexesToSelect {std::vector<int>()};

        for (int i = 0; i < stSize; ++i) {
            auto* c = storage.at(i);
            if (c->containsPoint(x, y)) {
                hitButton = true;
                indexesToSelect.push_back(i);
                if (!c->getSelected()) hitForSelect = true;
            }
        }

        if (!hitButton) {
            // Создание

            // todo: 20 как константу брать радиус
            if ((x + 20 > size().width()) || (y + 20 > size().height()) || (x < 20) || (y < 20)) {
                QMessageBox::warning(this, "Предупреждение!", "Нельзя создавать объекты на границах!");
                return;
            }

            for (int k = 0; k < stSize; ++k) {
                storage.at(k)->setSelected(false);
            }

            storage.append(new CCircle(x, y));
            storage.at(stSize)->setHovered(true);
        } else {
            // Выделение
            if (!selectAll) {
                auto* c = storage.at(indexesToSelect[indexesToSelect.size()-1]);
                if (c->getSelected()) {
                    if (!ctrl) {
                        for (int k = 0; k < stSize; ++k) {
                            storage.at(k)->setSelected(false);
                        }
                    }
                    c->setSelected(false);
                } else {
                    if (!ctrl) {
                        for (int k = 0; k < stSize; ++k) {
                            storage.at(k)->setSelected(false);
                        }
                    }
                    c->setSelected(true);
                }
            } else {
                if (hitForSelect) {
                    if (!ctrl) {
                        for (int k = 0; k < stSize; ++k) {
                            storage.at(k)->setSelected(false);
                        }
                    }
                    for (size_t k = 0; k < indexesToSelect.size(); ++k) {
                        storage.at(indexesToSelect[k])->setSelected(true);
                    }
                } else {
                    if (ctrl) {
                        for (size_t k = 0; k < indexesToSelect.size(); ++k) {
                            storage.at(indexesToSelect[k])->setSelected(false);
                        }
                    } else {
                        for (int k = 0; k < stSize; ++k) {
                            storage.at(k)->setSelected(false);
                        }
                    }
                }
            }
        }
        update();
    }
}

void PaintBox::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    qDebug() << "mouseMoveEvent: " << x << "|" << y;

    for (int i = 0; i < storage.getSize(); ++i) {
        if (storage.at(i)->containsPoint(x, y)) {
            storage.at(i)->setHovered(true);
        } else {
            storage.at(i)->setHovered(false);
        }
    }
    update();
}

