#include "sqr.h"

Sqr::Sqr(QPoint p, int s, QColor c):
    Rect(p, QSize(s, s), color)
{
    qDebug() << "Sqr::Sqr";
}

void Sqr::resize(QPoint offset, QSize& bounds)
{
    // если стал слишком маленький размер то не делать и предупреждать
    int x = rect.x();
    int y = rect.y();

    int w = rect.width();
    if (w < 0) {
        x += w;
        w = -w;
    }

    int h = rect.height();
    if (h < 0) {
        y += h;
        h = -h;
    }

    // todo min
    if (x + offset.x() < 0) offset.setX(0 - x);
    else if (x + w + offset.x() > bounds.width()) offset.setX(bounds.width() - x - w);

    if (y + offset.y() < 0) offset.setY(0 - y);
    else if (y + h + offset.y() > bounds.height()) offset.setY(bounds.height() - y - h);

    int offsetMax;

    // пересчитать
    qDebug() << "offset: " << offset.x() << " " << offset.y();
    switch(handle) {
    case Handles::RightBottom:
        offsetMax = qMax(offset.x(), offset.y());
        rect.setWidth(rect.width() + offsetMax);
        rect.setHeight(rect.height() + offsetMax);
        break;
    case Handles::LeftTop:
        offsetMax = qMax(offset.x(), offset.y());
        rect.setX(rect.x() + offsetMax);
        rect.setWidth(rect.width());
        rect.setY(rect.y() + offsetMax);
        rect.setHeight(rect.height());
        break;
    case Handles::LeftBottom:
        offsetMax = qMax(-offset.x(), offset.y());
        rect.setX(rect.x() - offsetMax);
        rect.setWidth(rect.width());

        rect.setHeight(rect.height() + offsetMax);
        break;
    case Handles::RightTop:
        offsetMax = qMax(-offset.x(), offset.y());
        rect.setWidth(rect.width() - offsetMax);

        rect.setY(rect.y() + offsetMax);
        rect.setHeight(rect.height());
        break;
    }



    // int x = newCoords.x();
    // if (x < 0) x = 0;
    // else if (x > bounds.width()) x = bounds.width();

    // int y = newCoords.y();
    // if (y < 0) y = 0;
    // else if (y > bounds.height()) y = bounds.height();

    // int oldX = rect.x();
    // int oldY = rect.y();
    // int oldWidth = rect.width();
    // int oldHeight = rect.height();

    // int size;

    // switch(handle) {
    //     case Handles::RightBottom:
    //         size = qMin(x - rect.x(), y - rect.y());
    //         rect.setWidth(size);
    //         rect.setHeight(size);
    //         break;

    //     case Handles::LeftTop:
    //         size = qMin(oldWidth - (x - oldX), oldHeight - (y - oldY));
    //         rect.setX(oldX + oldWidth - size);
    //         rect.setY(oldY + oldHeight - size);
    //         rect.setWidth(size);
    //         rect.setHeight(size);
    //         break;

    //     case Handles::LeftBottom:
    //         size = qMin(oldWidth - (x - oldX), y - oldY);
    //         rect.setX(oldX + oldWidth - size);
    //         rect.setWidth(size);
    //         rect.setHeight(size);
    //         break;

    //     case Handles::RightTop:
    //         size = qMin(x - oldX, oldHeight - (y - oldY));
    //         rect.setY(oldY + oldHeight - size);
    //         rect.setWidth(size);
    //         rect.setHeight(size);
    //         break;
    // }

}
