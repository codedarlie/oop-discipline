#include "circ.h"

Circ::Circ(QPoint p, int s, QColor c):
    Ell(p, QSize(s, s), color)
{
    qDebug() << "Circ::Circ";
}

void Circ::resize(QPoint& newCoords, QSize& bounds)
{
    int x = newCoords.x();
    if (x < 0) x = 0;
    else if (x > bounds.width()) x = bounds.width();

    int y = newCoords.y();
    if (y < 0) y = 0;
    else if (y > bounds.height()) y = bounds.height();

    int oldX = rect.x();
    int oldY = rect.y();
    int oldWidth = rect.width();
    int oldHeight = rect.height();

    int size;

    switch(handle) {
    case Handles::RightBottom:
        size = qMin(x - rect.x(), y - rect.y());
        rect.setWidth(size);
        rect.setHeight(size);
        break;

    case Handles::LeftTop:
        size = qMin(oldWidth - (x - oldX), oldHeight - (y - oldY));
        rect.setX(oldX + oldWidth - size);
        rect.setY(oldY + oldHeight - size);
        rect.setWidth(size);
        rect.setHeight(size);
        break;

    case Handles::LeftBottom:
        size = qMin(oldWidth - (x - oldX), y - oldY);
        rect.setX(oldX + oldWidth - size);
        rect.setWidth(size);
        rect.setHeight(size);
        break;

    case Handles::RightTop:
        size = qMin(x - oldX, oldHeight - (y - oldY));
        rect.setY(oldY + oldHeight - size);
        rect.setWidth(size);
        rect.setHeight(size);
        break;
    }

}
