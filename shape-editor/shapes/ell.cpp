#include "ell.h"


Ell::Ell(QPoint p, QSize s, QColor color):
    Shape(p, s, color)
{
    qDebug() << "Ell::Ell2";
}

bool Ell::containsPoint(QPoint& p) const
{
    // (x^2/rx^2) + (y^2/ry^2) <= 1
    double rx = rect.width() / 2;
    double ry = rect.height() / 2;

    double dx = p.x() - rect.center().x();
    double dy = p.y() - rect.center().y();

    return (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1;
}

void Ell::draw(QPainter& painter) const
{
    // if (hide) return;

    setDrawSettings(painter);
    painter.drawEllipse(rect);
    if (selected) drawSelectedOutline(false, painter);
}


Ell::~Ell()
{
    qDebug() << "Ell::~Ell";
}

QRect Ell::getRect() const
{
    return rect;
}
