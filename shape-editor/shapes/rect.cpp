#include "rect.h"

Rect::Rect(QPoint p, QSize s, QColor c):
    Shape(p, s, color)
{
    qDebug() << "Rect::Rect";
}

void Rect::draw(QPainter& painter) const
{    
    setDrawSettings(painter);
    painter.drawRect(rect);
    if (selected) drawSelectedOutline(true, painter);
}

bool Rect::containsPoint(QPoint& p) const
{
    return rect.contains(p);
}

Rect::~Rect()
{
    qDebug() << "Rect::~Rect";
}
