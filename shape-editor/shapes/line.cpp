#include "line.h"

Line::Line(QPoint p, QSize s, QColor c):
    Shape(p, s, Qt::black)
{
    qDebug() << "Line::Line";
}

void Line::draw(QPainter &painter) const
{
    int x2 = rect.x() + rect.width();
    int y2 = rect.y() + rect.height();

    setDrawSettings(painter);
    painter.setPen(QPen(Qt::black, 2));

    painter.drawLine(rect.x(), rect.y(), x2, y2);
    if (selected) drawSelectedOutline(false, painter);
}

bool Line::containsPoint(QPoint& p) const
{
    return rect.contains(p);

    // QPoint p1 = rect.topLeft();
    // QPoint p2 = rect.bottomRight();

    // double distance = pointToLineDistance(p, p1, p2);

    // return distance <= 10.0;
}

Line::~Line()
{
    qDebug() << "Line::~Line";
}
