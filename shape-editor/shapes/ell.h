#ifndef ELL_H
#define ELL_H

#include "shape.h"

class Ell: public Shape {
public:
    Ell(QPoint, QSize, QColor color = Qt::yellow);

    virtual bool containsPoint(QPoint&) const;
    virtual void draw(QPainter&) const;

    ~Ell();
protected:
    // int radiusX;
    // int radiusY;
    virtual QRect getRect() const;
};

#endif // ELL_H
