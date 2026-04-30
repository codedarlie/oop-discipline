#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QDebug>
#include <QPoint>
#include <QSize>
#include <QRect>

class Shape
{
public:
    Shape(QPoint, QSize, QColor c = Qt::white);

    bool isHovered() const;
    bool isSelected() const;
    bool getMoving();
    virtual bool isWithinBounds(QRect&) const;
    QColor getColor() const;

    virtual void move(QPoint, QSize&);
    virtual void resize(QPoint, QSize&);
    virtual void resizeEnd();
    virtual bool findHandles(QPoint&);

    virtual bool containsPoint(QPoint&) const = 0;
    virtual void draw(QPainter&) const = 0;

    void setSelected(bool);
    void setHovered(bool);
    void setResizing(bool);
    void setMoving(bool);
    void setColor(QColor);

    bool isShapeSmall();

    virtual ~Shape() = default;

protected:
    QRect rect;

    QColor color;

    bool selected = false;
    bool hovered = false;
    bool isResizing = false;
    bool isMoving = false;

    enum class Handles {
        RightBottom,
        RightTop,
        LeftTop,
        LeftBottom
        // Top,
        // Left,
        // Right,
        // Bottom
    };
    Handles handle = Handles::RightBottom;

    void setDrawSettings(QPainter&) const;
    void drawSelectedOutline(bool, QPainter&) const;
};

#endif // SHAPE_H
