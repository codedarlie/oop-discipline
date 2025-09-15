#include "ccircle.h"

/*
    переделать:
        границы при создании чтобы учитывались - если попали то предупреждение!
*/

CCircle::CCircle(int gx, int gy)
{
    x = gx;
    y = gy;

    qDebug() << "CCircle Constructor: " << gx << " | " << gy;
}

bool CCircle::containsPoint(int gx, int gy) const
{
    int dx = gx - x;
    int dy = gy - y;
    int distSqr = dx*dx + dy*dy;
    // qDebug() << distSqr << " <= " << radius*radius;

    return distSqr <= (radius*radius);
}

void CCircle::draw(QPainter& painter) const
{
    if (hide) return;
    painter.setPen(QPen(Qt::black, 1));

    if (selected) painter.setBrush(QBrush(Qt::red));
    else if (hovered) painter.setBrush(QBrush(Qt::blue));
    else painter.setBrush(QBrush(Qt::gray));

    painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
}

void CCircle::setSelected(bool value)
{
    selected = value;
}

void CCircle::setHovered(bool value)
{
    hovered = value;
}

void CCircle::setHide(bool value)
{
    hide = value;
}

int CCircle::getX() const
{
    return x;
}

int CCircle::getY() const
{
    return y;
}

bool CCircle::getSelected() const
{
    return selected;
}

bool CCircle::getHovered() const
{
    return hovered;
}

CCircle::~CCircle()
{
    qDebug() << "~CCircle";
}
