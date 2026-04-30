#include "shape.h"

Shape::Shape(QPoint p, QSize s, QColor c):
    rect (p, s),
    color (c)
{
    qDebug() << "Shape::Shape";
}

bool Shape::isSelected() const
{
    return selected;
}

bool Shape::getMoving()
{
    return isMoving;
}

bool Shape::isWithinBounds(QRect& bounds) const
{
    qDebug() << "Rect::isWithinBounds";
    return bounds.contains(rect);
}

QColor Shape::getColor() const
{
    return color;
}

void Shape::move(QPoint offset, QSize& bounds)
{
    qDebug() << "Shape::move";

    int x = rect.x();
    int y = rect.y();
    int w = rect.width();
    if (w < 0) {
        x += w;
        w = -w;
    }
    int h = rect.height();
    if (h < 0) {
        y += h;
        h = -h;
    }

    if (x + offset.x() < 0) {
        offset.setX(0 - x);
    } else if (x + w + offset.x() > bounds.width()) {
        offset.setX(bounds.width() - x - w);
    }

    if (y + offset.y() < 0) {
        offset.setY(0 - y);
    } else if (y + h + offset.y() > bounds.height()) {
        offset.setY(bounds.height() - y - h);
    }

    rect.translate(offset);
}


void Shape::resize(QPoint offset, QSize& bounds)
{
    int x = rect.x();
    int y = rect.y();

    int w = rect.width();
    if (w < 0) {
        x += w;
        w = -w;
    }

    int h = rect.height();
    if (h < 0) {
        y += h;
        h = -h;
    }

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
        rect.setWidth(rect.width());
        rect.setY(rect.y() + offset.y());
        rect.setHeight(rect.height());
        break;
    case Handles::LeftBottom:
        rect.setX(rect.x() + offset.x());
        rect.setWidth(rect.width());
        rect.setHeight(rect.height() + offset.y());
        break;
    case Handles::RightTop:
        rect.setWidth(rect.width() + offset.x());
        rect.setY(rect.y() + offset.y());
        rect.setHeight(rect.height());
        break;
    }
}

void Shape::resizeEnd()
{
    qDebug() << "Shape: " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height();
    // if (rect.width() < 0) {
    //     int oldX = rect.x();
    //     int oldWidth = rect.width();
    //     rect.setX(oldX + oldWidth);
    //     rect.setWidth(-oldWidth);
    // }

    // if (rect.height() < 0) {
    //     int oldY = rect.y();
    //     int oldHeight = rect.height();
    //     rect.setY(oldY + oldHeight);
    //     rect.setHeight(-oldHeight);
    // }
    qDebug() << "Now Shape: " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height();

    // setResizing(false);
    // handle = Handles::RightBottom;
}

bool Shape::findHandles(QPoint& mouse)
{
    bool findHandle = false;
    QRect mouseArea (mouse.x() - 5, mouse.y() - 5, 10, 10);

    int x = rect.x();
    int y = rect.y();
    int w = rect.width();
    int h = rect.height();
    if (mouseArea.contains(x + w, y + h)) {
        handle = Handles::RightBottom; // (default)
        findHandle = true;
        qDebug() << "Handle: RightBottom";
    } else if (mouseArea.contains(x + w, y)) {
        handle = Handles::RightTop;
        findHandle = true;
        qDebug() << "Handle: RightTop";
    } else if (mouseArea.contains(x , y + h)) {
        handle = Handles::LeftBottom;
        findHandle = true;
        qDebug() << "Handle: LeftBottom";
    } else if (mouseArea.contains(x , y)) {
        handle = Handles::LeftTop;
        findHandle = true;
        qDebug() << "Handle: LeftTop";
    }

    return findHandle;
}

bool Shape::isHovered() const
{
    return hovered;
}

void Shape::setSelected(bool v)
{
    selected = v;
}

void Shape::setHovered(bool v)
{
    hovered = v;
}

void Shape::setResizing(bool v)
{
    isResizing = v;
}

void Shape::setMoving(bool v)
{
    isMoving = v;
}

void Shape::setColor(QColor c)
{
    color = c;
}

bool Shape::isShapeSmall()
{
    return (qAbs(rect.width()) < 20) || (qAbs(rect.height()) < 20);
}

void Shape::setDrawSettings(QPainter& painter) const
{
    if (selected || isMoving || isResizing) {
        QPen dashedPen(Qt::black, 1);
        dashedPen.setStyle(Qt::DashLine);
        dashedPen.setDashPattern({5, 5});
        painter.setPen(dashedPen);

        QColor c = color;
        c.setAlpha(150);
        painter.setBrush(QBrush(c));
    } else if (hovered) {
        painter.setPen(QPen(Qt::black, 1));

        QColor c = color;
        c.setAlpha(200);
        painter.setBrush(QBrush(c));
    } else {
        painter.setPen(QPen(Qt::black, 1));
        painter.setBrush(QBrush(color));
    }
}

void Shape::drawSelectedOutline(bool isRect, QPainter& painter) const
{
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::black, 4));

    painter.drawPoint(rect.x(), rect.y());
    painter.drawPoint(rect.x() + rect.width(), rect.y());
    painter.drawPoint(rect.x(), rect.y() + rect.height());
    painter.drawPoint(rect.x() + rect.width(), rect.y() + rect.height());

    if (!isRect) {
        QPen dashed(Qt::black, 0.5);
        dashed.setStyle(Qt::DashLine);
        dashed.setDashPattern({5, 5});
        painter.setPen(dashed);
        painter.drawRect(rect);
    }
}
