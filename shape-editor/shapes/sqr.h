#ifndef SQR_H
#define SQR_H

#include "rect.h"

class Sqr: public Rect
{
public:
    Sqr(QPoint, int, QColor c = Qt::green);
    void resize(QPoint, QSize&);
};

#endif // SQR_H
