#ifndef TRIANG_H
#define TRIANG_H

#include "shape.h"

class Triang : public Shape
{
public:
    Triang(QPoint p, int size, QColor c = Qt::green);
    Triang(QPoint p, QSize s, QColor c = Qt::green);

    virtual bool containsPoint(QPoint& p) const override;
    virtual void draw(QPainter& painter) const override;
    virtual void resize(QPoint offset, QSize& bounds) override;

    ~Triang();

private:
    QPolygon getPolygon() const;
};

#endif // TRIANG_H