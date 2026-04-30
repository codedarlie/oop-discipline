#ifndef RECT_H
#define RECT_H

#include "shape.h"

class Rect: public Shape
{
public:
    Rect(QPoint, QSize, QColor c = Qt::blue);

    virtual void draw(QPainter&) const;
    virtual bool containsPoint(QPoint&) const;

    ~Rect();
};

#endif // RECT_H
