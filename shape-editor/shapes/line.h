#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line: public Shape
{
public:
    Line(QPoint, QSize, QColor c = Qt::blue);

    virtual void draw(QPainter&) const;
    virtual bool containsPoint(QPoint&) const;

    ~Line();
};

#endif // LINE_H
