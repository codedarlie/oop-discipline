#include "triang.h"

Triang::Triang(QPoint p, int size, QColor c):
    Shape(p, QSize(size, size), c)
{
    qDebug() << "Triang::Triang(QPoint, int)";
}

Triang::Triang(QPoint p, QSize s, QColor c):
    Shape(p, s, c)
{
    qDebug() << "Triang::Triang(QPoint, QSize)";
}

QPolygon Triang::getPolygon() const
{
    QPolygon polygon;
    int x = rect.x();
    int y = rect.y();
    int w = rect.width();
    int h = rect.height();

    if (w < 0) {
        x += w;
        w = -w;
    }
    if (h < 0) {
        y += h;
        h = -h;
    }

    // Равнобедренный треугольник
    polygon << QPoint(x + w / 2, y)           // верхняя вершина
            << QPoint(x, y + h)               // левая нижняя
            << QPoint(x + w, y + h);          // правая нижняя

    return polygon;
}

bool Triang::containsPoint(QPoint& p) const
{
    QPolygon polygon = getPolygon();
    return polygon.containsPoint(p, Qt::WindingFill);
}

void Triang::draw(QPainter& painter) const
{
    setDrawSettings(painter);
    painter.drawPolygon(getPolygon());
    if (selected) drawSelectedOutline(false, painter);
}

void Triang::resize(QPoint offset, QSize& bounds)
{
    int x = rect.x();
    int y = rect.y();
    int w = rect.width();
    int h = rect.height();

    if (w < 0) {
        x += w;
        w = -w;
    }
    if (h < 0) {
        y += h;
        h = -h;
    }

    // Проверка границ
    if (x + offset.x() < 0) offset.setX(0 - x);
    else if (x + w + offset.x() > bounds.width()) offset.setX(bounds.width() - x - w);

    if (y + offset.y() < 0) offset.setY(0 - y);
    else if (y + h + offset.y() > bounds.height()) offset.setY(bounds.height() - y - h);

    switch(handle) {
    case Handles::RightBottom:
        rect.setWidth(rect.width() + offset.x());
        rect.setHeight(rect.height() + offset.y());
        break;
    case Handles::LeftTop:
        rect.setX(rect.x() + offset.x());
        rect.setY(rect.y() + offset.y());
        rect.setWidth(rect.width() - offset.x());
        rect.setHeight(rect.height() - offset.y());
        break;
    case Handles::LeftBottom:
        rect.setX(rect.x() + offset.x());
        rect.setWidth(rect.width() - offset.x());
        rect.setHeight(rect.height() + offset.y());
        break;
    case Handles::RightTop:
        rect.setY(rect.y() + offset.y());
        rect.setWidth(rect.width() + offset.x());
        rect.setHeight(rect.height() - offset.y());
        break;
    }

    // Сохраняем пропорции для треугольника
    int newW = qAbs(rect.width());
    int newH = qAbs(rect.height());
    if (newW < 20) newW = 20;
    if (newH < 20) newH = 20;

    if (rect.width() < 0) rect.setX(rect.x() + rect.width());
    rect.setWidth(newW);
    if (rect.height() < 0) rect.setY(rect.y() + rect.height());
    rect.setHeight(newH);
}

Triang::~Triang()
{
    qDebug() << "Triang::~Triang";
}