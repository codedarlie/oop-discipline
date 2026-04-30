#ifndef CIRC_H
#define CIRC_H

#include "ell.h"

class Circ: public Ell
{
public:
    Circ(QPoint, int, QColor c = Qt::green);
    void resize(QPoint&, QSize&) ;
};


#endif // CIRC_H
