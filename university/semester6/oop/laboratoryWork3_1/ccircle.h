#ifndef CCIRCLE_H
#define CCIRCLE_H

#include <QDebug>
#include <QPainter>

#include <tuple>

class CCircle
{
private:
    int x;
    int y;
    const double radius = 20;

    bool selected = false;
    bool hovered = false;
    bool hide = false;

public:
    CCircle(int, int);

    int getX() const;
    int getY() const;
    bool getSelected() const;
    bool getHovered() const;
    double getRadius() const;

    void setSelected(bool);
    void setHovered(bool);
    void setHide(bool);

    bool containsPoint(int, int) const;
    void draw(QPainter&) const;

    ~CCircle();
};

#endif // CCIRCLE_H
