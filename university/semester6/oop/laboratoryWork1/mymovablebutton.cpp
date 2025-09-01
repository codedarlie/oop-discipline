#include "mymovablebutton.h"
#include <QApplication>
#include <QCursor>

myMovableButton::myMovableButton(QWidget *parent)
    : QPushButton(parent)
    , dragging(false)
    , fellIntoPlace(false)
{
    setStyleSheet("background-color: rgb(119, 118, 123)");
}

void myMovableButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (fellIntoPlace) {
            setCursor(Qt::ArrowCursor);
            // todo: somefunction(); START

        } else {
            dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
            dragging = true;
            setCursor(Qt::ClosedHandCursor);
        }
    }
    QPushButton::mousePressEvent(event);
}

void myMovableButton::mouseMoveEvent(QMouseEvent *event)
{
    if (fellIntoPlace) return;

    if (dragging && (event->buttons() & Qt::LeftButton)) {
        // todo: смотреть чтобы не выходил за границы
        move(event->globalPosition().toPoint() - dragPosition);
    }
    QPushButton::mouseMoveEvent(event);

    checkPosition();
}

void myMovableButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false;
        setCursor(Qt::ArrowCursor);
    }
    QPushButton::mouseReleaseEvent(event);
}

void myMovableButton::checkPosition() {
    int bX = mapToGlobal(QPoint(0, 0)).x();
    int bY = mapToGlobal(QPoint(0, 0)).y();

    // QPoint(155, 235-23)
    int rX = 155;
    int rY = 235-23;

    int rangeEntry = 5;

    if ((rX - rangeEntry <= bX) && (bX <= rX + rangeEntry) && (rY - rangeEntry <= bY) && (bY <= rY + rangeEntry)) {
        move(rX, rY);
        fellIntoPlace = true;
        setStyleSheet("background-color: rgb(36, 31, 49)");

        return;
    }
}
